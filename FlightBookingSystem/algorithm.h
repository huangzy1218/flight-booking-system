#pragma once
#include <cstddef>

namespace utils
{
	/* 生成next数组*/
	void get_next(const char* sub, size_t sub_len, int* next);

	/* kmp算法 */
	size_t kmp(const char* str, const char* sub, size_t strlen, size_t sublen, size_t pos = 0);

	/* 交换元素 */
	template<class T> void swap(T& a, T& b)
	{
		T temp = a;
		a = b;
		b = temp;
	};
}
