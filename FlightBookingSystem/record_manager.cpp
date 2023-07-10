#include "record_manager.h"
#include "index_manager.h"

#include <iomanip>
#include <iostream>

BlockInfo* RecordManager::getBlockInfo(Table* tb, int blockNum)
{
	if (blockNum == -1)
	{
		return nullptr;
	}
	BlockInfo* block = bm->getFileBlock(dbName, tb->getTbName(), FORMAT_RECORD, blockNum);
	return block;
}

void RecordManager::insert(SQLInsert& sql)
{
	utils::string tbName = sql.getTbName();

	Table* tb = cm->getDB(dbName)->getTable(tbName);
	if (tbName == nullptr)
	{
		throw TableNoExistExcepion();
	}
	// 最大容纳的记录数
	int maxCount = (BLOCK_SIZE - 12) / (tb->getRecordLength());
	utils::vector<TKey> tkeyValues;
	int pkIndex = -1;

	unsigned long valuesSize = sql.getValues().size();
	for (int i = 0; i < valuesSize; i++)
	{
		int valueType = sql.getValues()[i].dataType;
		utils::string value = sql.getValues()[i].value;
		int length = tb->getAtrs()[i].getLength();

		TKey tmp(valueType, length);
		tmp.readValue(value.c_str());
		tkeyValues.push_back(tmp);

		// 记录主键的索引
		if (tb->getAtrs()[i].getAttrType() == PRIMARY_KEY)
		{
			pkIndex = i;
		}
	}

	if (pkIndex != -1)
	{
		if (tb->getIndexNum() != 0)
		{
			BPlusTree tree(tb->getIndex(0), bm, cm, dbName);

			int value = tree.getVal(tkeyValues[pkIndex]);
			if (value == -1)
			{
				throw PrimaryKeyConflictException();
			}
		}
		else
		{
			int blockNum = tb->getFirstBlockNum();
			for (int i = 0; i < tb->getBlockCount(); i++)
			{
				BlockInfo* bp = getBlockInfo(tb, blockNum);

				for (int j = 0; j < bp->getRecordCount(); j++)
				{
					utils::vector<TKey> tkeyValue = getRecord(tb, blockNum, j);

					if (tkeyValue[pkIndex] == tkeyValues[pkIndex])
					{
						throw PrimaryKeyConflictException();
					}
				}

				blockNum = bp->getNextBlockNum();
			}
		}
	}

	char* content;
	// 已用块
	int ub = tb->getFirstBlockNum();
	// 第一个垃圾块
	int frb = tb->getRubbishNum();
	// 最后使用块
	int lastub;
	int blockNum, offset;

	// 查找第一块可用块
	while (ub != NPOS)
	{
		lastub = ub;
		BlockInfo* bp = getBlockInfo(tb, ub);
		// 当前块已查找到最大记录数
		if (bp->getRecordCount() == maxCount)
		{
			// 转入下一块
			ub = bp->getNextBlockNum();
			continue;
		}
		content = bp->getContentAddress() + bp->getRecordCount() * tb->getRecordLength();
		for (utils::vector<TKey>::iterator iter = tkeyValues.begin();
			iter != tkeyValues.end(); ++iter)
		{
			memcpy(content, iter->getKey(), iter->getLength());
			// 偏移length个单位
			content += iter->getLength();
		}
		bp->setRecordCount(1 + bp->getRecordCount());

		blockNum = ub;
		offset = bp->getRecordCount() - 1;

		bm->writeBlock(bp);

		// 添加记录到索引
		if (tb->getIndexNum() != 0)
		{
			BPlusTree tree(tb->getIndex(0), bm, cm, dbName);
			for (int i = 0; i < tb->getAtrs().size(); i++)
			{
				if (tb->getIndex(0)->getAttrName() == tb->getIndex(i)->getAttrName())
				{
					tree.add(tkeyValues[i], blockNum, offset);
					break;
				}
			}
		}
		bm->writeToDisk();
		cm->writeArchiveFile();

		return;
	}

	if (frb != NPOS)
	{
		BlockInfo* bp = getBlockInfo(tb, frb);
		content = bp->getContentAddress();
		for (utils::vector<TKey>::iterator iter = tkeyValues.begin();
			iter != tkeyValues.end(); ++iter)
		{
			memcpy(content, iter->getKey(), iter->getLength());
			content += iter->getLength();
		}
		bp->setRecordCount(1);

		BlockInfo* lastubp = getBlockInfo(tb, lastub);
		lastubp->setNextBlockNum(frb);

		tb->setFirstRubbishNum(lastub);
		
		bp->setPreBlockNum(lastub);
		bp->setNextBlockNum(NPOS);

		blockNum = frb;
		offset = 0;

		bm->writeBlock(bp);
		bm->writeBlock(lastubp);
	}
	else
	{
		// 添加一个块
		int nextBlock = tb->getFirstBlockNum();
		if (tb->getFirstBlockNum() != NPOS)
		{
			BlockInfo* upbp = getBlockInfo(tb, tb->getFirstBlockNum());
			upbp->setPreBlockNum(tb->getBlockCount());
			bm->writeBlock(upbp);
		}
		tb->setFirstBlockNum(tb->getBlockCount());
		BlockInfo* bp = getBlockInfo(tb, tb->getFirstBlockNum());

		bp->setPreBlockNum(-1);
		bp->setNextBlockNum(nextBlock);
		bp->setRecordCount(1);

		content = bp->getContentAddress();
		for (utils::vector<TKey>::iterator iter = tkeyValues.begin();
			iter != tkeyValues.end(); ++iter)
		{
			memcpy(content, iter->getKey(), iter->getLength());
			content += iter->getLength();
		}

		blockNum = tb->getBlockCount();
		offset = 0;

		bm->writeBlock(bp);

		tb->increaseBlockNum();
	}

	if (tb->getIndexNum() != 0)
	{
		BPlusTree tree(tb->getIndex(0), bm, cm, dbName);
		for (int i = 0; i < tb->getAtrs().size(); i++)
		{
			if (tb->getIndex(0)->getAttrName() == tb->getIndex(i)->getName())
			{
				tree.add(tkeyValues[i], blockNum, offset);
				break;
			}
		}
	}

	cm->writeArchiveFile();
	bm->writeToDisk();
}

