
#include "main.h"

/************************* PRINT UNSIGNED NUMBER *************************/
/**
 * print_unsigned - To Prints an unsigned number
 * @arg_types: List a of arguments
 * @buffer: The Buffer array to handle print
 * @flag:  This Calculates active flags
 * @width: To get width
 * @precision: For Precision specification
 * @size: For Size specifier
 * Return: Number of chars printed.
 */
int print_unsigned(va_list arg_types, char buffer[],
	int flag, int width, int precision, int size)
{
	int j = BUFF_SIZE - 2;
	unsigned long int num = va_arg(arg_types, unsigned long int);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[j--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[j--] = (num % 10) + '0';
		num /= 10;
	}

	j++;

	return (write_unsgnd(0, j, buffer, flag, width, precision, size));
}

/************* PRINT UNSIGNED NUMBER IN OCTAL  ****************/
/**
 * print_oct - Prints an unsigned number in octal notation
 * @arg_types: List a of arguments
 * @buffer: The Buffer array to handle print
 * @flag:  This Calculates active flags
 * @width: get width
 * @precision: For Precision specification
 * @size: For Size specifier
 * Return: Number of chars printed
 */
int print_oct(va_list arg_types, char buffer[],
	int flag, int width, int precision, int size)
{

	int j = BUFF_SIZE - 2;
	unsigned long int num = va_arg(arg_types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[j--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[j--] = (num % 8) + '0';
		num /= 8;
	}

	if (flag & F_HASH && init_num != 0)
		buffer[j--] = '0';

	j++;

	return (write_unsgnd(0, j, buffer, flag, width, precision, size));
}

/************** PRINT UNSIGNED NUMBER IN HEXADECIMAL **************/
/**
 * print_hexadec - Prints an unsigned number in hexadecimal notation
 * @arg_types: List a of arguments
 * @buffer: The Buffer array to handle print
 * @flag:  This Calculates active flags
 * @width: get width
 * @precision: For Precision specification
 * @size: For Size specifier
 * Return: Number of chars printed
 */
int print_hexadec(va_list arg_types, char buffer[],
	int flag, int width, int precision, int size)
{
	return (print_hexa(arg_types, "0123456789abcdef", buffer,
		flag, 'x', width, precision, size));
}

/************* PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL **************/
/**
 * print_hex_upper - Prints an unsigned number in upper hexadecimal notation
 * @arg_types: List a of arguments
 * @buffer: The Buffer array to handle print
 * @flag:  This Calculates active flags
 * @width: get width
 * @precision: For Precision specification
 * @size: For Size specifier
 * Return: Number of chars printed
 */
int print_hex_upper(va_list arg_types, char buffer[],
	int flag, int width, int precision, int size)
{
	return (print_hexa(arg_types, "0123456789ABCDEF", buffer,
		flag, 'X', width, precision, size));
}

/************** PRINT HEX NUM IN LOWER OR UPPER **************/
/**
 * print_hex - Prints a hexadecimal number in lower or upper
 * @arg_types: List a of arguments
 * @maps: Array of values to map the number to
 * @buffer: The Buffer array to handle print
 * @flag:  This Calculates active flags
 * @act_flag: Calculates active flag
 * @width: get width
 * @precision: For Precision specification
 * @size: For Size specifier
 * @size: For Size specification
 * Return: Number of chars printed
 */
int print_hex(va_list arg_types, char maps[], char buffer[],
	int flag, char act_flag, int width, int precision, int size)
{
	int j = BUFF_SIZE - 2;
	unsigned long int num = va_arg(arg_types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[j--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[j--] = maps[num % 16];
		num /= 16;
	}

	if (flag & F_HASH && init_num != 0)
	{
		buffer[j--] = act_flag;
		buffer[j--] = '0';
	}

	j++;

	return (write_unsgnd(0, j, buffer, flag, width, precision, size));
}
