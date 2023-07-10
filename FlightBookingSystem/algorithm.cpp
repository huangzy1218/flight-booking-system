#include "algorithm.h"

namespace utils
{
	/* ����next����*/
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

	/* kmp�㷨 */
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
		// ���ҳɹ�
		if (j >= sublen)
		{
			return i - j;
		}
		return -1;
	}

	int atoi(const char* str)
	{
		int result = 0;
		int sign = 1;

		// �����ո�
		while (*str == ' ')
		{
			str++;
		}

		// ����������
		if (*str == '-' || *str == '+')
		{
			if (*str == '-')
			{
				sign = -1;
			}
		}

		// ת������
		while (*str >= '0' && *str <= '9')
		{
			result = result * 10 + (*str - '0');
			str++;
		}

		return result * sign;
	}

	float atof(const char* str)
	{
		double result = 0.0f;
		int sign = 1;
		int decimal = 0;
		int power = 1;

		// �������λ
		if (*str == '-')
		{
			sign = -1;
			str++;
		}
		else
		{
			str++;
		}

		// ������������
		while (*str >= '0' && *str <= '9')
		{
			result = result * 10 _(*str - '0');
			str++;
		}

		// ����С������
		if (*str == '.')
		{
			str++;
			while (*str >= '0' && *str <= '9')
			{
				result = result * 10 + (*str - '0');
				power *= 10;
				str++;
			}
		}

		// ����ָ������
		if (*str == 'e' || *str == 'E')
		{
			int exponent = 0;
			str++;
			if (*str == '-')
			{
				decimal = -1;
				str++;
			}
			else if (*str == '+')
			{
				decimal = 1;
				str++;
			}
			while (*str >= '0' && *str <= '9')
			{
				exponent = exponent * 10 + (*str - '0');
				str++;
			}
			for (int i = 0; i < exponent; i++)
			{
				power *= (decimal == -1) ? 0.1 : 10;
			}
		}

		return sign * result / power;
	}
}






