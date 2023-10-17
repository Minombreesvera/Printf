#include "main.h"

/****************** PRINT POINTER ******************/
/**
 * print_pointer - Prints the value of a pointer variable
 * @arg_types: List a of arguments
 * @buffer: The Buffer array to handle print
 * @flag:  This Calculates active flags
 * @width: get width
 * @precision: For Precision specification
 * @size: For Size specifier
 * Return: Number of chars printed.
 */
int print_pointer(va_list arg_types, char buffer[],
	int flag, int width, int precision, int size)
{
	char ext_c = 0, pad = ' ';
	int ind = BUFF_SIZE - 2, len = 2, pad_start = 1; /* len=2, for '0x' */
	unsigned long num_addrs;
	char maps[] = "0123456789abcdef";
	void *addrs = va_arg(arg_types, void *);

	UNUSED(width);
	UNUSED(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	num_addrs = (unsigned long)addrs;

	while (num_addrs > 0)
	{
		buffer[ind--] = maps[num_addrs % 16];
		num_addrs /= 16;
		len++;
	}

	if ((flag & F_ZERO) && !(flag & F_MINUS))
		pad = '0';
	if (flag & F_PLUS)
		ext_c = '+', len++;
	else if (flag & F_SPACE)
		ext_c = ' ', len++;

	ind++;

	/*return (write(1, &buffer[i], BUFF_SIZE - i - 1));*/
	return (write_pointer(buffer, ind, len,
		width, flag, pad, ext_c, pad_start));
}

/************************* PRINT NON PRINTABLE *************************/
/**
 * print_non_printable - Prints ascii codes in hexa of non printable chars
 * @arg_types: List a of arguments
 * @buffer: The Buffer array to handle print
 * @flag:  This Calculates active flag
 * @width: get width
 * @precision: For Precision specification
 * @size: For Size specifier
 * Return: Number of chars printed
 */
int print_non_printable(va_list arg_types, char buffer[],
	int flag, int width, int precision, int size)
{
	int i = 0, off_set = 0;
	char *str = va_arg(arg_types, char *);

	UNUSED(flag);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[i] != '\0')
	{
		if (for_printable(str[i]))
			buffer[i + off_set] = str[i];
		else
			off_set += append_hex_code(str[i], buffer, i + off_set);

		i++;
	}

	buffer[i + off_set] = '\0';

	return (write(1, buffer, i + off_set));
}

/************************* PRINT REVERSE *************************/
/**
 * print_reverse - Prints reverse string.
 * @arg_types: List a of arguments
 * @buffer: The Buffer array to handle print
 * @flag:  This Calculates active flag
 * @width: get width
 * @precision: For Precision specification
 * @size: For Size specifier
 * Return: Numbers of chars printed
 */

int print_reverse(va_list arg_types, char buffer[],
	int flag, int width, int precision, int size)
{
	char *str;
	int i, cnt = 0;

	UNUSED(buffer);
	UNUSED(flag);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(arg_types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (i = 0; str[i]; i++)
		;

	for (i = i - 1; i >= 0; i--)
	{
		char z = str[i];

		write(1, &z, 1);
		cnt++;
	}
	return (cnt);
}
/************************* PRINT A STRING IN ROT13 *************************/
/**
 * print_rot13_string - Print a string in rot13.
 * @arg_types: List a of arguments
 * @buffer: The Buffer array to handle print
 * @flag:  This Calculates active flag
 * @width: get width
 * @precision: For Precision specification
 * @size: For Size specifier
 * Return: Numbers of chars printed
 */
int print_rot13_string(va_list arg_types, char buffer[],
	int flag, int width, int precision, int size)
{
	char x;
	char *str;
	unsigned int i, j;
	int cnt = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(arg_types, char *);
	UNUSED(buffer);
	UNUSED(flag);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (i = 0; str[i]; i++)
	{
		for (j = 0; in[j]; j++)
		{
			if (in[j] == str[i])
			{
				x = out[j];
				write(1, &x, 1);
				cnt++;
				break;
			}
		}
		if (!in[j])
		{
			x = str[i];
			write(1, &x, 1);
			cnt++;
		}
	}
	return (cnt);
}
