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
		// 该区块存在
		if (block != nullptr)
		{
			return block;
		}
		else
		{
			// 不存在则分配可用块
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
		// 使用LRU取出块
		return fhandler->recycleBlock();
	}
}

void BufferManager::writeBlock(BlockInfo* block)
{
	// 不执行实际写任务，只设置脏区 
	block->setDirty(true);
}

void BufferManager::writeToDisk()
{
	// 执行写回文件操作
	fhandler->writeToDik();
}