void RecordManager::select(SQLSelect& sql)
{
	Table* tb = cm->getDB(dbName)->getTable(sql.getTbName());

	for (int i = 0; i < tb->getAttributeNum(); ++i)
	{
		std::cout << std::setw(9) << std::left << tb->getAtrs()[i].getAttrName();
	}
	std::cout << std::endl;

	utils::vector<utils::vector<TKey>> tkeyValues;

	bool hasIndex = false;
	int indexIdx;
	int whereIdx;

	if (tb->getIndexNum() != 0)
	{
		for (int i = 0; i < tb->getIndexNum(); i++)
		{
			Index* idx = tb->getIndex(i);
			for (int j = 0; j < sql.getWheres().size(); j++)
			{
				if (idx->getAttrName() == sql.getWheres()[j].key)
				{
					if (sql.getWheres()[i].signType == SIGN_EQ)
					{
						hasIndex = true;
						indexIdx = i;
						whereIdx = j;
					}
				}
			}
		}
	}

	if (!hasIndex)
	{
		// 没有索引
		int blockNum = tb->getFirstBlockNum();
		for (int i = 0; i < tb->getBlockCount(); i++)
		{
			BlockInfo* bp = getBlockInfo(tb, blockNum);

			for (int j = 0; j < bp->getRecordCount(); j++)
			{
				utils::vector<TKey> tkeyValue = getRecord(tb, blockNum, j);

				bool status = true;

				for (int k = 0; k < sql.getWheres().size(); k++)
				{
					SQLWhere where = sql.getWheres()[k];
					if (!satisfyWhere(tb, tkeyValue, where))
					{
						status = false;
					}
				}
				if (status)
				{
					tkeyValues.push_back(tkeyValue);
				}
			}

			blockNum = bp->getNextBlockNum();
		}
	}
	else
	{
		// 有索引
		BPlusTree tree(tb->getIndex(indexIdx), bm, cm, dbName);

		// 建立用于搜索的键值
		int type = tb->getIndex(indexIdx)->getKeyType();
		int length = tb->getIndex(indexIdx)->getKeyLen();
		utils::string value = sql.getWheres()[whereIdx].value;
		TKey destKey(type, length);

		int blockNum = tree.getVal(destKey);

		if (blockNum != NPOS)
		{
			int blockOffset = blockNum;
			blockNum = blockNum >> 16;
			blockNum = blockNum & 0xffff;
			blockOffset = blockOffset & 0xffff;
			utils::vector<TKey> tkeyValue = getRecord(tb, blockNum, blockOffset);
			bool status = true;

			for (int k = 0; k < sql.getWheres().size(); k++)
			{
				SQLWhere where = sql.getWheres()[k];
				if (!satisfyWhere(tb, tkeyValue, where))
				{
					status = false;
				}
			}
			if (status)
			{
				tkeyValues.push_back(tkeyValue);
			}
		}
	}

	for (int i = 0; i < tkeyValues.size(); i++)
	{
		for (int j = 0; j < tkeyValues[i].size(); j++)
		{
			std::cout << tkeyValues[i][j];
		}
		std::cout << std::endl;
	}
	if (tb->getIndexNum() != 0)
	{
		BPlusTree tree(tb->getIndex(0), bm, cm, dbName);
		tree.print();
	}
}


