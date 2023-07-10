#pragma once

#include "string.h"
#include "block_info.h"
#include "file_info.h"

class FileHandler
{
public:
	// ���캯��
	FileHandler(utils::string p)
		: firstFile(new FileInfo())
		, path(p)
	{}
	// ��������
	~FileHandler();
	// ��ȡ�ļ���Ϣ
	FileInfo* getFileInfo(utils::string dbName, utils::string tbName, int fileType);
	// ��ȡ����Ϣ
	BlockInfo* getBlockInfo(FileInfo* file, int blockPos);
	// ��ӿ���Ϣ
	void addBlockInfo(BlockInfo* block);
	// ����ʹ��ʱ��
	void increaseAge();
	// ���տ�
	BlockInfo* recycleBlock();
	// ����ļ���Ϣ
	void addFileInfo(FileInfo* file);
	// д�����
	void writeToDik();

private:
	FileInfo* firstFile;
	utils::string path;
};