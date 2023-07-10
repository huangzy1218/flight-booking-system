#pragma once

#include "string.h"
#include "block_handler.h"
#include "file_handler.h"

class BufferManager
{
public:
	// ���캯��
	BufferManager(utils::string p)
		: bhandler(new BlockHandler(p))
		, fhandler(new FileHandler(p))
		, path(p)
	{}
	// ��������
	~BufferManager()
	{
		delete bhandler;
		delete fhandler;
	}
	BlockInfo* getFileBlock(utils::string dbName, utils::string tbName,
		int fielType, int blockNum);
	void writeBlock(BlockInfo* block);
	void writeToDisk();
private:
	// �����������������
	BlockHandler* bhandler;
	// �ļ������ļ���
	FileHandler* fhandler;
	utils::string path;

	BlockInfo* getUsableBlock();
};