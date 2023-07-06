#pragma once
#include <cstddef>

namespace utils
{
	/* ����next����*/
	void get_next(const char* sub, size_t sub_len, int* next);

	/* kmp�㷨 */
	size_t kmp(const char* str, const char* sub, size_t strlen, size_t sublen, size_t pos = 0);

	/* ����Ԫ�� */
	template<class T> void swap(T& a, T& b)
	{
		T temp = a;
		a = b;
		b = temp;
	};
}
