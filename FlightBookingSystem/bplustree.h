#pragma once

#include "string.h"
#include "sql_statement.h"

class BufferManager;


struct FindNodeParam
{
	BPlusTree* pNode;
	int index;
	bool flag;
};

class BPlusTree
{
public:
	BPlusTree(Index* idx, BufferManager* bm,
		CatalogManager* cm, utils::string dbName)
		: idx(idx)
		, cm(cm)
		, bm(bm)
		, degree(2 * idx->getRank() + 1)
		, dbName(dbName)
	{}
	~BPlusTree()
	{}

	Index* getIdx()
	{
		return idx;
	}
	int getDegree()
	{
		return degree;
	}
	BufferManager* getBM()
	{
		return bm;
	}
	CatalogManager* getCM()
	{
		return cm;
	}
	utils::string getDbName()
	{
		return dbName;
	}
	bool add(TKey& key, int blockNum, int offset);
	bool adjustAfterAdd(int node);
	
	bool remove(TKey key);
	bool adjustAfterRemove(int node);

	FindNodeParam search(int node, TKey& key);
	FindNodeParam searchBranch(int node, TKey& key);

	BPlusTreeNode* getNode(int num);

	int getVal(TKey key);
	int getNewBlock()
	{
		return idx->increaseMaxCount();
	}

	void print();
	void printNode(int num);
private:
	Index* idx;
	int degree;
	BufferManager* bm;
	CatalogManager* cm;
	utils::string dbName;
};

class BPlusTreeNode
{
public:
	BPlusTreeNode(bool isNew, BPlusTree* tree, int blockNum, bool newLeaf = false);
	~BPlusTreeNode()
	{}
	int getBlockNum()
	{
		return blockNum;
	}
	TKey getKeys(int i);
	int getValues(int i);
	int getNextLeaf();
	int getParent();
	int getNodeType();
	int getCount();
	bool getIsLeaf();

	void setKeys(int i, TKey key);
	void setValues(int i, int value);
	void setNextLeaf(int nextLeaf);
	void setParent(int parent);
	void setNodeType(int nodeType);
	void setCount(int count);
	void setIsLeaf(bool isLeaf);
	void getBuffer();
	bool search(TKey key, int& index);
	int add(TKey& key);
	int add(TKey& key, int& val);
	BPlusTreeNode* split(TKey& key);

	bool isRoot()
	{
		if (getParent() != -1)
		{
			return false;
		}
		return true;
	}
	bool removeAt(int index);
	
	void print();
private:
	BPlusTree* tree;
	int blockNum;
	int rank;
	char* buffer;
	bool isLeaf;
	bool isNewNode;
};