#include "main.h"
/**
 * get_flags - flags active
 * @format: formatted string
 * @i: argument
 * Return: flag
 */
int get_flags(const char *format, int *i)
{
	int x, curr_x, flagss = 0;
	const char FLAGS[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARRAY[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (curr_x = *i + 1; format[curr_x] != '\0'; curr_x++)
	{
		for (x = 0; FLAGS[x] != '\0'; x++)
			if (format[curr_x] == FLAGS[x])
			{
				flagss |= FLAGS_ARRAY[x];
				break;
			}

		if (FLAGS[x] == 0)
			break;
	}
	*i = curr_x - 1;
	return (flags);
}
