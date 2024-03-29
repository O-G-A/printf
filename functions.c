#include "main.h"

/**
 * print_char - prints char
 * @types: list of arguments
 * @buffer: the array to handle print
 * @flags:  calculates flags
 * @width: the width
 * @precision: the specification
 * @size: the specifier
 *
 * Return: printed chars
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char i = va_arg(types, int);

	return (handle_write_char(i, buffer, flags, width, precision, size));
}

/**
 * print_string - prints string
 * @types: list of arguments
 * @buffer: the array to handle print
 * @flags: calculates flags
 * @width: get width
 * @precision: precision specification
 * @size: size specifier
 *
 * Return: printed chars
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, c;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (c = width - length; c > 0; c--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (c = width - length; c > 0; c--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}

/**
 * print_percent - prints the percentage sign
 * @types: list of arguments
 * @buffer: the array to handle print
 * @flags:  calculates flags
 * @width: gets width
 * @precision: the specification
 * @size: the specifier
 * Return: printed chars
 */
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	return (write(1, "%%", 1));
}

/**
 * print_int - prints int
 * @types: list of arguments
 * @buffer: the array to handle print
 * @flags: calculates flags
 * @width: gets width
 * @precision: the specification
 * @size: the specifier
 * Return: printed chars
 */
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int c = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[c--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[c--] = (num % 10) + '0';
		num /= 10;
	}

	c++;

	return (write_number(is_negative, c, buffer, flags, width, precision, size));
}

/**
 * print_binary - prints unsigned number
 * @types: list of arguments
 * @buffer: the array to handle print
 * @flags:  calculates flags
 * @width: gets width
 * @precision: the specification
 * @size: the specifier
 * Return: printed char
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int n, m, c, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	n = va_arg(types, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	a[0] = n / m;
	for (c = 1; c < 32; c++)
	{
		m /= 2;
		a[c] = (n / m) % 2;
	}
	for (c = 0, sum = 0, count = 0; c < 32; c++)
	{
		sum += a[c];
		if (sum || c == 31)
		{
			char z = '0' + a[c];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
