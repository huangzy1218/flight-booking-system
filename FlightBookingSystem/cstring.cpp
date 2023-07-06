#include "cstring.h"
#include "algorithm.h"

namespace utils
{
	/* �ַ������� */
	size_t strlen(const char* str)
	{
		int len = 0;
		while (*str++)
		{
			len++;
		}
		return len;
	}

	/* �ַ������� */
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

	/* �ַ���ƴ�� */
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

	/* �ַ����Ƚ� */
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

	/* ����needle��haystack��һ�γ���λ�� */
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

	/* ����c��s��һ�γ���λ�� */
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