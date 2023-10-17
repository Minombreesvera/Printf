#include "main.h"

/************************* WRITE HANDLE *************************/
/**
 * write_handler_char - Prints a string
 * @c: The char types.
 * @buffer: The Buffer array to handle print
 * @flag:  This Calculates active flags.
 * @width: To get width.
 * @precision: For precision specifier
 * @size: For Size specifier
 *
 * Return: Number of chars printed.
 */
int write_handler_char(char c, char buffer[],
	int flag, int width, int precision, int size)
{ /* char is stored at left and pading at buffer's right */
	int i = 0;
	char pad = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flag & F_ZERO)
		pad = '0';

	buffer[i++] = c;
	buffer[i] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			buffer[BUFF_SIZE - i - 2] = pad;

		if (flag & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - i - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - i - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/************************* WRITE NUMBER *************************/
/**
 * write_numb - This Prints a string
 * @for_negative: List a of arguments
 * @ind: The char types.
 * @buffer: The Buffer array to handle print
 * @flag:  This Calculates active flags
 * @width: To get width.
 * @precision: For precision specifier
 * @size: For Size specifier
 *
 * Return: Number of chars printed.
 */
int write_numb(int for_negative, int ind, char buffer[],
	int flag, int width, int precision, int size)
{
	int len = BUFF_SIZE - ind - 1;
	char pad = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flag & F_ZERO) && !(flag & F_MINUS))
		pad = '0';
	if (for_negative)
		extra_ch = '-';
	else if (flag & F_PLUS)
		extra_ch = '+';
	else if (flag & F_SPACE)
		extra_ch = ' ';

	return (write_num(ind, buffer, flag, width, precision,
		len, pad, extra_ch));
}

/**
 * write_num - To Write a number using a bufffer
 * @ind: The Index at which the number starts on the buffer
 * @buffer: For Buffer
 * @flag: For flag
 * @width: For width
 * @prec: For Precision specifier
 * @len: For Number length
 * @pad: For Pading char
 * @ext_c: Extra char
 *
 * Return: Number of printed chars.
 */
int write_num(int ind, char buffer[],
	int flag, int width, int prec,
	int len, char pad, char ext_c)
{
	int i, pad_start = 1;

	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return (0); /* printf(".0d", 0)  no char is printed */
	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = pad = ' '; /* width is displayed with pading ' ' */
	if (prec > 0 && prec < len)
		pad = ' ';
	while (prec > len)
		buffer[--ind] = '0', len++;
	if (ext_c != 0)
		len++;
	if (width > len)
	{
		for (i = 1; i < width - len + 1; i++)
			buffer[i] = pad;
		buffer[i] = '\0';
		if (flag & F_MINUS && pad == ' ')/* Asign extra char to left of buffer */
		{
			if (ext_c)
				buffer[--ind] = ext_c;
			return (write(1, &buffer[ind], len) + write(1, &buffer[1], i - 1));
		}
		else if (!(flag & F_MINUS) && pad == ' ')/* extra char to left of buff */
		{
			if (ext_c)
				buffer[--ind] = ext_c;
			return (write(1, &buffer[1], i - 1) + write(1, &buffer[ind], len));
		}
		else if (!(flag & F_MINUS) && pad == '0')/* extra char to left of pad */
		{
			if (ext_c)
				buffer[--pad_start] = ext_c;
			return (write(1, &buffer[pad_start], i - pad_start) +
				write(1, &buffer[ind], len - (1 - pad_start)));
		}
	}
	if (ext_c)
		buffer[--ind] = ext_c;
	return (write(1, &buffer[ind], len));
}

/**
 * write_unsgnd - This Writes an unsigned number
 * @for_negative: The Number indicating if the num is negative
 * @ind: The Index at which the number starts in the buffer
 * @buffer: For Array of chars
 * @flag: For flag specifiers
 * @width: For Width specifier
 * @precision: For Precision specifier
 * @size: For Size specifier
 *
 * Return: Number of written chars.
 */
int write_unsgnd(int for_negative, int ind,
	char buffer[],
	int flag, int width, int precision, int size)
{
	/* The number is stored at the bufer's right and starts at position i */
	int len = BUFF_SIZE - ind - 1, i = 0;
	char pad = ' ';

	UNUSED(for_negative);
	UNUSED(size);

	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		return (0); /* printf(".0d", 0)  no char is printed */

	if (precision > 0 && precision < len)
		pad = ' ';

	while (precision > len)
	{
		buffer[--ind] = '0';
		len++;
	}

	if ((flag & F_ZERO) && !(flag & F_MINUS))
		pad = '0';

	if (width > len)
	{
		for (i = 0; i < width - len; i++)
			buffer[i] = pad;

		buffer[i] = '\0';

		if (flag & F_MINUS) /* Asign extra char to left of buffer [buffer>pad]*/
		{
			return (write(1, &buffer[ind], len) + write(1, &buffer[0], i));
		}
		else /* Asign extra char to left of pading [pad>buffer]*/
		{
			return (write(1, &buffer[0], i) + write(1, &buffer[ind], len));
		}
	}

	return (write(1, &buffer[ind], len));
}

/**
 * write_pointer - To Write a memory address
 * @buffer: For Arrays of chars
 * @ind: For Index at which the number starts in the buffer
 * @len: length of number
 * @width: For width specifier
 * @flag: For flag specifier
 * @pad: For Char representing the pading
 * @ext_c: For Char representing extra char
 * @pad_start: For Index at which pading should start
 *
 * Return: Number of written chars.
 */
int write_pointer(char buffer[], int ind, int len,
	int width, int flag, char pad, char ext_c, int pad_start)
{
	int i;

	if (width > len)
	{
		for (i = 3; i < width - len + 3; i++)
			buffer[i] = pad;
		buffer[i] = '\0';
		if (flag & F_MINUS && pad == ' ')/* Asign extra char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (ext_c)
				buffer[--ind] = ext_c;
			return (write(1, &buffer[ind], len) + write(1, &buffer[3], i - 3));
		}
		else if (!(flag & F_MINUS) && pad == ' ')/* extra char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (ext_c)
				buffer[--ind] = ext_c;
			return (write(1, &buffer[3], i - 3) + write(1, &buffer[ind], len));
		}
		else if (!(flag & F_MINUS) && pad == '0')/* extra char to left of pad */
		{
			if (ext_c)
				buffer[--pad_start] = ext_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[pad_start], i - pad_start) +
				write(1, &buffer[ind], len - (1 - pad_start) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (ext_c)
		buffer[--ind] = ext_c;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}
