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
	// ����дλ���ƶ�����ǰ��
	ifs.seekg(blockNum * BLOCK_SIZE);
	// ��ȡ���ݵ�data
	ifs.read(data, BLOCK_SIZE);
	// �ر��ļ���
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
	// ����дλ���ƶ�����ǰ��
	ofs.seekp(blockNum * BLOCK_SIZE);
	// ��data����д���ļ�
	ofs.write(data, BLOCK_SIZE);
	// �ر��ļ���
	ofs.close();
}