void RecordManager::remove(SQLDelete& sql)
{
	Table* tb = cm->getDB(dbName)->getTable(sql.getTbName());
	
	bool hasIndex = false;
	int indexIdx;
	int whereIdx;

	if (tb->getIndexNum() != 0)
	{
		for (int i = 0; i < tb->getIndexNum(); i++)
		{
			Index* idx = tb->getIndex(i);
			for (int j = 0; j < sql.getWheres().size(); j++)
			{
				if (idx->getAttrName() == sql.getWheres()[j].key)
				{
					if (idx->getAttrName() == sql.getWheres()[j].key)
					{
						indexIdx = i;
						if (sql.getWheres()[j].signType == SIGN_EQ)
						{
							hasIndex = true;
							whereIdx = j;
						}
					}
				}
			}
		}
	}

	if (!hasIndex)
	{
		int blockNum = tb->getFirstBlockNum();
		for (int i = 0; i < tb->getBlockCount(); i++)
		{
			BlockInfo* bp = getBlockInfo(tb, blockNum);
			int count = bp->getRecordCount();
			for (int j = 0; j < count; j++)
			{
				utils::vector<TKey> tkeyValue = getRecord(tb, blockNum, j);

				bool status = true;

				for (int k = 0; k < sql.getWheres().size(); k++)
				{
					SQLWhere where = sql.getWheres()[k];
					if (!satisfyWhere(tb, tkeyValue, where))
					{
						status = false;
					}
				}
				if (status)
				{
					deleteRecord(tb, blockNum, j);
					if (tb->getIndexNum() != 0)
					{
						BPlusTree tree(tb->getIndex(indexIdx), bm, cm, dbName);
							
						int idx = -1;
						for (int i = 0; i < tb->getAttributeNum(); i++)
						{
							if (tb->getAtrs()[i].getAttrName() == tb->getIndex(indexIdx)->getAttrName())
							{
								idx = i;
							}
						}

						tree.remove(tkeyValue[idx]);
					}
				}
			}
			blockNum = bp->getNextBlockNum();
		}
	}
	else
	{
		BPlusTree tree(tb->getIndex(indexIdx), bm, cm, dbName);

		// 建立用于搜索的键值
		int type = tb->getIndex(indexIdx)->getKeyType();
		int length = tb->getIndex(indexIdx)->getKeyLen();
		utils::string value = sql.getWheres()[whereIdx].value;
		TKey destKey(type, length);
		destKey.readValue(value);

		int blockNum = tree.getVal(destKey);

		if (blockNum != -1)
		{
			int blockOffset = blockNum;
			blockNum = blockNum >> 16;
			blockNum = blockNum & 0xffff;
			blockOffset = blockOffset & 0xffff;
			utils::vector<TKey> tkeyValue = getRecord(tb, blockNum, blockOffset);
			bool status = true;

			for (int k = 0; k < sql.getWheres().size(); k++)
			{
				SQLWhere where = sql.getWheres()[k];
				if (!satisfyWhere(tb, tkeyValue, where))
				{
					status = false;
				}
			}
			if (status)
			{
				deleteRecord(tb, blockNum, blockOffset);
				tree.remove(destKey);
			}
		}
	}

	bm->writeToDisk();
}

