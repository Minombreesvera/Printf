#include "main.h"

/**
 * get_width - This Calculates the width for printing
 * @format: The Formatted string in which to print the arguments.
 * @i: list of arguments to be printed.
 * @list_of_arg: list of arguments.
 *
 * Return: width.
 */
int get_width(const char *format, int *i, va_list list_of_arg)
{
	int cur_j;
	int width = 0;

	for (cur_j = *i + 1; format[cur_j] != '\0'; cur_j++)
	{
		if (for_digit(format[cur_j]))
		{
			width *= 10;
			width += format[cur_j] - '0';
		}
		else if (format[cur_j] == '*')
		{
			cur_j++;
			width = va_arg(list_of_arg, int);
			break;
		}
		else
			break;
	}

	*i = cur_j - 1;

	return (width);
}
