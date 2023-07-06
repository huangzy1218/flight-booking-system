#pragma once
#include "commons.h"
#include "string.h"

class BlockInfo;

class FileInfo
{
public:
	// �޲ι���
	FileInfo();
	// ���캯��
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
	// �ļ���
	utils::string fileName;
	// �ļ��еļ�¼��
	size_t recordAmount;
	// �ļ��еļ�¼����
	size_t recordLength;
	// ָ���ļ��еĵ�һ����
	BlockInfo* firstBlock;
	// ָ����һ���ļ���ָ��
	FileInfo* next;

};
