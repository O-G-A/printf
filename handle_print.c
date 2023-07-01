#include "main.h"

/**
* handle_print - prints argument on the bases of it type
* @fmt: formatted string in which argument is printed
* @list: list of arguments
* @ind: the index
* @buffer: the array to handle print
* @flags: calculates flags
* @width: gets width
* @precision: the specification
* @size: the specifier
* Return: 1 or 2;
*/
int handle_print(const char *fmt, int *ind, va_list list, char buffer[],
int flags, int width, int precision, int size)
{
int c, unknow_len = 0, printed_chars = -1;

fmt_t fmt_types[] = {
{'c', print_char}, {'s', print_string}, {'%', print_percent},
{'i', print_int}, {'d', print_int}, {'b', print_binary},
{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
};
for (c = 0; fmt_types[c].fmt != '\0'; c++)
if (fmt[*ind] == fmt_types[c].fmt)
return (fmt_types[c].fn(list, buffer, flags, width, precision, size));

if (fmt_types[c].fmt == '\0')
{
if (fmt[*ind] == '\0')
return (-1);
unknow_len += write(1, "%%", 1);
if (fmt[*ind - 1] == ' ')
unknow_len += write(1, " ", 1);
else if (width)
{
--(*ind);
while (fmt[*ind] != ' ' && fmt[*ind] != '%')
--(*ind);
if (fmt[*ind] == ' ')
--(*ind);
return (1);
}
unknow_len += write(1, &fmt[*ind], 1);
return (unknow_len);
}
return (printed_chars);
}
