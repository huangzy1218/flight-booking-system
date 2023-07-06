#pragma once

#include "string.h"
#include "vector.h"
#include "commons.h"
#include <iostream>

class TKey;
class Table;
class CatalogManager;
class Table;
class Index;
class Attribute;

std::ostream& operator<<(std::ostream& out, const TKey& object);

struct SQLValue
{
	int dataType;
	utils::string value;
};

struct SQLWhere
{
	utils::string key;
	int signType;
	utils::string value;
};

struct SQLKeyValue
{
	utils::string key;
	utils::string value;
};

class TKey
{
public:
	// 复制构造函数
	TKey(int keyType, int length);

	// 构造函数
	TKey(const TKey& t);

	// 读取数据
	void readValue(const char* content);
	void readValie(utils::string content);

	// 析构函数
	~TKey();
	// 输出运算符重载
	friend std::ostream& operator<<(std::ostream& out, const TKey& object);

	// 比较运算符重载
	bool operator<(const TKey t);
	bool operator>(const TKey t);
	bool operator<=(const TKey t);
	bool operator>=(const TKey t);
	bool operator==(const TKey t);
	bool operator!=(const TKey t);

private:
	int keyType;
	char* key;
	size_t length;
};


class SQL 
{
public:
	// 无参构造
	SQL()
		: sqlType(-1) 
	{}
	// 有参构造
	SQL(int sqlType)
		: sqlType(sqlType)
	{}
	// 析构函数
	virtual ~SQL() {}
	int getSqlType()
	{
		return sqlType;
	}
	void setSqlType(int sqlType)
	{
		this->sqlType = sqlType;
	}
	virtual void parse(utils::vector<utils::string> sqls) = 0;
	int parseDataType(utils::vector<utils::string> sqls, Attribute& attr,
		size_t pos);

protected:
	int sqlType;
};

class SQLCreateDataBase : public SQL
{
public:
	SQLCreateDataBase(utils::vector<utils::string> sqls);
	utils::string getDbName()
	{
		return dbName;
	}
	void setDbName(utils::string dbName)
	{
		dbName = dbName;
	}
	void parse(utils::vector<utils::string> sqls);
private:
	utils::string dbName;
};

class SQLDropDatabase : public SQL
{
public:
	SQLDropDatabase(utils::vector<utils::string> sqls);
	utils::string getDbName()
	{
		return dbName;
	}
	void setDbName(utils::string dbName)
	{
		dbName = dbName;
	}
	void parse(utils::vector<utils::string> sqls);
private:
	utils::string dbName;
};


class SQLCreateTable : public SQL
{
public:
	SQLCreateTable(utils::vector<utils::string> sqls);
	utils::string getTbName()
	{
		return tbName;
	}
	void setTbName(utils::string tbName)
	{
		this->tbName = tbName;
	}
	utils::vector<Attribute> getAttrs()
	{
		return attrs;
	}
	utils::vector<Attribute> setAttrs()
	{
		this->attrs = attrs;
	}
	void parse(utils::vector<utils::string> sqls);
private: 
	utils::string tbName;
	utils::vector<Attribute> attrs;
};


class SQLDropTable : public SQL
{
public:
	SQLDropTable(utils::vector<utils::string> sqls);
	utils::string getTbName()
	{
		return tbName;
	}
	void setTbName(utils::string tbName)
	{
		this->tbName = tbName;
	}
	void parse(utils::vector<utils::string> sqls);

private:
	utils::string tbName;
};


class CreateIndex : public SQL
{
public:
	SQLCreateIndex(utils::vector<utils::string> sqls);
	void parse(utils::vector<utils::string> sqls);
	utils::string getIdxName()
	{
		return idxName;
	}
	utils::string getTbName()
	{
		return tbName;
	}
	utils::string getColName()
	{
		return colName;
	}
private:
	utils::string idxName;
	utils::string tbName;
	utils::string colName;
};

class SQLDropIndex : public SQL
{
public:
	SQLDropIndex(utils::vector<utils::string> sqls);
	utils::string getIdxName()
	{
		return idxName;
	}
	void setIdxName(utils::string idxName)
	{
		this->idxName = idxName;
	}
	void parse(utils::vector<utils::string> sqls);
private:
	utils::string idxName;
};

class SQLUse : public SQL
{
public:
	SQLUse(utils::vector<utils::string> sqls);
	utils::string getDbName()
	{
		return dbName;
	}
	void setDbName(utils::string dbName)
	{
		this->dbName = dbName;
	}
	void parse(utils::vector<utils::string> sqls);
private:
	utils::string dbName;
};

class SQLInsert : public SQL
{
public: 
	SQLInsert(utils::vector<utils::string> sqls);
	void parse(utils::vector<utils::string> sqls);
	utils::string getTbName()
	{
		return tbName;
	}
	utils::vector<SQLValue>& getValues()
	{
		return values;
	}
private:
	utils::string tbName;
	utils::vector<SQLValue> values;
};


class SQLExec : public SQL
{
public:
	SQLExec(utils::vector<utils::string> sqls);
	void parse(utils::vector<utils::string> sqls);
	utils::string getFileName()
	{
		return fileName;
	}
private:
	utils::string fileName;
};


class SQLSelect : public SQL
{
public:
	SQLSelect(utils::vector<utils::string> sqls);
	void parse(utils::vector<utils::string> sqls);
	utils::string getTbName()
	{
		return tbName;
	}
	utils::vector<SQLWhere>& getWheres()
	{
		return wheres;
	}
private:
	utils::string tbName;
	utils::vector<SQLWhere> wheres;
};

class SQLDelete : public SQL
{
public:
	SQLDelete(utils::vector<utils::string> sqls);
	void parse(utils::vector<utils::string> sqls);
	utils::string getTbName()
	{
		return tbName;
	}
	utils::vector<SQLWhere>& getWheres()
	{
		return wheres;
	}
private:
	utils::string tbName;
	utils::vector<SQLWhere> wheres;
};

class SQLUpdate : public SQL
{
public:
	SQLUpdate(utils::vector<utils::string> sqls);
	void parse(utils::vector<utils::string> sqls);
	utils::string getTbName()
	{
		return tbName;
	}
	utils::vector<SQLWhere>& getWheres()
	{
		return wheres;
	}
	utils::vector<SQLKeyValue>& getKeyValues()
	{
		return keyValues;
	}
private:
	utils::string tbName;
	utils::vector<SQLWhere> wheres;
	utils::vector<SQLKeyValue> keyValues;
};


