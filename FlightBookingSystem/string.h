#pragma once
#include <iostream>
#include <cassert>
#include "algorithm.h"
#pragma warning (disable: 4996)

// 创建一个命名空间
namespace utils
{
	class string
	{
	public:
		// 迭代器
		typedef char* iterator;
		typedef const char* const_iterator;
		/* 返回一个迭代器到开头 */
		const_iterator begin() const
		{
			return _str;
		}
		/* 返回一个迭代器到末尾 */
		const_iterator end() const
		{
			return _str + _size;
		}
		/* 返回一个迭代器到字符串开头 */
		iterator begin()
		{
			return _str;
		}
		/* 返回一个迭代器到字符串末尾 */
		iterator end()
		{
			return _str + _size;
		}
		/* 构造函数 */
		string(const char* str = "");
		/* 交换函数 */
		void swap(string& s);
		/* 复制构造函数 */
		string(const string& s);
		/* 赋值运算符重载 */
		string operator=(string& s);
		/* 析构函数 */
		~string();
		/* 获取大小 */
		size_t size() const
		{
			return _size;
		}
		/* 获取容量 */
		size_t capacity() const
		{
			return _capacity;
		}
		/* 获取C字符串 */
		const char* c_str()
		{
			return _str;
		}
		/* []重载 */
		char& operator[](size_t pos)
		{
			// 判断是否越界
			assert(pos < _size);
			return _str[pos];
		}
		const char& operator[](size_t pos) const
		{
			assert(pos < _size);
			return _str[pos];
		}
		/* 反转 */
		void reserve(size_t n);
		/* 改变存储的字符数 */
		void resize(size_t n, char ch = '\0');
		/* 在末尾添加字符 */
		void push_back(char ch);
		/* 在末尾添加字符串 */
		void append(char* str);
		/* +=运算符重载 */
		string& operator+=(const string& other);
		/* 查找ch第一次出现位置  */
		size_t find(char ch);
		/* 在pos位查找str首次出现位置 */
		size_t find(char* str, size_t pos = 0);
		/* 查找ch最后一次出现位置 */
		size_t rfind(char ch);
		/* 在pos位置查找str最后一次出现位置 */
		size_t rfind(char* str, size_t pos = 0);
		/* 清空所有字符 */
		void clear()
		{
			*_str = '\0';
		}
		/* 截取子串 */
		string substr(size_t pos = 0, size_t count = npos);
	private:
		char* _str;
		size_t _size;
		size_t _capacity;
		static const size_t npos = -1;
	};

	/* 构造函数 */
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

	/* 复制构造函数 */
	string::string(const string& s)
		:_str(nullptr)
		, _size(0)
		, _capacity(0)
	{
		string tmp(s._str);
		swap(tmp);
	}

	/* 赋值运算符重载 */
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
	
	/* 析构函数 */
	string::~string()
	{
		delete _str;
		_str = nullptr;
		_size = 0;
		_capacity = 0;
	}

	/* 储备存储空间 */
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

	/* 改变存储的字符数 */
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

	/* 在末尾添加字符 */
	void string::push_back(char ch)
	{
		if (_size == _capacity)
		{
			// 扩容为2倍
			reserve(_capacity == 0 ? 4 : 2 * _capacity);
		}
		_str[_size] = ch;
		_size++;
		_str[_size] = '\0';
	}

	/* 在末尾添加字符串 */
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

	/* +=运算符重载 */
	string& string::operator+=(const string& other)
	{
		append(other._str);
		return *this;
	}

	/* 查找ch第一次出现位置  */
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

	/* 在pos位查找str首次出现位置 */
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

	/* 查找ch最后一次出现位置 */
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

	/* 在pos位置查找str最后一次出现位置 */
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

	/* 截取子串 */
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

