#include "sql_statement.h"

// ���캯��
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

// �������캯��
TKey(const TKey& t)
	:
{
	keyType = t.
}