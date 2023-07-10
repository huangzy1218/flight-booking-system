#pragma once

#include "string.h"
#include "vector.h"
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/vector.hpp>

#include "sql_statement.h"

class CatalogManager
{
public:
	// 构造函数
	CatalogManager(utils::string p);
	// 析构函数
	~CatalogManager();
	utils::vector<DataBase>& getDbs()
	{
		return dbs;
	}
	utils::string getPath()
	{
		return path;
	}
	DataBase* getDB(utils::string dbName);
	void readArchiveFile();
	void writeArchiveFile();
	void createDataBase(utils::string dbName);
	void deleteDataBase(utils::string dbName);
private:
	friend class boost::serialization::access;

	template <class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& dbs;
	}
	utils::string path;
	utils::vector<DataBase> dbs;
};

class DataBase
{ 
public:
	// 构造函数
	DataBase();
	DataBase(utils::string dbName);
	// 析构函数
	~DataBase()
	{}
	Table* getTable(utils::string tbName);
	utils::string getDbName()
	{
		return dbName;
	}
	void createTable(SQLCreateTable& sql);
	void dropTable(SQLDropTable& sql);
	void dropIndex(SQLDropIndex& sql);
	utils::vector<Table>& getTables()
	{
		return tbs;
	}
	bool checkIfIndexExists(utils::string indexName);
private:
	friend class boost::serialization::access;
	template <class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& dbName;
		ar& tbs;
	}
	utils::string dbName;
	utils::vector<Table> tbs;
};


class Table
{
public:
	// 构造函数
	Table()
		: tbName("")
		, recordLength(-1)
		, firstBlockNum(-1)
		, firstRubbishNum(-1)
		, blockCount(0)
	{}
	// 析构函数
	~Table()
	{}

	utils::string getTbName()
	{
		return tbName;
	}
	void setTbName(utils::string tbName)
	{
		this->tbName = tbName;
	}
	int getRecordLength()
	{
		return recordLength;
	}
	void setRecordLength(int recordLength)
	{
		this->recordLength = recordLength;
	}
	utils::vector<Attribute>& getAtrs()
	{
		return atrs;
	}
	Attribute* getAttribute(utils::string name);
	int getAttributeIndex(utils::string name);

	int getFirstBlockNum()
	{
		return firstBlockNum;
	}
	void setFirstBlockNum(int num)
	{
		firstBlockNum = num;
	}
	int getRubbishNum()
	{
		return firstBlockNum;
	}
	void setFirstRubbishNum(int num)
	{
		firstRubbishNum = num;
	}
	int getBlockCount()
	{
		return blockCount;
	}
	unsigned long getAttributeNum()
	{
		return atrs.size();
	}
	void addAttribute(Attribute& attr)
	{
		atrs.push_back(attr);
	}
	void increaseBlockNum()
	{
		blockCount++;
	}
	utils::vector<Index>& getIdxs()
	{
		return idxs;
	}
	Index* getIndex(int num)
	{
		return &(idxs[num]);
	}
	unsigned long getIndexNum()
	{
		return idxs.size();
	}
	void addIndex(Index& idx)
	{
		idxs.push_back(idx);
	}
private:
	friend class boost::serialization::access;
	template <class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& tbName;
		ar& recordLength;
		ar& firstBlockNum;
		ar& firstRubbishNum;
		ar& blockCount;
		ar& ats;
		ar& idxs;
	}
	utils::string tbName;
	int recordLength;
	int firstBlockNum;
	int firstRubbishNum;
	int blockCount;
	utils::vector<Attribute> atrs;
	utils::vector<Index> idxs;
};



class Attribute
{
public:
	// 构造函数
	Attribute()
		: attrName("")
		, dataType(-1)
		, length(-1)
		, attrType(0)
	{}
	// 析构函数
	~Attribute()
	{}
	utils::string getAttrName()
	{
		return attrName;
	}
	void setAttrName(utils::string name)
	{
		attrName = name;
	}
	int getAttrType()
	{
		return attrType;
	}
	void setAttrType(int type)
	{
		attrType = type;
	}
	int getDataType()
	{
		return dataType;
	}
	void setDataType(int type)
	{
		dataType = type;
	}
	int getLength()
	{
		return length;
	}
	void setLength(int length)
	{
		this->length = length;
	}
private:
	friend class boost::serialization::access;

	template <class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& attrName;
		ar& dataType;
		ar& length;
		ar& attrType;
	}
	utils::string attrName;
	int dataType;
	int length;
	int attrType;
};


class Index
{
public:
	Index()
	{}
	Index(utils::string name, utils::string attrName, int keyType, int keyLen, int rank)
		: attrName(attrName)
		, name(name)
		, keyCount(keyCount)
		, level(-1)
		, nodeCount(0)
		, leafHead(-1)
		, keyType(keyType)
		, keyLen(keyLen)
		, rank(rank)
		, rubbish(rubbish)
		, maxCount(0)
	{
	}
	utils::string getAttrName()
	{
		return attrName;
	}
	int getKeyType()
	{
		return keyType;
	}
	int getKeyLen()
	{
		return keyLen;
	}
	int getRank()
	{
		return rank;
	}
	int getRoot()
	{
		return root;
	}
	int getLeafHead()
	{
		return leafHead;
	}
	int getKeyCount()
	{
		return keyCount;
	}
	int getLevel()
	{
		return level;
	}
	int getNodeCount()
	{
		return nodeCount;
	}
	utils::string getName()
	{
		return name;
	}
	void setRoot(int root)
	{
		this->root = root;
	}
	int setLeafHead(int leafHead)
	{
		this->leafHead = leafHead;
	}
	void setLevel(int level)
	{
		this->level = level;
	}
	void setNodeCount(int nodeCount)
	{
		this->nodeCount = nodeCount;
	}
	
	int increaseMaxCount()
	{
		return maxCount;
	}
	int increaseKeyCount()
	{
		return keyCount++;
	}
	int increaseNodeCount()
	{
		nodeCount++;
	}
	int increaseLevel()
	{
		return level++;
	}
	int decreaseKeyCount()
	{
		return keyCount--;
	}
	int decreaseNodeCount()
	{
		return nodeCount;
	}
	int decreaseLevel()
	{
		return level--;
	}
private:
	friend class boost::serialization::access;

	template <class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& maxCount;
		ar& attrName;
		ar& name;
		ar& keyLen;
		ar& keyType;
		ar& rank;
		ar& rubbish;
		ar& root;
		ar& leafHead;
		ar& keyCount;
		ar& level;
		ar& nodeCount;
	}
	int maxCount;
	utils::string attrName;
	utils::string name;
	int keyLen;
	int keyType;
	int rank;
	int rubbish;
	int root;
	int leafHead;
	int keyCount;
	int level;
	int nodeCount;
};