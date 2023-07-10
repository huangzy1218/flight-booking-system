#include "block_handler.h"

// ��������
BlockHandler::~BlockHandler()
{
	BlockInfo* p = firstBlock;
	while (bCount > 0)
	{
		BlockInfo* pNext = p->getNext();
		// ɾ����һ����
		delete p;
		p = pNext;
		bCount--;
	}
}

// ��block������¿�
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

// ��ÿ��ÿ�
BlockInfo* BlockHandler::getUsableBlock()
{
	// �޿��ÿ�
	if (bCount == 0)
	{
		return nullptr;
	}

	BlockInfo* p = firstBlock->getNext();
	firstBlock->setNext(p->getNext());
	// ���ÿ�����1
	bCount--;
	p->resetAge();
	// ��p�������н��
	p->setNext(nullptr);
	return p;
}

// �ͷſ飬�����ٴ���������
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