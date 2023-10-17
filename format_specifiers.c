#include "main.h"

/************************* PRINT CHAR *************************/

/**
 * print_char - Prints a char using %c
 * @arg_types: List a of arguments
 * @buffer: The Buffer array to handle print
 * @flag:  This Calculates active flags
 * @width: Width
 * @precision: The Precision specification
 * @size: For Size specifier
 * Return: Number of chars printed
 */
int print_char(va_list arg_types, char buffer[],
	int flag, int width, int precision, int size)
{
	char c = va_arg(arg_types, int);

	return (write_handler_char(c, buffer, flag, width, precision, size));
}
/************************* PRINT A STRING *************************/
/**
 * print_str - Prints a string using %s
 * @arg_types: List a of arguments
 * @buffer: The Buffer array to handle print
 * @flag:  This Calculates active flag
 * @width: get width.
 * @precision: For Precision specification
 * @size: For Size specifier
 * Return: Number of chars printed
 */
int print_str(va_list arg_types, char buffer[],
	int flag, int width, int precision, int size)
{
	int len = 0, i;
	char *str = va_arg(arg_types, char *);

	UNUSED(buffer);
	UNUSED(flag);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[len] != '\0')
		len++;

	if (precision >= 0 && precision < len)
		len = precision;

	if (width > len)
	{
		if (flag & F_MINUS)
		{
			write(1, &str[0], len);
			for (i = width - len; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - len; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], len);
			return (width);
		}
	}

	return (write(1, str, len));
}
/************************* PRINT PERCENT SIGN *************************/
/**
 * print_percent - Prints a percent sign using %%
 * @arg_types: List a of arguments
 * @buffer: The Buffer array to handle print
 * @flag:  This Calculates active flag
 * @width: get width.
 * @precision: For Precision specification
 * @size: For Size specifier
 * Return: Number of chars printed
 */
int print_percent(va_list arg_types, char buffer[],
	int flag, int width, int precision, int size)
{
	UNUSED(arg_types);
	UNUSED(buffer);
	UNUSED(flag);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/************************* PRINT INT *************************/
/**
 * print_int - Print int
 * @arg_types: List a of arguments
 * @buffer: The Buffer array to handle print
 * @flag:  This Calculates active flag
 * @width: get width.
 * @precision: For Precision specification
 * @size: For Size specifier
 * Return: Number of chars printed
 */
int print_int(va_list arg_types, char buffer[],
	int flag, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	int for_negative = 0;
	long int n = va_arg(arg_types, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		for_negative = 1;
	}

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_numb(for_negative, i, buffer, flag, width, precision, size));
}

/************************* PRINT BINARY *************************/
/**
 * print_bin - Prints an unsigned number
 * @arg_types: List a of arguments
 * @buffer: The Buffer array to handle print
 * @flag:  This Calculates active flag
 * @width: get width.
 * @precision: For Precision specification
 * @size: For Size specifier
 * Return: Numbers of char printed.
 */
int print_bin(va_list arg_types, char buffer[],
	int flag, int width, int precision, int size)
{
	unsigned int n, m, i, sum;
	unsigned int a[32];
	int cnt;

	UNUSED(buffer);
	UNUSED(flag);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	n = va_arg(arg_types, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	a[0] = n / m;
	for (i = 1; i < 32; i++)
	{
		m /= 2;
		a[i] = (n / m) % 2;
	}
	for (i = 0, sum = 0, cnt = 0; i < 32; i++)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			cnt++;
		}
	}
	return (cnt);
}
