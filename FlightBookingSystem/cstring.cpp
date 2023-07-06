#include "cstring.h"
#include "algorithm.h"

namespace utils
{
	/* 字符串长度 */
	size_t strlen(const char* str)
	{
		int len = 0;
		while (*str++)
		{
			len++;
		}
		return len;
	}

	/* 字符串复制 */
	char* strcpy(char* dest, const char* src)
	{
		char* ret = dest;
		while (*src)
		{
			*dest++ = *src++;
		}
		*dest = '\0';
		return ret;
	}

	/* 字符串拼接 */
	char* strcat(char* dest, const char* src)
	{
		char* ret = dest;
		while (*dest)
		{
			dest++;
		}
		while (*src)
		{
			*dest++ = *src++;
		}
		*dest = '\0';
		return ret;
	}

	/* 字符串比较 */
	size_t strcmp(char* str1, char* str2)
	{
		int ret = 0;
		while (!(ret = *(unsigned char*)str1 - *(unsigned char*)str2) && *str2)
		{
			++str1;
			++str2;
		}
		return ret;
	}

	/* 查找needle在haystack第一次出现位置 */
	char* strstr(char* haystack, const char* needle)
	{
		size_t haystack_len = strlen(haystack);
		size_t needle_len = strlen(needle);
		const char* p = haystack;
		if (!needle_len)
		{
			return (char*)haystack;
		}
		int offset = kmp(haystack, needle, haystack_len, needle_len, 0);
		if (offset == -1)
		{
			return nullptr;
		}
		return (char*)p + offset;
	}

	/* 查找c在s第一次出现位置 */
	char* strchr(char* s, char c)
	{
		while (*s != c)
		{
			if (*s++)
			{
				return 0;
			}
			return (char*)s;
		}
		return nullptr;
	}
}