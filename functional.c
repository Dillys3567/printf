#include "main.h"
/**
 * print_char - print char
 * @types: list of arg
 * @buffer: buffer array
 * @flags: active flags
 * @width: width
 * @precision: precision
 * @size: size
 * Return: number of chars
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char ch = va_arg(types, int);

	return (handle_write_char(ch, buffer, flags, width, precision, size));
}
/**
 * print_string - print string
 * @types: list of arg
 * @buffer: buffer array
 * @flags: active flags
 * @width: width
 * @precision: precision
 * @size: size
 * Return: number of chars
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int len = 0, x;
	char *st = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (st == NULL)
	{
		st = "(null)";
		if (precision >= 6)
			st = "      ";
	}
	while (st[len] != '\0')
		len++;
	if ((precision >= 0) && (precision < len))
		len = precision;
	if (width > len)
	{
		if (flags & F_MINUS)
		{
			write(1, &st[0], len);
			for (x = width - len; x > 0; x--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (x = width - len; x > 0; x--)
				write(1, " ", 1);
			write(1, &st[0], len);
			return (width);
		}
	}
	return (write(1, st, len));
}
/**
 * print_percent - print %
 * @types: list of args
 * @buffer: buffer array
 * @flags: active flags
 * @width: width
 * @precision: precision
 * @size: size
 * Return: number of chars
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
 * print_int - print integer
 * @types: list of args
 * @buffer: buffer array
 * @flags: active flags
 * @width: width
 * @precision: precision
 * @size: size
 * Return: number of chars
 */
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int x = BUFF_SIZE - 2, is_neg = 0;
	long int m = va_arg(types, long int);
	unsigned long int numb;

	m = convert_size_number(m, size);
	if (m == 0)
		buffer[x--] = '0';
	buffer[BUFF_SIZE - 1] = '\0';
	numb = (unsigned long int)m;
	if (m < 0)
	{
		numb = (unsigned long int)((-1) * m);
		is_neg = 1;
	}
	while (numb > 0)
	{
		buffer[x--] = (numb % 10) + '0';
		numb /= 10;
	}
	x++;
	return (write_number(is_neg, x, buffer, flags, width, precision, size));
}
/**
 * print_binary - unsigned number
 * @types: list of args
 * @buffer: buffer array
 * @flags: active flag
 * @width: width
 * @precision: precision
 * @size: size
 * Return: number of chars
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int y, x, j, sums, counter;
	unsigned int b[32];

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	y = va_arg(types, unsigned int);
	x = 2147483648;
	b[0] = y / x;
	for (j = 1; j < 32; j++)
	{
		x /= 2;
		b[j] = (y / x) % 2;
	}
	for (j = 0, sums = 0, counter = 0; j < 32; j++)
	{
		sums += b[j];
		if (sums || (j == 31))
		{
			char w = '0' + b[j];

			write(1, &w, 1);
			counter++;
		}
	}
	return (counter);
}
