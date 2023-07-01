#include "main.h"

/**
* is_printable - evaluates char, if it's printable
* @c: the char evaluate
*
* Return: 1 if the char is printable, 0 if otherwise
*/
int is_printable(char c)
{
if (c >= 32 && c < 127)
return (1);

return (0);
}

/**
* append_hexa_code - append ASCII in hexa to buffer
* @buffer: the array of chars
* @i: the ind at which appending to starts
* @ascii_code: the ASCII code
* Return: 3 Always
*/
int append_hexa_code(char ascii_code, char buffer[], int i)
{
char map_to[] = "0123456789ABCDEF";
/* Hexadecimal code is always 2 digits long */
if (ascii_code < 0)
ascii_code *= -1;

buffer[i++] = '\\';
buffer[i++] = 'x';

buffer[i++] = map_to[ascii_code / 16];
buffer[i] = map_to[ascii_code % 16];

}

/**
* is_digit - verifies char, if it's a digit or not
* @c: the char to be evaluated
*
* Return: 1 if char is digit, 0 if not
*/
int is_digit(char c)
{
if (c >= '0' && c <= '9')
return (1);

return (0);
}

/**
* convert_size_number - casts number to specified size
* @num: the number to be casted
* @size: indicates the type that would be casted
*
* Return: the casted value
*/
long int convert_size_number(long int num, int size)
{
if (size == S_LONG)
return (num);
else if (size == S_SHORT)
return ((short)num);

return ((int)num);
}

/**
* convert_size_unsgnd - casts number to specified size
* @num: the number that would be casted
* @size: indicates the type that would be casted
*
* Return: casted value of the number
*/
long int convert_size_unsgnd(unsigned long int num, int size)
{
if (size == S_LONG)
return (num);
else if (size == S_SHORT)
return ((unsigned short)num);

return ((unsigned int)num);
}
