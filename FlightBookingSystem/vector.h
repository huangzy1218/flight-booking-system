#pragma once
#include <assert.h>

namespace utils
{
	template <class T>
	class vector 
	{
	public:
		// ��ͨ������
		typedef T* iterator;
		// const������
		typedef const T* const_iterator;
		// ����һ��ָ���һ�����ݵ���ͨ������
		iterator begin()
		{
			return _start;
		}
		// ����һ��ָ���һ�����ݵ�const������
		const_iterator cbegin()
		{
			return _start;
		}
		// ����һ��ָ�����һ�����ݵ���һ��λ�õ���ͨ������
		iterator end()
		{
			return _finish;
		}
		// ����һ��ָ�����һ�����ݵ���һ��λ�õ�const������
		const_iterator cend()
		{
			return _finish;
		}
		// ������Ч���ݵĸ���
		size_t size() const
		{
			return _finish - _start;
		}
		// ����������С
		size_t capacity()
		{
			return _finishstorage - _start;
		}
		// �п�
		bool empty() const
		{
			return _start == _finish;
		}
		// ��ȡ��Ԫ��
		T& front()
		{
			return _start[0];
		}
		const T& front() const
		{
			return _start[0];
		}
		// ��ȡβԪ��
		T& back()
		{
			return *(_finish - 1);
		}
		const T& back() const
		{
			return *(_finish - 1);
		}
		// �������Ԫ��
		void clear()
		{
			_finish = _start;
		}
		// []����
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
		// β��
		void push_back(const T& val);
		// βɾ
		void pop_back();
		// ��������
		void reserve(size_t n);
		// ������Ч���ݴ�С
		void resize(size_t n, const T& val = T());
		// ����ն���
		vector();
		// ���첢��ʼ��
		vector(size_t n, const T val = T());
		// ��������
		vector(const vector<T>& v);
		// ��������
		~vector();
		// ��ֵ����
		vector<T>& operator=(vector<T> v);
		// ����
		void swap(vector<T>& v);
		// ��pos����һ������
		iterator insert(iterator pos, const T& val);
		// ɾ��pos������
		iterator erase(iterator pos);
	private:
		// ָ����Ч����ͷ��ָ��
		iterator _start;
		// ָ����Ч����β��ָ��
		iterator _finish;
		// ָ��洢������βָ��
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
	// βɾ
	template <class T>
	void vector<T>::pop_back()
	{
		if (empty())
		{
			return;
		}
		_finish--;
	};
	// ��������
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
	// ������Ч���ݴ�С
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
	// ����ն���
	template <class T>
	vector<T>::vector()
		: _start(nullptr)
		, _finish(nullptr)
		, _finishstorage(nullptr)
	{};
	// ���첢��ʼ��
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
	// ��������
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
	// ��������
	template <class T>
	vector<T>::~vector()
	{
		if (_start)
		{
			delete[] _start;
		}
		_start = _finish = _finishstorage = nullptr;
	};
	// ��ֵ����
	template <class T>
	vector<T>& vector<T>::operator=(vector<T> v)
	{
		swap(v);
		return *this;
	};
	// ����
	template <class T>
	void vector<T>::swap(vector<T>& v)
	{
		aswap(_start, v._start);
		aswap(_finish, v._finish);
		aswap(_finishstorage, v._finishstorage);
	};
	// ��pos����һ������
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

	// ɾ��pos������
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