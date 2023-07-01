#include "main.h"

/**
 * print_pointer - prints value of a pointer
 * @types: list of arguments
 * @buffer: the array to handle print
 * @flags:  calculates flags
 * @width: gets width
 * @precision: the specification
 * @size: the specifier
 * Return: printed chars
 */
int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char extra_c = 0, padd = ' ';
	int Ind = BUFF_SIZE - 2, lngth = 2, padd_start = 1; /* lngth=2, for '0x' */
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));
	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	num_addrs = (unsigned long)addrs;

	while (num_addrs > 0)
	{
		buffer[Ind--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		lngth++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		extra_c = '+', lngth++;
	else if (flags & F_SPACE)
		extra_c = ' ', lngth++;
	Ind++;

	/*return (write(1, &buffer[i], BUFF_SIZE - i - 1));*/
	return (write_pointer(buffer, Ind, lngth,
		width, flags, padd, extra_c, padd_start));
}

/**
 * print_non_printable - prints ASCII codes in hexa no-printable format
 * @types: list of arguments
 * @buffer: the array to handle print
 * @flags:  calculates flags
 * @width: gets width
 * @precision: the specification
 * @size: the specifier
 * Return: the printed chars
 */
int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int c = 0, offset = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[c] != '\0')
	{
		if (is_printable(str[c]))
			buffer[c + offset] = str[c];
		else
			offset += append_hexa_code(str[c], buffer, c + offset);
		c++;
	}

	buffer[c + offset] = '\0';

	return (write(1, buffer, c + offset));
}

/**
 * print_reverse - prints string in reverse order
 * @types: list of arguments
 * @buffer: the array to handle print
 * @flags:  calculates flags
 * @width: gets width
 * @precision: the specification
 * @size: the specifier
 * Return: printed chars
 */
int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int c, count = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}

	for (c = 0; str[c]; c++)
		;

	for (c = c - 1; c >= 0; c--)
	{
		char z = str[c];

		write(1, &z, 1);
		count++;
	}
	return (count);
}

/**
 * print_rot13string - print string in rot13
 * @types: list of arguments
 * @buffer: the array to handle print
 * @flags:  calculates flags
 * @width: gets width
 * @precision: the specification
 * @size: the specifier
 * Return: printed chars
 */
int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char a;
	char *str;
	unsigned int c, j;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (c = 0; str[c]; c++)
	{
		for (j = 0; in[j]; j++)
		{
			if (in[j] == str[c])
			{
				a = out[j];
				write(1, &a, 1);
				count++;
				break;
			}
		}
		if (!in[j])
		{
			a = str[c];
			write(1, &a, 1);
			count++;
		}
	}
	return (count);
}
