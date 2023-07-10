#pragma once

#include "string.h"
#include "vector.h"
#include "buffer_manager.h"
#include "block_info.h"
#include "catalog_manager.h"
#include "exceptions.h"
#include "sql_statement.h"

class RecordManager
{
public:
	RecordManager(CatalogManager* cm, BufferManager* bm, utils::string db)
		: cm(cm)
		, bm(bm)
		, dbName(db)
	{}
	~RecordManager()
	{}
	void insert(SQLInsert& sql);
	void select(SQLSelect& sql);
	void remove(SQLDelete& sql);
	void update(SQLUpdate& sql);

	BlockInfo* getBlockInfo(Table* tb, int blockNum);
	utils::vector<TKey> getRecord(Table* tb, int blockNum, int offset);
	void deleteRecord(Table* tb, int blockNum, int offset);
	void updateRecord(Table* tb, int blockNum, int offset,
		utils::vector<int>& indices, utils::vector<TKey>& values);
	bool satisfyWhere(Table* tb, utils::vector<TKey> keys, SQLWhere where);
private:
	BufferManager* bm;
	CatalogManager* cm;
	utils::string dbName;
};