#include "main.h"
/**
 * print_pointer - print pointer
 * @types: List of args
 * @buffer: buffer array
 * @flags: active flags
 * @width: width
 * @precision: precision
 * @size: size
 * Return: number of chars
 */
int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char ext_c = 0, pad = ' ';
	int index = BUFF_SIZE - 2, len = 2, pad_st = 1;
	unsigned long num_addr;
	char maps_to[] = "0123456789abcdef";
	void *addr = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);
	if (addr == NULL)
		return (write(1, "(nil)", 5));
	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);
	num_addr = (unsigned long)addr;
	while (num_addr > 0)
	{
		buffer[index--] = maps_to[num_addr % 16];
		num_addr /= 16;
		len++;
	}
	if ((flags & F_ZERO) && !(flags & F_MINUS))
		pad = '0';
	if (flags & F_PLUS)
		ext_c = '+', len++;
	else if (flags & F_SPACE)
		ext_c = ' ', len++;
	index++;
	return (write_pointer(buffer, index, len,
		width, flags, pad, ext_c, pad_st));
}
/**
 * print_non_printable - ascii to hex
 * @types: List of args
 * @buffer: Buffer array
 * @flags: active flags
 * @width: width
 * @precision: Precision
 * @size: Size
 * Return: Number of chars
 */
int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int x = 0, offsets = 0;
	char *st = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (st == NULL)
		return (write(1, "(null)", 6));
	while (st[i] != '\0')
	{
		if (is_printable(st[i]))
			buffer[x + offsets] = st[i];
		else
			offsets += append_hexa_code(st[x], buffer, x + offsets);
		x++;
	}
	buffer[x + offsets] = '\0';
	return (write(1, buffer, x + offsets));
}
/**
 * print_reverse - reverse string.
 * @types: List of args
 * @buffer: Buffer array
 * @flags: active flags
 * @width: width
 * @precision: Precision
 * @size: Size
 * Return: Numbers of chars
 */
int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *st;
	int x, counter = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);
	st = va_arg(types, char *);
	if (st == NULL)
	{
		UNUSED(precision);
		st = ")Null(";
	}
	for (x = 0; st[i]; x++)
		;
	for (x = x - 1; x >= 0; x--)
	{
		char w = st[x];

		write(1, &w, 1);
		counter++;
	}
	return (counter);
}
/**
 * print_rot13string - rot13.
 * @types: List of ags
 * @buffer: Buffer array
 * @flags: active flags
 * @width: width
 * @precision: Precision
 * @size: Size
 * Return: Numbers of chars
 */
int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char i, *st;
	unsigned int x, y;
	int counter = 0;
	char ins[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char outs[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	st = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (st == NULL)
		st = "(AHYY)";
	for (x = 0; st[x]; x++)
	{
		for (y = 0; ins[y]; y++)
		{
			if (ins[y] == st[x])
			{
				i = outs[y];
				write(1, &i, 1);
				counter++;
				break;
			}
		}
		if (!ins[y])
		{
			i = st[x];
			write(1, &i, 1);
			counter++;
		}
	}
	return (counter);
}
