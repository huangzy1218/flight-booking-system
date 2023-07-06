#pragma once
#include <assert.h>

namespace utils
{
	template <class T>
	class vector 
	{
	public:
		// 普通迭代器
		typedef T* iterator;
		// const迭代器
		typedef const T* const_iterator;
		// 返回一个指向第一个数据的普通迭代器
		iterator begin()
		{
			return _start;
		}
		// 返回一个指向第一个数据的const迭代器
		const_iterator cbegin()
		{
			return _start;
		}
		// 返回一个指向最后一个数据的下一个位置的普通迭代器
		iterator end()
		{
			return _finish;
		}
		// 返回一个指向最后一个数据的下一个位置的const迭代器
		const_iterator cend()
		{
			return _finish;
		}
		// 返回有效数据的个数
		size_t size() const
		{
			return _finish - _start;
		}
		// 返回容量大小
		size_t capacity()
		{
			return _finishstorage - _start;
		}
		// 判空
		bool empty() const
		{
			return _start == _finish;
		}
		// 获取首元素
		T& front()
		{
			return _start[0];
		}
		const T& front() const
		{
			return _start[0];
		}
		// 获取尾元素
		T& back()
		{
			return *(_finish - 1);
		}
		const T& back() const
		{
			return *(_finish - 1);
		}
		// 清空所有元素
		void clear()
		{
			_finish = _start;
		}
		// []重载
		T& operator[](size_t index)
		{
			assert(index < size());
			return _start[index];
		}
		const T& operator[](size_t index) const
		{
			assert(-1 < index < size());
			return _start[index];
		}
		// 尾插
		void push_back(const T& val);
		// 尾删
		void pop_back();
		// 调整容量
		void reserve(size_t n);
		// 调整有效数据大小
		void resize(size_t n, const T& val = T());
		// 构造空对象
		vector();
		// 构造并初始化
		vector(size_t n, const T val = T());
		// 拷贝构造
		vector(const vector<T>& v);
		// 析构函数
		~vector();
		// 赋值重载
		vector<T>& operator=(vector<T> v);
		// 交换
		void swap(vector<T>& v);
		// 在pos插入一个数据
		iterator insert(iterator pos, const T& val);
		// 删除pos的数据
		iterator erase(iterator pos);
	private:
		// 指向有效数据头的指针
		iterator _start;
		// 指向有效数据尾的指针
		iterator _finish;
		// 指向存储容量的尾指针
		iterator _finishstorage;
	};

	template <class T>
	void vector<T>::push_back(const T& val)
	{
		if (_finish == _finishstorage)
		{
			reserve(capacity() * 2);
		}
		*_finish = val;
		_finish++;
	};
	// 尾删
	template <class T>
	void vector<T>::pop_back()
	{
		if (empty())
		{
			return;
		}
		_finish--;
	};
	// 调整容量
	template <class T>
	void vector<T>::reserve(size_t n)
	{
		size_t oldCapacity = capacity();
		size_t oldSize = size();

		T* tmp = new T[n];
		if (n > oldCapacity)
		{
			if (_start)
			{
				for (size_t i = 0; i < oldSize; i++)
				{
					tmp[i] = _start[i];
				}
				delete[] _start;
			}
			_start = tmp;
			_finish = _start + oldSize;
			_finishstorage = _start + n;
		}
	};
	// 调整有效数据大小
	template <class T>
	void vector<T>::resize(size_t n, const T& val)
	{
		size_t oldCapacity = capacity();
		size_t oldSize = size();
		if (n > oldCapacity)
		{
			reserve(n);
		}
		for (size_t i = oldSize; i < n; i++)
		{
			_start[i] = val;
		}
		_finish = _start + n;
	};
	// 构造空对象
	template <class T>
	vector<T>::vector()
		: _start(nullptr)
		, _finish(nullptr)
		, _finishstorage(nullptr)
	{};
	// 构造并初始化
	template <class T>
	vector<T>::vector(size_t n, const T val)
		: _start(new T[n])
	{
		for (size_t i = 0; i < n; i++)
		{
			_start[i] = val;
		}
		_finish = _start + n;
		_finishstorage = _finish;
	};
	// 拷贝构造
	template <class T>
	vector<T>::vector(const vector<T>& v)
		:_start(new T[v.size()])
	{
		size_t sz = v.size();
		for (size_t i = 0; i < sz; i++)
		{
			_start[i] = v._start[i];
		}
		_finish = _start + sz;
		_finishstorage = _finish;
	};
	// 析构函数
	template <class T>
	vector<T>::~vector()
	{
		if (_start)
		{
			delete[] _start;
		}
		_start = _finish = _finishstorage = nullptr;
	};
	// 赋值重载
	template <class T>
	vector<T>& vector<T>::operator=(vector<T> v)
	{
		swap(v);
		return *this;
	};
	// 交换
	template <class T>
	void vector<T>::swap(vector<T>& v)
	{
		aswap(_start, v._start);
		aswap(_finish, v._finish);
		aswap(_finishstorage, v._finishstorage);
	};
	// 在pos插入一个数据
	template <class T>
	T* vector<T>::insert(vector<T>::iterator pos, const T& val)
	{
		if (pos < _start || pos < _finish)
		{
			return end();
		}
		if (_start == _finish)
		{
			reserve(capacity() * 2);
		}
		iterator it = _finish;
		while (it != pos)
		{
			*it = (*it - 1);
			it--;
		}
		*pos = val;
		_finish++;
		return pos;
	};

	// 删除pos的数据
	template <class T>
	T* vector<T>::erase(vector<T>::iterator pos)
	{
		iterator begin = pos + 1;
		while (begin != _finish)
		{
			*(begin - 1) = *begin;
			++begin;
		}
		--_finish;
		return pos;
	};
}