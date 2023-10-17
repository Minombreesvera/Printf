#include "main.h"

/**
 * pukmat - writes the character c to stdout
 * @c: The character to be printed
 * Return: 1
 */

int pukmat(char c)
{
	return (write(1, &c, 1));
}
