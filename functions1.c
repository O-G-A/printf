
#include "main.h"

/**
 * print_unsigned - prints unsigned number
 * @types: list of arguments
 * @buffer: the array to handle print
 * @flags:  calculates flags
 * @width: gets width
 * @precision: the specification
 * @size: the specifier
 * Return: printed chars
 */
int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int c = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[c--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[c--] = (num % 10) + '0';
		num /= 10;
	}

	c++;

	return (write_unsgnd(0, c, buffer, flags, width, precision, size));
}

/**
 * print_octal - Prints an unsigned number in octal notation
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int c = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[c--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[c--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & F_HASH && init_num != 0)
		buffer[c--] = '0';

	c++;

	return (write_unsgnd(0, c, buffer, flags, width, precision, size));
}

/**
 * print_hexadecimal - prints unsigned number in hexadecimal
 * @types: list of arguments
 * @buffer: the array to print
 * @flags:  calculates flags
 * @width: gets width
 * @precision: the specification
 * @size: the specifier
 * Return: printed chars
 */
int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
				flags, 'x', width, precision, size));
}

/**
 * print_hexa_upper - prints unsigned number in upper hexadecimal
 * @types: list of arguments
 * @buffer: the array to handle print
 * @flags:  calculates flags
 * @width: gets width
 * @precision: the specification
 * @size: Size specifier
 * Return: printed chars
 */
int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
				flags, 'X', width, precision, size));
}

/**
 * print_hexa - prints hex number in lower or upper notation
 * @types: list of arguments
 * @map_to: values to map the number to
 * @buffer: the array to handle print
 * @flags:  calculates flags
 * @flag_ch: calculates flags
 * @width: gets width
 * @precision: the specification
 * @size: the specifier
 * @size: the size specification
 * Return: printed chars
 */
int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int c = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[c--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[c--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		buffer[c--] = flag_ch;
		buffer[c--] = '0';
	}

	c++;

	return (write_unsgnd(0, c, buffer, flags, width, precision, size));
}
