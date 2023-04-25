#include "main.h"

/*------------------------ WRITE STRING ---------------------*/

/**
 * print_string - Prints a string
 *
 * @args: arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 *
 * Return: Number of chars printed
 */
int print_string(va_list args, char buffer[], int flags, int width,
		int precision, int size)
{
	int len = 0, i;
	char *str = va_arg(args, char *);

	UNUSED(size);
	UNUSED(width);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(precision);

	if (IS_NULL_STRING(str))
	{
		str = "(null)";
		if (HAS_PRECISION(precision, len))
			str = "      ";
	}

	while (str[len] != '\0')
		len++;

	if (HAS_PRECISION(precision, len))
		len = precision;

	if (NEED_PADDING_W(width, len))
	{
		if (IS_FLAG_MINUS(flags))
		{
			write(1, &str[0], len);
			for (i = width - len; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}

		for (i = width - len; i > 0; i--)
			write(1, " ", 1);
		write(1, &str[0], len);
		return (width);
	}

	return (write(1, str, len));
}


/*------------------------ WRITE CHAR ---------------------*/

/**
 * print_char - Prints a char
 *
 * @args: arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 *
 * Return: Number of chars printed
 */
int print_char(va_list args, char buffer[], int flags, int width,
		int precision, int size)
{
	char s = va_arg(args, int);

	return (handle_write_char(s, buffer, flags, width,
				precision, size));
}


/*---------------------- WRITE PERCENT (%) ----------------*/

/**
 * print_percent - Print %
 *
 * @args: arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 *
 * Return: Number of chars printed
 */
int print_percent(va_list args, char buffer[], int flags,
		int width, int precision, int size)
{
	UNUSED(precision);
	UNUSED(width);
	UNUSED(args);
	UNUSED(flags);
	UNUSED(size);
	UNUSED(buffer);

	return (write(1, "%%", 1));
}


/*---------------------- WRITE INTEGGERS ----------------*/

/**
 * print_int - Print integer
 *
 * @args: arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 *
 * Return: Number of chars printed
 */
int print_int(va_list args, char buffer[], int flags, int width,
		int precision, int size)
{
	int negative = 0, i = BUFF_SIZE - 2;
	unsigned long int n;
	long int num = va_arg(args, long int);

	num = convert_size_number(num, size);

	if (num == 0)
		buffer[i--] = '0';
	buffer[BUFF_SIZE - 1] = '\0';
	n = (unsigned long int)num;

	if (num < 0)
	{
		n = (unsigned long int)((-1) * n);
		negative = 1;
	}

	while (n > 0)
	{
		buffer[i--] = (n % 10) + '0';
		n /= 10;
	}
	i++;

	return (write_number(negative, i, buffer, flags, width,
				precision, size));
}

/*---------------------- WRITE BINARY NUMBERS ----------------*/

/**
 * print_binary - Printsunsigned numbers
 *
 * @args: arguments
 * @buffer: Buffer array to handle print
 * @flags:  Determines active flags
 * @width: get width.
 * @precision: specifies precision
 * @size: Size specifier
 *
 * Return: Numbers of char printed.
 */
int print_binary(va_list args, char buffer[], int flags, int width,
		int precision, int size)
{
	int count;
	unsigned int num, i, j, sum;
	unsigned int a[32];
	char z;

	UNUSED(width);
	UNUSED(size);
	UNUSED(flags);
	UNUSED(buffer);
	UNUSED(precision);

	num = va_arg(args, unsigned int);
	j = 2147483648;
	a[0] = num / j;

	i = 1;
	while (i < 32)
	{
		j /= 2;
		a[i] = (num / j) % 2;
		i++;
	}
	i = 0;
	count = 0;
	sum = 0;
	while (i < 32)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			z = '0' + a[i];
			write(1, &z, 1);
			count++;
		}
		i++;
	}

	return (count);

}
