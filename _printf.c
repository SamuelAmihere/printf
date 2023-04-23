#include "main.h"

/**
 * _printf - Printf function
 *
 * @format: format.
 *
 * Return: Printed chars.
 */
int _printf(const char *format, ...)
{
	int i = 0, printed_chars = 0, buff_ind = 0;
	int flags, width, precision, size;
	int printed = 0;
	char buffer[BUFF_SIZE];
	va_list list;

	if (format == NULL)
		return (-1);

	va_start(list, format);

	while (format[i] != '\0')
	{
		if (format[i] != '%')
		{
			buffer[buff_ind++] = format[i++];
			if (buff_ind == BUFF_SIZE)
				printed_chars += print_buffer(buffer, &buff_ind);
		}
		else
		{
			printed_chars += print_buffer(buffer, &buff_ind);
			flags = get_flags(format, &i);
			width = get_width(format, &i, list);
			precision = get_precision(format, &i, list);
			size = get_size(format, &i);
			++i;
			printed = handle_print(format, &i, list, buffer,
					flags, width, precision, size);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
	}
	printed_chars += print_buffer(buffer, &buff_ind);

	va_end(list);

	return (printed_chars);

}
