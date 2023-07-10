#pragma once

#include "file_info.h"
#include "commons.h"

class BlockInfo
{
public:
	BlockInfo(int num)
		: dirty(false)
		, next(nullptr)
		, file(nullptr)
		, age(0)
		, blockNum(num)
	{
		data = new char[BLOCK_SIZE];
	}

	virtual ~BlockInfo()
	{
		delete[] data;
	}
	FileInfo* getFile()
	{
		return file;
	}
	void setFile(FileInfo* file)
	{
		this->file = file;
	}
	int getBlockNum()
	{
		return blockNum;
	}
	void setBlockNum(int num)
	{
		blockNum = num;
	}
	char* getData()
	{
		return data;
	}
	void setData(char* data)
	{
		this->data = data;
	}
	bool getDirty()
	{
		return dirty;
	}
	long getAge()
	{
		return age;
	}
	void setAge(long age)
	{
		this->age = age;
	}
	void setDirty(bool dirty)
	{
		this->dirty = dirty;
	}
	BlockInfo* getNext()
	{
		return next;
	}
	void setNext(BlockInfo* next)
	{
		this->next = next;
	}
	void increaseAge()
	{
		++age;
	}
	void resetAge()
	{
		age = 0;
	}
	void setPreBlockNum(int num)
	{
		*(int*)(data) = num;
	}
	int getPreBlockNum()
	{
		return *(int*)(data);
	}
	int setNextBlockNum(int num)
	{
		*(int*)(data + 4) = num;
	}
	int getNextBlockNum()
	{
		return *(int*)(data + 4);
	}
	void setRecordCount(int count)
	{
		*(int*)(data + 8) = count;
	}
	int getRecordCount()
	{
		return *(int*)(data + 8);
	}
	void decreaseRecordCount()
	{
		*(int*)(data + 8) = *(int*)(data + 8) - 1;
	}
	char* getContentAddress()
	{
		return data + 12;
	}
	void readInfo(utils::string path);
	void writeInfo(utils::string path);
private:
	FileInfo* file;
	int blockNum;
	char* data;
	bool dirty;
	// 区块上次访问距当前距离
	long age;
	BlockInfo* next;
};