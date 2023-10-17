#include "main.h"

/**
 * get_precision - This Calculates the precision for printing
 * @format: The Formatted string in which to print the arguments
 * @i: The List of arguments to be printed.
 * @list_of_arg: The list of arguments.
 *
 * Return: Precision.
 */
int get_precision(const char *format, int *i, va_list list_of_arg)
{
	int cur_j = *i + 1;
	int precision = -1;

	if (format[cur_j] != '.')
		return (precision);

	precision = 0;

	for (cur_j += 1; format[cur_j] != '\0'; cur_j++)
	{
		if (for_digit(format[cur_j]))
		{
			precision *= 10;
			precision += format[cur_j] - '0';
		}
		else if (format[cur_j] == '*')
		{
			cur_j++;
			precision = va_arg(list_of_arg, int);
			break;
		}
		else
			break;
	}

	*i = cur_j - 1;

	return (precision);
}
