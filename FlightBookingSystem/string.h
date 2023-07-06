#pragma once
#include <iostream>
#include <cassert>
#include "algorithm.h"
#pragma warning (disable: 4996)

// ����һ�������ռ�
namespace utils
{
	class string
	{
	public:
		// ������
		typedef char* iterator;
		typedef const char* const_iterator;
		/* ����һ������������ͷ */
		const_iterator begin() const
		{
			return _str;
		}
		/* ����һ����������ĩβ */
		const_iterator end() const
		{
			return _str + _size;
		}
		/* ����һ�����������ַ�����ͷ */
		iterator begin()
		{
			return _str;
		}
		/* ����һ�����������ַ���ĩβ */
		iterator end()
		{
			return _str + _size;
		}
		/* ���캯�� */
		string(const char* str = "");
		/* �������� */
		void swap(string& s);
		/* ���ƹ��캯�� */
		string(const string& s);
		/* ��ֵ��������� */
		string operator=(string& s);
		/* �������� */
		~string();
		/* ��ȡ��С */
		size_t size() const
		{
			return _size;
		}
		/* ��ȡ���� */
		size_t capacity() const
		{
			return _capacity;
		}
		/* ��ȡC�ַ��� */
		const char* c_str()
		{
			return _str;
		}
		/* []���� */
		char& operator[](size_t pos)
		{
			// �ж��Ƿ�Խ��
			assert(pos < _size);
			return _str[pos];
		}
		const char& operator[](size_t pos) const
		{
			assert(pos < _size);
			return _str[pos];
		}
		/* ��ת */
		void reserve(size_t n);
		/* �ı�洢���ַ��� */
		void resize(size_t n, char ch = '\0');
		/* ��ĩβ����ַ� */
		void push_back(char ch);
		/* ��ĩβ����ַ��� */
		void append(char* str);
		/* +=��������� */
		string& operator+=(const string& other);
		/* ����ch��һ�γ���λ��  */
		size_t find(char ch);
		/* ��posλ����str�״γ���λ�� */
		size_t find(char* str, size_t pos = 0);
		/* ����ch���һ�γ���λ�� */
		size_t rfind(char ch);
		/* ��posλ�ò���str���һ�γ���λ�� */
		size_t rfind(char* str, size_t pos = 0);
		/* ��������ַ� */
		void clear()
		{
			*_str = '\0';
		}
		/* ��ȡ�Ӵ� */
		string substr(size_t pos = 0, size_t count = npos);
	private:
		char* _str;
		size_t _size;
		size_t _capacity;
		static const size_t npos = -1;
	};

	/* ���캯�� */
	string::string(const char* str)
		: _size(strlen(str))
		, _capacity(_size)
	{
		_str = new char[_capacity + 1];
		strcpy(_str, str);
	}

	void string::swap(string& s)
	{
		utils::swap(_str, s._str);
		utils::swap(_size, s._size);
		utils::swap(_capacity, s._capacity);
	}

	/* ���ƹ��캯�� */
	string::string(const string& s)
		:_str(nullptr)
		, _size(0)
		, _capacity(0)
	{
		string tmp(s._str);
		swap(tmp);
	}

	/* ��ֵ��������� */
	string string::operator=(string& s)
	{
		if (this != &s)
		{
			string tmp(s);
			_str = new char[strlen(s._str) + 1];
			strcpy(_str, tmp._str);
			_size = s._size;
			_capacity = s._capacity;
		}
		return *this;
	}
	
	/* �������� */
	string::~string()
	{
		delete _str;
		_str = nullptr;
		_size = 0;
		_capacity = 0;
	}

	/* �����洢�ռ� */
	void string::reserve(size_t n)
	{
		if (n > _capacity)
		{
			char* tmp = new char[n + 1];
			strcpy(tmp, _str);
			delete _str;
			_str = tmp;
			_capacity = n;
		}
	}

	/* �ı�洢���ַ��� */
	void string::resize(size_t n, char ch)
	{
		if (n <= _size)
		{
			_size = n;
			_str[_size] = '\0';
		}
		else
		{
			if (n > _capacity)
			{
				reserve(n);
			}
			memset(_str + _size, ch, n - _size);
			_size = n;
			_str[_size] = '\0';
		}
	}

	/* ��ĩβ����ַ� */
	void string::push_back(char ch)
	{
		if (_size == _capacity)
		{
			// ����Ϊ2��
			reserve(_capacity == 0 ? 4 : 2 * _capacity);
		}
		_str[_size] = ch;
		_size++;
		_str[_size] = '\0';
	}

	/* ��ĩβ����ַ��� */
	void string::append(char* str)
	{
		size_t len = strlen(str);
		if (_size + len > _capacity)
		{
			reserve(_size + len);
		}
		strcat(_str, str);
		_size = _size + len;
	}

	/* +=��������� */
	string& string::operator+=(const string& other)
	{
		append(other._str);
		return *this;
	}

	/* ����ch��һ�γ���λ��  */
	size_t string::find(char ch)
	{
		for (size_t i = 0; i < _size; i++)
		{
			if (ch == *(_str + i))
			{
				return i;
			}
		}
		return string::npos;
	}

	/* ��posλ����str�״γ���λ�� */
	size_t string::find(char* substr, size_t pos)
	{
		size_t len1 = _size, len2 = strlen(substr);
		for (size_t i = 0; i <= len1 - len2; ++i)
		{
			size_t j = 0;
			for (; j < len2; j++)
			{
				if (_str[i + j] != substr[j])
				{
					break;
				}
			}
			if (j == len2)
			{
				return i;
			}
		}
		return string::npos;
	}

	/* ����ch���һ�γ���λ�� */
	size_t string::rfind(char ch)
	{
		for (size_t i = _size - 1; i >= 0; i--)
		{
			if (ch == *(_str + i))
			{
				return i;
			}
		}
		return string::npos;
	}

	/* ��posλ�ò���str���һ�γ���λ�� */
	size_t string::rfind(char* substr, size_t pos)
	{
		size_t len1 = _size, len2 = strlen(substr);
		for (size_t i = len1 - len2; i >= 0; --i)
		{
			size_t j = 0;
			for (; j < len2; j++)
			{
				if (_str[i + j] != substr[j])
				{
					break;
				}
			}
			if (j == len2)
			{
				return i;
			}
		}
		return string::npos;
	}

	/* ��ȡ�Ӵ� */
	string string::substr(size_t pos, size_t count)
	{
		string ret;
		size_t len = _size;
		if (pos >= len)
		{
			return ret;
		}
		if (pos + len > count)
		{
			len = len - pos;
		}
		ret.resize(len);
		memcpy(&ret, &this[pos], len);
		return ret;
	}
}

