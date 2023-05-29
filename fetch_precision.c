#include "main.h"
/**
 * get_precision - get precision
 * @format: formatted string
 * @i: list of args
 * @list: list of args
 * Return: precision
 */
int get_precision(const char *format, int *i, va_list list)
{
	int curr_x = *i + 1;
	int precise = -1;

	if (format[curr_x] != '.')
		return (precise);

	precise = 0;

	for (curr_x += 1; format[curr_x] != '\0'; curr_x++)
	{
		if (is_digit(format[curr_x]))
		{
			precise *= 10;
			precise += format[curr_x] - '0';
		}
		else if (format[curr_x] == '*')
		{
			curr_x++;
			precise = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = curr_x - 1;

	return (precise);
}

