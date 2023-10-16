#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - Printf function
 * @format: constant char pointer .
 * Return: char_len.
 */
int _printf(const char *format, ...)
{
	int i, prints = 0, char_len = 0;
	int flag, width, precision, size, buff_ind = 0;
	va_list list_of_arg;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list_of_arg, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buff_ind++] = format[i];
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);
			/* write(1, &format[i], 1);*/
			char_len++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			flag = get_flag(format, &i);
			width = get_width(format, &i, list_of_arg);
			precision = get_precision(format, &i, list_of_arg);
			size = get_size(format, &i);
			++i;
			prints = handle_print(format, &i, list_of_arg, buffer,
				flag, width, precision, size);
			if (prints == -1)
				return (-1);
			char_len += prints;
		}
	}

	print_buffer(buffer, &buff_ind);

	va_end(list_of_arg);

	return (char_len);
}

/**
 * print_buffer - Prints the contents of the buffer if it exist
 * @buffer: Array of chars
 * @buff_ind: Index at which to add next char, this represents the length.
 */
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}
