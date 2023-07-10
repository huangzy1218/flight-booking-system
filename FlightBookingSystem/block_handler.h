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
	// �ܴ�С
	int bSize;
	// ���ô�С���ѷ���Ŀ��С��
	int bCount;
	utils::string path;
	BlockInfo* add(BlockInfo* block);
};