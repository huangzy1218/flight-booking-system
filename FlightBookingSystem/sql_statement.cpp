#include "sql_statement.h"

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
TKey(const TKey& t)
	:
{
	keyType = t.
}