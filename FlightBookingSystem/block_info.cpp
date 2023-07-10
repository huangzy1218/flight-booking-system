#include "block_info.h"
#include "commons.h"
#include <fstream>
#include <ios>

void BlockInfo::readInfo(utils::string path)
{
	path += file->getDbName() + "/" + file->getFileName();

	if (file->getType() == FORMAT_INDEX)
	{
		path += ".index";
	}
	else
	{
		path += ".records";
	}

	std::ifstream ifs(path.c_str(), std::ios::binary);
	// 将读写位置移动到当前块
	ifs.seekg(blockNum * BLOCK_SIZE);
	// 读取内容到data
	ifs.read(data, BLOCK_SIZE);
	// 关闭文件流
	ifs.close();
}

void BlockInfo::writeInfo(utils::string path)
{
	path += file->getDbName() + file->getFileName();

	if (file->getType() == FORMAT_INDEX)
	{
		path += ".index";
	}
	else
	{
		path += ".records";
	}

	std::ofstream ofs(path.c_str(), std::ios::binary);
	// 将读写位置移动到当前块
	ofs.seekp(blockNum * BLOCK_SIZE);
	// 将data内容写入文件
	ofs.write(data, BLOCK_SIZE);
	// 关闭文件流
	ofs.close();
}