void RecordManager::update(SQLUpdate& sql)
{
	Table* tb = cm->getDB(dbName)->getTable(sql.getTbName());

	utils::vector<int> indices;
	utils::vector<TKey> values;
	int pkIndex = -1;
	int affectIndex = -1;

	for (int i = 0; i < tb->getAtrs().size(); i++)
	{
		if (tb->getAtrs()[i].getAttrType() == FORMAT_RECORD)
		{
			pkIndex = i;
		}
	}

	for (int i = 0; i < sql.getKeyValues().size(); i++)
	{
		int index = tb->getAttributeIndex(sql.getKeyValues()[i].key);
		indices.push_back(index);
		TKey value(tb->getAtrs()[index].getDataType(), tb->getAtrs()[index].getLength());
		value.readValue(sql.getKeyValues()[i].value);
		values.push_back(value);

		if (index == pkIndex)
		{
			affectIndex = i;
		}
	}

	if (affectIndex != -1)
	{
		if (tb->getIndexNum() != 0)
		{
			BPlusTree tree(tb->getIndex(0), bm, cm, dbName);

			int value = tree.getVal(values[affectIndex]);
			if (value != -1)
			{
				throw PrimaryKeyConflictException();
			}
		}
		else
		{
			int blockNum = tb->getFirstBlockNum();
			for (int i = 0; i < tb->getBlockCount(); i++)
			{
				BlockInfo* bp = getBlockInfo(tb, blockNum);

				for (int j = 0; j < bp->getRecordCount(); j++)
				{
					utils::vector<TKey> tkeyValue = getRecord(tb, blockNum, j);

					if (tkeyValue[pkIndex] == values[affectIndex])
					{
						throw PrimaryKeyConflictException();
					}
				}

				blockNum = bp->getNextBlockNum();
			}
		}
	}

	int blockNum = tb->getFirstBlockNum();
	for (int i = 0; i < tb->getBlockCount(); i++)
	{
		BlockInfo* bp = getBlockInfo(tb, blockNum);

		for (int j = 0; j < bp->getRecordCount(); j++)
		{
			utils::vector<TKey> tkeyValue = getRecord(tb, blockNum, j);

			bool status = true;

			for (int k = 0; k < sql.getWheres().size(); k++)
			{
				SQLWhere where = sql.getWheres()[k];
				if (!satisfyWhere(tb, tkeyValue, where))
				{
					status = false;
				}
			}
			if (status)
			{
				if (tb->getIndexNum() != 0)
				{
					BPlusTree tree(tb->getIndex(0), bm, cm, dbName);

					int idx = -1;
					for (int i = 0; i < tb->getAttributeNum(); i++)
					{
						if (tb->getAtrs()[i].getAttrName() == tb->getIndex(0)->getAttrName())
						{
							idx = i;
						}
					}

					tree.remove(tkeyValue[idx]);
				}
				updateRecord(tb, blockNum, j, indices, values);

				tkeyValue = getRecord(tb, blockNum, j);

				if (tb->getIndexNum() != 0)
				{
					BPlusTree tree(tb->getIndex(0), bm, cm, dbName);

					int idx = -1;
					for (int i = 0; i < tb->getAttributeNum(); i++)
					{
						if (tb->getAtrs()[i].getAttrName() == tb->getIndex(0)->getAttrName())
						{
							idx = i;
						}
					}

					tree.add(tkeyValue[idx], blockNum, j);
				}
			}
		}
		blockNum = bp->getNextBlockNum();
	}
	bm->writeToDisk();
}

