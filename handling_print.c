#include "main.h"
/**
 * handle_print - This Prints an argument based on its type
 * @frmt: The Formatted string in which to print the arguments.
 * @list_of_arg: list of arguments to be printed.
 * @ind: ind.
 * @buffer: The Buffer array to handle print.
 * @flag: This Calculates active flags
 * @width: get width.
 * @precision: For Precision specification
 * @size: For Size specifier
 * Return: 1 or 2;
 */
int handle_print(const char *frmt, int *ind,
		va_list list_of_arg, char buffer[],
	int flag, int width, int precision, int size)
{
	int i, unknow_len = 0, char_len = -1;
	frmt_t frmt_types[] = {
		{'c', print_char}, {'s', print_str}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_bin},
		{'u', print_unsigned}, {'o', print_oct}, {'x', print_hex},
		{'X', print_hex_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13_string}, {'\0', NULL}
	};
	for (i = 0; frmt_types[i].frmt != '\0'; i++)
		if (frmt[*ind] == frmt_types[i].frmt)
			return (frmt_types[i].fn(list_of_arg,
						buffer, flag, width, precision, size));

	if (frmt_types[i].frmt == '\0')
	{
		if (frmt[*ind] == '\0')
			return (-1);
		unknow_len += write(1, "%%", 1);
		if (frmt[*ind - 1] == ' ')
			unknow_len += write(1, " ", 1);
		else if (width)
		{
			--(*ind);
			while (frmt[*ind] != ' ' && frmt[*ind] != '%')
				--(*ind);
			if (frmt[*ind] == ' ')
				--(*ind);
			return (1);
		}
		unknow_len += write(1, &frmt[*ind], 1);
		return (unknow_len);
	}
	return (char_len);
}
