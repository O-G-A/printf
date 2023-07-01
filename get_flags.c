#include "main.h"

/**
 * get_flags - calculates flags
 * @format: the formatted strg in argument is printed
 * @i: takes parameter
 * Return: the flags:
 */
int get_flags(const char *format, int *i)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8  16 */
	int b, curr_a;
	int flags = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (curr_a = *i + 1; format[curr_a] != '\0'; curr_a++)
	{
		for (b = 0; FLAGS_CH[b] != '\0'; b++)
			if (format[curr_a] == FLAGS_CH[b])
			{
				flags |= FLAGS_ARR[b];
				break;
			}

		if (FLAGS_CH[b] == 0)
			break;
	}

	*i = curr_a - 1;

	return (flags);
}
