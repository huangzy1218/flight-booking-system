#include "file_info.h"

FileInfo::FileInfo()
	: dbName("")
	, type(0)
	, fileName("")
	, recordAmount(0)
	, recordLength(0)
	, firstBlock(nullptr)
	, next(nullptr)
{}
// ¹¹Ôìº¯Êý
FileInfo::FileInfo(utils::string db, int tp, utils::string file, size_t rea,
	size_t rel, BlockInfo* fb, FileInfo* next)
	: dbName(db)
	, type(tp)
	, fileName(file)
	, recordAmount(rea)
	, recordLength(rel)
	, firstBlock(fb)
	, next(next)
{}