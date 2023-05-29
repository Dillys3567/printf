#include "main.h"
/**
 * print_unsigned - print unsigned
 * @types: list of args
 * @buffer: buffer array
 * @flags: flags active
 * @width: width
 * @precision: precision
 * @size: size
 * Return: number of chars
 */
int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int x = BUFF_SIZE - 2;
	unsigned long int numb = va_arg(types, unsigned long int);

	numb = convert_size_unsgnd(numb, size);
	if (numb == 0)
		buffer[x--] = '0';
	buffer[BUFF_SIZE - 1] = '\0';
	while (numb > 0)
	{
		buffer[x--] = (numb % 10) + '0';
		numb /= 10;
	}
	x++;
	return (write_unsgnd(0, x, buffer, flags, width, precision, size));
}
/**
 * print_octal - octal notattion
 * @types: list of args
 * @buffer: buffer array
 * @flags: flags active
 * @width: width
 * @precision: precision
 * @size: size
 * Return: number of chars
 */
int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int x = BUFF_SIZE - 2;
	unsigned long int numb = va_arg(types, unsigned long int);
	unsigned long int init_numb = numb;

	UNUSED(width);
	numb = convert_size_unsgnd(numb, size);
	if (numb == 0)
		buffer[x--] = '0';
	buffer[BUFF_SIZE - 1] = '\0';
	while (numb > 0)
	{
		buffer[x--] = (numb % 8) + '0';
		numb /= 8;
	}
	if (flags & F_HASH && init_numb != 0)
		buffer[x--] = '0';
	x++;
	return (write_unsgnd(0, x, buffer, flags, width, precision, size));
}
/**
 * print_hexadecimal - hexadecimal
 * @types: List of ars
 * @buffer: Buffer array
 * @flags: active flags
 * @width: width
 * @precision: Precision
 * @size: Size
 * Return: Number of chars
 */
int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}
/**
 * print_hexa_upper - hex upper
 * @types: List of args
 * @buffer: Buffer array
 * @flags: active flags
 * @width: width
 * @precision: Precision
 * @size: Size
 * Return: Number of chars
 */
int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}
/**
 * print_hexa - hex numb
 * @types: List of args
 * @map_to: Array to map
 * @buffer: Buffer array * @flags:  Calculates active flags
 * @flag_ch: active flags
 * @flags: flags
 * @width: width
 * @precision: Precision
 * @size: Size
 * Return: Number of chars
 */
int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int x = BUFF_SIZE - 2;
	unsigned long int numb = va_arg(types, unsigned long int);
	unsigned long int init_numb = numb;

	UNUSED(width);
	numb = convert_size_unsgnd(numb, size);
	if (numb == 0)
		buffer[x--] = '0';
	buffer[BUFF_SIZE - 1] = '\0';
	while (numb > 0)
	{
		buffer[x--] = map_to[numb % 16];
		numb /= 16;
	}
	if (flags & F_HASH && init_numb != 0)
	{
		buffer[x--] = flag_ch;
		buffer[x--] = '0';
	}
	x++;
	return (write_unsgnd(0, x, buffer, flags, width, precision, size));
}
