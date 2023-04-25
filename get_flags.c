#include "main.h"

/**
 * get_flags - Finds active flags
 *
 * @format: Formatted string to print the arguments to
 * @i: take a parameter.
 * Return: Flags:
 */
int get_flags(const char *format, int *i)
{
	int j, cur_i, flags = 0;
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO,
		F_HASH, F_SPACE, 0};
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};

	cur_i = *i + 1;
	while (format[cur_i] != '\0')
	{
		j = 0;
		while (FLAGS_CH[j] != '\0')
		{
			if (format[cur_i] == FLAGS_CH[j])
			{
				flags |= FLAGS_ARR[j];
				break;
			}
			j++;
		}
		if (FLAGS_CH[j] == 0)
			break;
		cur_i++;
	}

	*i = cur_i - 1;

	return (flags);
}
