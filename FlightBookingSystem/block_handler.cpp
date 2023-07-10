#include "block_handler.h"

// 析构函数
BlockHandler::~BlockHandler()
{
	BlockInfo* p = firstBlock;
	while (bCount > 0)
	{
		BlockInfo* pNext = p->getNext();
		// 删除第一个块
		delete p;
		p = pNext;
		bCount--;
	}
}

// 在block后插入新块
BlockInfo* BlockHandler::BlockHandler::add(BlockInfo* block)
{
	BlockInfo* adder = new BlockInfo(0);
	adder->setNext(block->getNext());
	block->setNext(adder);
	bCount++;
	if (bCount == bSize)
	{
		return adder;
	}
	else
	{
		return add(adder);
	}
}

// 获得可用块
BlockInfo* BlockHandler::getUsableBlock()
{
	// 无可用块
	if (bCount == 0)
	{
		return nullptr;
	}

	BlockInfo* p = firstBlock->getNext();
	firstBlock->setNext(p->getNext());
	// 可用块数减1
	bCount--;
	p->resetAge();
	// 将p从链表中解出
	p->setNext(nullptr);
	return p;
}

// 释放块，将块再次链入链表
void BlockHandler::freeBlock(BlockInfo* block)
{
	if (bCount == 0)
	{
		firstBlock = block;
		//block->setNext(block);
		block->setNext(nullptr);
	}
	else
	{
		block->setNext(firstBlock->getNext());
		firstBlock->setNext(block);
	}
	bCount++;
}