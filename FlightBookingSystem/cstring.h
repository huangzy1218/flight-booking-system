#pragma once

#include "algorithm.h"
namespace utils
{
	/* 字符串长度 */
	size_t strlen(const char* str);

	/* 字符串复制 */
	char* strcpy(char* dest, const char* src);

	/* 字符串拼接 */
	char* strcat(char* dest, const char* src);

	/* 字符串比较 */
	size_t strcmp(char* str1, char* str2);

	/* 查找needle在haystack第一次出现位置 */
	char* strstr(char* haystack, char* needle);

	/* 查找c在s第一次出现位置 */
	char* strchr(char* s, int c);

}
