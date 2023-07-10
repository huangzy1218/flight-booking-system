#include "buffer_manager.h"
#include <fstream>
#include "commons.h"

BlockInfo* BufferManager::getFileBlock(utils::string dbName, utils::string tbName,
	int fileType, int blockNum)
{
	fhandler->increaseAge();
	FileInfo* file = fhandler->getFileInfo(dbName, tbName, fileType);
	if (file != nullptr)
	{
		BlockInfo* block = fhandler->getBlockInfo(file, blockNum);
		// ���������
		if (block != nullptr)
		{
			return block;
		}
		else
		{
			// �������������ÿ�
			BlockInfo* bp = getUsableBlock();
			bp->setBlockNum(blockNum);
			FileInfo* fp = new FileInfo(dbName, fileType, tbName, 0, 0, nullptr, nullptr);
			fhandler->addFileInfo(fp);
			bp->readInfo(path);
			fhandler->addBlockInfo(bp);
			return bp;
		}
		return 0;
	}
}

BlockInfo* BufferManager::getUsableBlock()
{

	if (bhandler->getBCount() > 0)
	{
		return bhandler->getUsableBlock();
	}
	else
	{
		// ʹ��LRUȡ����
		return fhandler->recycleBlock();
	}
}

void BufferManager::writeBlock(BlockInfo* block)
{
	// ��ִ��ʵ��д����ֻ�������� 
	block->setDirty(true);
}

void BufferManager::writeToDisk()
{
	// ִ��д���ļ�����
	fhandler->writeToDik();
}
