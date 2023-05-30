#include "main.h"
/**
 * print_buffer - print buffer content
 * @buffer: char array
 * @buff_ind: index of next char
 */
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
	{
		write(1, &buffer[0], *buff_ind);
	}
	*buff_ind = 0;
}
/**
 * _printf - printf
 * @format: format
 * Return: int of chars
 */
int _printf(const char *format, ...)
{
	int x, print = 0, print_char = 0, flag, wid, precise, sizes, index = 0;
	va_list ls;
	char buff[BUFF_SIZE];

	if (format == NULL)
		return (-1);
	va_start(ls, format);
	for (x = 0; format && format[x] != '\0'; x++)
	{
		if (format[x] != '%')
		{
			buff[index++] = format[x];
			if (index == BUFF_SIZE)
				print_buffer(buff, &index);
			print_char++;
		}
		else
		{
			print_buffer(buff, &index);
			flag = get_flags(format, &x);
			wid = get_width(format, &x, ls);
			precise = get_precision(format, &x, ls);
			sizes = get_size(format, &x);
			++x;
			print = handle_print(format, &x, ls, buff, flag, wid, precise, sizes);
			if (print == -1)
				return (-1);
			print_char += print;
		}
	}
	print_buffer(buff, &index);
	va_end(ls);
	return (print_char);
}
