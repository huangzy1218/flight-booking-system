#pragma once

#include "block_info.h"

class BlockHandler
{
public:
	BlockHandler(utils::string p)
		: firstBlock(new BlockInfo(0))
		, bSize(300)
		, bCount(0)
		, path(p)
	{
		add(firstBlock);
	}

	~BlockHandler();

	int getBCount()
	{
		return bCount;
	}
	BlockInfo* getUsableBlock();

	void freeBlock(BlockInfo* block);
private:
	BlockInfo* firstBlock;
	// 总大小
	int bSize;
	// 可用大小（已分配的块大小）
	int bCount;
	utils::string path;
	BlockInfo* add(BlockInfo* block);
};