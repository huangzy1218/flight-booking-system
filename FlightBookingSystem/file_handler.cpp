#include "file_handler.h"
#include "commons.h"
#include <fstream>

FileHandler::~FileHandler()
{
	writeToDik();
	FileInfo* fp = firstFile;
	while (fp != nullptr)
	{
		FileInfo* fpn = fp->getNext();
		BlockInfo* bp = fp->getFirstBlock();
		while (bp != nullptr)
		{
			BlockInfo* bpn = bp->getNext();
			delete bp;
			bp = bpn;
		}
		delete fp;
		fp = fpn;
	}
}

void FileHandler::addFileInfo(FileInfo* file)
{
	FileInfo* p = firstFile;
	if (p == nullptr)
	{
		p = file;
	}
	else
	{
		while (p->getNext() != nullptr)
		{
			p = p->getNext();
		}
		// ���ļ���ӵ���β
		p->setNext(file);
	}
}

// ��ȡ�ļ���Ϣ
FileInfo* FileHandler::getFileInfo(utils::string dbName, utils::string tbName, int fileType)
{
	FileInfo* p = firstFile;
	while (p != nullptr)
	{
		if (p->getDbName() == dbName && p->getType() == fileType
			&& p->getFileName() == tbName)
		{
			return p;
		}
		p = p->getNext();
	}
	return nullptr;
}

// ��ȡ����Ϣ
BlockInfo* FileHandler::getBlockInfo(FileInfo* file, int blockPos)
{
	BlockInfo* p = file->getFirstBlock();
	while (p != nullptr)
	{
		if (p->getBlockNum() == blockPos)
		{
			return p;
		}
		p = p->getNext();
	}
	return nullptr;
}

// ��ӿ���Ϣ
void FileHandler::addBlockInfo(BlockInfo* block)
{
	BlockInfo* p = block->getFile()->getFirstBlock();
	if (p == nullptr)
	{
		block->getFile()->setFirstBlock(block);
	}
	else
	{
		while (p->getNext() != nullptr)
		{
			p = p->getNext();
		}
		// ����β���
		p->setNext(block);
	}
	block->getFile()->increaseRecordAmmount();
	block->getFile()->increaseRecordLength();
}


void FileHandler::increaseAge()
{
	FileInfo* fp = firstFile;
	while (fp != nullptr)
	{
		BlockInfo* bp = fp->getFirstBlock();
		while (bp != nullptr)
		{
			bp->increaseAge();
			bp = bp->getNext();
		}
		fp = fp->getNext();
	}
}

// ���տ�
BlockInfo* FileHandler::recycleBlock()
{
	FileInfo* fp = firstFile;
	// �ɽ���ǰһ����㣬����ɾ������
	BlockInfo* oldestBefore = nullptr;
	BlockInfo* oldest = fp->getFirstBlock();

	while (fp != nullptr)
	{
		BlockInfo* bpBefore = nullptr;
		BlockInfo* bp = fp->getFirstBlock();
		while (bp != nullptr)
		{
			if (bp->getAge() > oldest->getAge())
			{
				oldestBefore = bpBefore;
				oldest = bp;
			}
			bpBefore = bp;
			bp = bp->getNext();
		}
		fp = fp->getNext();
	}
	
	if (oldest->getDirty())
	{
		oldest->writeInfo();
	}
	if (oldestBefore == nullptr)
	{
		oldest->getFile()->setFirstBlock(oldest->getNext());
	}
	else
	{
		oldestBefore->setNext(oldest->getNext());
	}
}

void FileHandler::writeToDik()
{
	FileInfo* fp = firstFile;
	
	while (fp != nullptr)
	{
		BlockInfo* bp = fp->getFirstBlock();
		while (bp != nullptr)
		{
			if (bp->getDirty())
			{
				bp->writeInfo(path);
				bp->setDirty(false);
				bp = bp->getNext();
			}
			bp = bp->getNext();
		}
		fp = fp->getNext();
	}
}