#include "main.h"

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
		if (HAS_PRECISION(precision))
			str = "      ";
	}

	while (str[len] != '\0')
		len++;

	if (HAS_PRECISION(precision))
		len = precision;

	if (NEED_PADDING(width, len))
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
