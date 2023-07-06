#include "algorithm.h"

namespace utils
{
	/* 生成next数组*/
	void get_next(const char* sub, size_t sub_len, int* next)
	{
		next[0] = -1;
		next[1] = 0;

		int i = 2, k = 0;
		while (i < sub_len)
		{
			if (sub[i - 1] == sub[k] || k == -1)
			{
				next[i] = k + 1;
				i++;
				k++;
			}
			else
			{
				k = next[k];
			}
		}
	}

	/* kmp算法 */
	size_t kmp(const char* str, const char* sub, size_t strlen, size_t sublen, size_t pos)
	{
		if (pos < 0 || pos >= strlen)
		{
			return -1;
		}
		if (sublen > strlen)
		{
			return -1;
		}
		size_t i = pos, j = 0;

		int* next = new int[sublen];
		get_next(sub, sublen, next);

		while (i < strlen && j < sublen)
		{
			if (str[i] == sub[j] || j == -1)
			{
				i++;
				j++;
			}
			else
			{
				j = next[j];
			}
		}
		// 查找成功
		if (j >= sublen)
		{
			return i - j;
		}
		return -1;
	}
}






