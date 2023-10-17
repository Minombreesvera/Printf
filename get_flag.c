#include "main.h"

/**
 * get_flag - This Calculates active flags
 * @format: The Formatted string in which to print the arguments
 * @i: To take a parameter.
 * Return: Flags:
 */
int get_flag(const char *format, int *i)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8  16 */
	int j, cur_j;
	int flag = 0;
	const char ACT_FLAG[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (cur_j = *i + 1; format[cur_j] != '\0'; cur_j++)
	{
		for (j = 0; ACT_FLAG[j] != '\0'; j++)
			if (format[cur_j] == ACT_FLAG[j])
			{
				flag |= FLAGS_ARR[j];
				break;
			}

		if (ACT_FLAG[j] == 0)
			break;
	}

	*i = cur_j - 1;

	return (flag);
}
