#include "main.h"

/**
* get_width - calculates width for the printing
* @format: formatted string in which argument is printed
* @i: list of arguments to be printed
* @list: list of arguments
*
* Return: the width
*/
int get_width(const char *format, int *i, va_list list)
{
int curr_a;
int width = 0;

for (curr_a = *i + 1; format[curr_a] != '\0'; curr_a++)
{
if (is_digit(format[curr_a]))
{
width *= 10;
width += format[curr_a] - '0';
}
else if (format[curr_a] == '*')
{
curr_a++;
width = va_arg(list, int);
break;
}
else

break;
}
*i = curr_a - 1;

return (width);
}
