#include "main.h"

/**
* handle_write_char - prints string
* @c: the types of char
* @buffer: the array to handle print
* @flags:  calculates flags
* @width: gets width
* @precision: the specifier
* @size: the size specifier
*
* Return: printed chars
*/
int handle_write_char(char c, char buffer[],
int flags, int width, int precision, int size)
{/* char is stored at left, where paddind is stored at the buffer's right */
int a = 0;
char padd = ' ';

UNUSED(precision);
UNUSED(size);

if (flags & F_ZERO)
padd = '0';

buffer[a++] = c;
buffer[a] = '\0';

if (width > 1)
{
buffer[BUFF_SIZE - 1] = '\0';
for (a = 0; a < width - 1; a++)
buffer[BUFF_SIZE - a - 2] = padd;

if (flags & F_MINUS)
return (write(1, &buffer[0], 1) +
write(1, &buffer[BUFF_SIZE - a - 1], width - 1));
else
return (write(1, &buffer[BUFF_SIZE - a - 1], width - 1) +
write(1, &buffer[0], 1));
}
return (write(1, &buffer[0], 1));
}

/**
* write_number - prints string
* @is_negative: list of arguments
* @ind: types of char
* @buffer: the array to handle print
* @flags:  calculates flags
* @width: gets width
* @precision: the specifier
* @size: the size specifier
*
* Return: printed chars
*/
int write_number(int is_negative, int ind, char buffer[],
int flags, int width, int precision, int size)
{
int length = BUFF_SIZE - ind - 1;
char padd = ' ', extra_ch = 0;

UNUSED(size);

if ((flags & F_ZERO) && !(flags & F_MINUS))
padd = '0';
if (is_negative)
extra_ch = '-';
else if (flags & F_PLUS)
extra_ch = '+';
else if (flags & F_SPACE)
extra_ch = ' ';

return (write_num(ind, buffer, flags, width, precision,
length, padd, extra_ch));
}

/**
* write_num - writes number using bufffer
* @ind: the indx in which number starts on buffer
* @buffer: the buffer
* @flags: the flags
* @width: the width
* @prec: the specifier
* @length: length of the number
* @padd: the pading char
* @extra_c: the extra char
*
* Return: printed chars
*/
int write_num(int ind, char buffer[],
int flags, int width, int prec,
int length, char padd, char extra_c)
{
int c, padd_starts = 1;

if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
return (0); /* printf(".0d", 0)  no char is printed */
if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
buffer[ind] = padd = ' '; /* width is displayed with padding ' ' */
if (prec > 0 && prec < length)
padd = ' ';
while (prec > length)
buffer[--ind] = '0', length++;
if (extra_c != 0)
length++;
if (width > length)
{
for (c = 1; c < width - length + 1; c++)
buffer[c] = padd;
buffer[c] = '\0';
if (flags & F_MINUS && padd == ' ')/* Asign extra char to left of buffer */
{
if (extra_c)
buffer[--ind] = extra_c;
return (write(1, &buffer[ind], length) + write(1, &buffer[1], c - 1));
}
else if (!(flags & F_MINUS) && padd == ' ')/* extra char to left of buff */
{
if (extra_c)
buffer[--ind] = extra_c;
return (write(1, &buffer[1], c - 1) + write(1, &buffer[ind], length));
}
else if (!(flags & F_MINUS) && padd == '0')/* extra char to left of padd */
{
if (extra_c)
buffer[--padd_starts] = extra_c;
return (write(1, &buffer[padd_starts], c - padd_starts) +
write(1, &buffer[ind], length - (1 - padd_starts)));
}
}
if (extra_c)
buffer[--ind] = extra_c;
return (write(1, &buffer[ind], length));
}

/**
* write_unsgnd - writes unsigned number
* @is_negative: indicates if number is negative
* @ind: indx in which number starts in buffer
* @buffer: the array of chars
* @flags: the flag specifiers
* @width: the width specifier
* @precision: the specifier
@size: the size specifier
*
* Return: printed chars
*/
int write_unsgnd(int is_negative, int ind,
char buffer[],
int flags, int width, int precision, int size)
{
/*Number is stored at right side of buffer, where as c starts at position */
int length = BUFF_SIZE - ind - 1, c = 0;
char padd = ' ';

UNUSED(is_negative);
UNUSED(size);

if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
return (0); /* printf(".0d", 0)  no char is printed */

if (precision > 0 && precision < length)
padd = ' ';

while (precision > length)
{
buffer[--ind] = '0';
length++;
}

if ((flags & F_ZERO) && !(flags & F_MINUS))
padd = '0';

if (width > length)
{
for (c = 0; c < width - length; c++)
buffer[c] = padd;

buffer[c] = '\0';

if (flags & F_MINUS) /* Asigns extra char to left of buffer [buffer>padd]*/
{
return (write(1, &buffer[ind], length) + write(1, &buffer[0], c));
}
else /* Asigns extra char to left of padding [padd>buffer]*/
{
return (write(1, &buffer[0], c) + write(1, &buffer[ind], length));
}
}
return (write(1, &buffer[ind], length));
}

/**
* write_pointer - Write a memory address
* @buffer: Arrays of chars
* @ind: Index at which the number starts in the buffer
* @length: Length of number
* @width: Wwidth specifier
* @flags: Flags specifier
* @padd: Char representing the padding
* @extra_c: Char representing extra char
* @padd_start: Index at which padding should start
*
* Return: Number of written chars
*/
int write_pointer(char buffer[], int ind, int length,
int width, int flags, char padd, char extra_c, int padd_start)
{
int c;

if (width > length)
{
for (c = 3; c < width - length + 3; c++)
buffer[c] = padd;
buffer[c] = '\0';
if (flags & F_MINUS && padd == ' ')/* Asign extra char to left of buffer */
{
buffer[--ind] = 'x';
buffer[--ind] = '0';
if (extra_c)
buffer[--ind] = extra_c;
return (write(1, &buffer[ind], length) + write(1, &buffer[3], c - 3));
}
else if (!(flags & F_MINUS) && padd == ' ')/* extra char to left of buffer */
{
buffer[--ind] = 'x';
buffer[--ind] = '0';
if (extra_c)
buffer[--ind] = extra_c;
return (write(1, &buffer[3], c - 3) + write(1, &buffer[ind], length));
}
else if (!(flags & F_MINUS) && padd == '0')/* extra char to left of padd */
{
if (extra_c)
buffer[--padd_start] = extra_c;
buffer[1] = '0';
buffer[2] = 'x';
return (write(1, &buffer[padd_start], c - padd_start) +
write(1, &buffer[ind], length - (1 - padd_start) - 2));
}
}
buffer[--ind] = 'x';
buffer[--ind] = '0';
if (extra_c)
buffer[--ind] = extra_c;
return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}
