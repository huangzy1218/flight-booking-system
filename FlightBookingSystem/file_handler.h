#pragma once

#include "string.h"
#include "block_info.h"
#include "file_info.h"

class FileHandler
{
public:
	// 构造函数
	FileHandler(utils::string p)
		: firstFile(new FileInfo())
		, path(p)
	{}
	// 析构函数
	~FileHandler();
	// 获取文件信息
	FileInfo* getFileInfo(utils::string dbName, utils::string tbName, int fileType);
	// 获取块信息
	BlockInfo* getBlockInfo(FileInfo* file, int blockPos);
	// 添加块信息
	void addBlockInfo(BlockInfo* block);
	// 增加使用时间
	void increaseAge();
	// 回收块
	BlockInfo* recycleBlock();
	// 添加文件信息
	void addFileInfo(FileInfo* file);
	// 写入磁盘
	void writeToDik();

private:
	FileInfo* firstFile;
	utils::string path;
};