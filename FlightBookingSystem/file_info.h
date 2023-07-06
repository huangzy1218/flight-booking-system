#pragma once
#include "commons.h"
#include "string.h"

class BlockInfo;

class FileInfo
{
public:
	// 无参构造
	FileInfo();
	// 构造函数
	FileInfo(utils::string db, int tp, utils::string file, size_t rea,
		size_t rel, BlockInfo* fb, FileInfo* next);
	~FileInfo() 
	{}
	utils::string getDbName()
	{
		return dbName;
	}
	int getType()
	{
		return type;
	}
	utils::string getFileName()
	{
		return fileName;
	}
	BlockInfo* getFirstBlock()
	{
		return firstBlock;
	}
	FileInfo* getNext()
	{
		return next;
	}
	void setNext(FileInfo* fp)
	{
		next = fp;
	}
	void IncreaseRecordAmmount()
	{
		recordAmount++;
	}
	void IncreaseRecordLength()
	{
		recordLength += 4096;
	}
private:
	utils::string dbName;
	int type;
	// 文件名
	utils::string fileName;
	// 文件中的记录数
	size_t recordAmount;
	// 文件中的记录长度
	size_t recordLength;
	// 指向文件中的第一个块
	BlockInfo* firstBlock;
	// 指向下一个文件的指针
	FileInfo* next;

};
