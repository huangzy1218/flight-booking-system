#include "sql_statement.h"

#include "string.h"
#include "vector.h"
#include "cstring.h"
// 构造函数
TKey::TKey(int keyType, int length)
	: keyType(keyType)
{
	if (keyType == T_CHAR)
	{
		this->length = length;
	}
	else
	{
		length = 4;
	}
	key = new char[length];
}

// 拷贝构造函数
TKey::TKey(const TKey& t)
	: keyType(t.keyType)
	, length(t.length)
{
	key = new char[length];
	memcpy(key, t.key, length);
}

void TKey::readValue(const char* content)
{
	switch (keyType)
	{
	case T_INT:
		int a = utils::atoi(content);
		memcpy(key, &a, length);
		break;
	case T_FLOAT:
		float a = utils::atof(content);
		memcpy(key, &a, length);
		break;
	case T_CHAR:
		memcpy(key, content, length);
		break;
	default:
		memcpy(key, content, length);
	}
}

void TKey::readValue(utils::string str)
{
	switch (keyType)
	{
	case T_INT:
		int a = utils::atoi(str.c_str());
		memcpy(key, &a, length);
		break;
	case T_FLOAT:
		float a = utils::atof(str.c_str());
		memcpy(key, &a, length);
		break;
	case T_CHAR:
		memcpy(key, str.c_str(), length);
		break;
	default:
		memcpy(key, str.c_str(), length);
	}
}

TKey::~TKey()
{
	if (key != nullptr)
	{
		delete[] key;
	}
}

bool TKey::operator<(const TKey t)
{
	switch (t.keyType)
	{
	case T_INT:
		return *(int*)key < *(int*)t.key;
	case T_FLOAT:
		return *(float*)key < *(float*)key;
	case T_CHAR:
		return (utils::strcmp(key, t.key) < 0);
	default:
		return false;
	}
}
bool TKey::operator>(const TKey t)
{
	switch (t.keyType)
	{
	case T_INT:
		return *(int*)key > *(int*)t.key;
	case T_FLOAT:
		return *(float*)key > *(float*)key;
	case T_CHAR:
		return (utils::strcmp(key, t.key) > 0);
	default:
		return false;
	}
}
bool TKey::operator<=(const TKey t)
{
	return !operator>(t);
}

bool TKey::operator>=(const TKey t)
{
	return !operator<(t);
}

bool TKey::operator==(const TKey t)
{
	switch (t.keyType)
	{
	case T_INT:
		return *(int*)key == *(int*)t.key;
	case T_FLOAT:
		return *(float*)key == *(float*)key;
	case T_CHAR:
		return (utils::strcmp(key, t.key) == 0);
	default:
		return false;
	}
}
bool TKey::operator!=(const TKey t)
{
	switch (t.keyType)
	{
	case T_INT:
		return *(int*)key != *(int*)t.key;
	case T_FLOAT:
		return *(float*)key != *(float*)key;
	case T_CHAR:
		return (utils::strcmp(key, t.key) != 0);
	default:
		return false;
	}
}
