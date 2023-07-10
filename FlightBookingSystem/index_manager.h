#pragma once

#include "string.h"
#include "catalog_manager.h"
#include "sql_statement.h"
#include "bplustree.h"

// Êý¾Ý¿âÄ¿Â¼
class IndexManager
{
public:
	IndexManager(CatalogManager* cm, BufferManager* bm, utils::string db)
		: cm(cm)
		, bm(bm)
		, dbName(db)
	{}
	~IndexManager()
	{}
	void createIndex(SQLCreateIndex& sql);
private:
	BufferManager* bm;
	CatalogManager* cm;
	utils::string dbName;
};