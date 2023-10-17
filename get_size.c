#include "main.h"

/**
 * get_size - this Calculates the size to cast the argument
 * @format: The Formatted string in which to print the arguments
 * @i: List of arguments to be printed.
 *
 * Return: Precision.
 */
int get_size(const char *format, int *i)
{
	int cur_j = *i + 1;
	int size = 0;

	if (format[cur_j] == 'l')
		size = S_LONG;
	else if (format[cur_j] == 'h')
		size = S_SHORT;

	if (size == 0)
		*i = cur_j - 1;
	else
		*i = cur_j;

	return (size);
}