utils::vector<TKey> RecordManager::getRecord(Table* tb, int blockNum, int offset)
{
	utils::vector<TKey> keys;
	BlockInfo* bp = getBlockInfo(tb, blockNum);

	char* content = bp->getData() + offset * tb->getRecordLength() + 12;

	for (int i = 0; i < tb->getAttributeNum(); i++)
	{
		int valueType = tb->getAtrs()[i].getDataType();
		int length = tb->getAtrs()[i].getLength();

		TKey tmp(valueType, length);

		memcpy(tmp.getKey(), content, length);

		keys.push_back(tmp);

		content += length;
	}
	return keys;
}


void RecordManager::deleteRecord(Table* tb, int blockNum, int offset)
{
	BlockInfo* bp = getBlockInfo(tb, blockNum);

	char* content = bp->getData() + offset * tb->getRecordLength() + 12;
	char* replace = bp->getData() + (bp->getRecordCount() - 1) * tb->getRecordLength() + 12;
	memcpy(content, replace, tb->getRecordLength());

	bp->decreaseRecordCount();

	// 添加块到垃圾块链
	if (bp->getRecordCount() == 0)
	{
		int preNum = bp->getPreBlockNum();
		int nextNum = bp->getNextBlockNum();

		if (preNum != -1)
		{
			BlockInfo* pbp = getBlockInfo(tb, preNum);
			pbp->setNextBlockNum(nextNum);
			bm->writeBlock(pbp);
		}

		if (nextNum != -1)
		{
			BlockInfo* nbp = getBlockInfo(tb, nextNum);
			nbp->setPreBlockNum(preNum);
			bm->writeBlock();
		}

		BlockInfo* firstRubbish = getBlockInfo(tb, tb->getFirstBlockNum());
		bp->setNextBlockNum(-1);
		bp->setPreBlockNum(-1);
		if (firstRubbish != nullptr)
		{
			firstRubbish->setPreBlockNum(blockNum);
			bp->setNextBlockNum(firstRubbish->getBlockNum());
		}
		tb->setFirstRubbishNum(blockNum);
	}

	bm->writeBlock(bp);
}

void RecordManager::updateRecord(Table* tb, int blockNum, int offset,
	utils::vector<int>& indices, utils::vector<TKey>& values)
{
	BlockInfo* bp = getBlockInfo(tb, blockNum);

	char* content = bp->getData() + offset * tb->getRecordLength() + 12;
	
	for (int i = 0; i < tb->getAttributeNum(); i++)
	{
		utils::vector<int>::iterator iter = find(indices.begin(), indices.end(), i);
		if (iter != indices.end())
		{
			memcpy(content, values[iter - indices.begin()].getKey(),
				values[iter - indices.begin()].getLength());
		}

		content += tb->getAtrs()[i].getLength();
	}

	bm->writeBlock(bp);
}

bool RecordManager::satisfyWhere(Table* tb, utils::vector<TKey> keys, SQLWhere where)
{
	int idx = -1;
	for (int i = 0; i < tb->getAttributeNum(); i++)
	{
		if (tb->getAtrs()[i].getAttrName() == where.key())
		{
			idx = i;
		}
	}

	TKey tmp(tb->getAtrs()[idx].getDataType(), tb->getAtrs()[idx].getLength());
	tmp.readValue(where.value.c_str());

	switch (where.signType)
	{
	case SIGN_EQ:
		return keys[idx] == tmp;
		break;
	case SIGN_NE:
		return keys[idx] != tmp;
		break;
	case SIGN_LT:
		return keys[idx] < tmp;
		break;
	case SIGN_GT:
		return keys[idx] > tmp;
		break;
	case SIGN_LE:
		return keys[idx] <= tmp;
		break;
	case SIGN_GE:
		return keys[idx] >= tmp;
		break;
	default:
		return false;
		break;
	}
}