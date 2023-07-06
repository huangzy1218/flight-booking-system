#pragma once

#include "algorithm.h"
namespace utils
{
	/* �ַ������� */
	size_t strlen(const char* str);

	/* �ַ������� */
	char* strcpy(char* dest, const char* src);

	/* �ַ���ƴ�� */
	char* strcat(char* dest, const char* src);

	/* �ַ����Ƚ� */
	size_t strcmp(char* str1, char* str2);

	/* ����needle��haystack��һ�γ���λ�� */
	char* strstr(char* haystack, char* needle);

	/* ����c��s��һ�γ���λ�� */
	char* strchr(char* s, int c);

}
