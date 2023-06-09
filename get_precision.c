#include "main.h"

/**
 * get_precision - Finds the precision for printing
 *
 * @format: Formatted string in which to print the arguments
 * @i: List of arguments to be printed.
 * @args: arg.
 *
 * Return: Precision.
 */
int get_precision(const char *format, int *i, va_list args)
{
	int prec = -1, curr_i = *i + 1;

	if (format[curr_i] != '.')
		return (prec);

	prec = 0;

	while (format[curr_i] != '\0')
	{
		if (is_digit(format[curr_i]))
		{
			prec *= 0;
			prec += format[curr_i] - '0';
			curr_i++;
		} else if (format[curr_i] == '*')
		{
			curr_i++;
			prec = va_arg(args, int);
			break;
		}
		else
			break;
	}

	*i = curr_i - 1;

	return (prec);
}
