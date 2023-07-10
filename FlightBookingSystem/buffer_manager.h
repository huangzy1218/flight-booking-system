#pragma once

#include "string.h"
#include "block_handler.h"
#include "file_handler.h"

class BufferManager
{
public:
	// 构造函数
	BufferManager(utils::string p)
		: bhandler(new BlockHandler(p))
		, fhandler(new FileHandler(p))
		, path(p)
	{}
	// 析构函数
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
	// 区块管理，空闲区块链
	BlockHandler* bhandler;
	// 文件管理，文件链
	FileHandler* fhandler;
	utils::string path;

	BlockInfo* getUsableBlock();
};