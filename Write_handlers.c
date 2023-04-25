#include "main.h"

/**
 * handle_write_char - Handles the printing of a single character
 * @c: char types.
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags.
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int handle_write_char(char c, char buffer[],
		int flags, int width, int precision, int size)
{
	int i = 0;
	/* Unused parameters */
	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
	{
		padding_char = '0';
	}

	buffer[i++] = c;
	buffer[i] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (i = 0; i < width - 1; i++)
		{
			buffer[BUFF_SIZE - i - 2] = padding_char;
		}

		if (flags & F_MINUS)
			return write(1, &buffer[0], 1) + write(1,
					&buffer[BUFF_SIZE - i - 1], width - 1);
		else
			return write(1, &buffer[BUFF_SIZE - i - 1],
					width - 1) + write(1, &buffer[0], 1);
	}

	return (write(1, &buffer[0], 1));
}

/**
 * write_num - Writes a number
 *
 * @idx: starting index of the number in buffer
 * @buffer: The buffer array to write the number to
 * @flags: The active flags for formatting the number
 * @width: The width specifier for the number
 * @precision: The precision specifier for the number
 * @len: Length of number
 * @padd: A padding character
 * @extra_char: Extra character
 *
 * Return: The number of characters written
 */
int write_num(int idx, char buffer[], int flags, int width, int precision,
		int len, char padd, char extra_char)
{
	int i, padd_start = 1;

	if (IS_ZERO_PREC_IND_WIDTH(precision, idx, width))
		return (0);

	if (IS_ZERO_PREC_IND(precision, idx))
		buffer[idx] = padd = ' ';
	if (NEED_PADDING(precision, len))
	{
		while (precision > len)
			buffer[--idx] = '0', len++;
	}

	if (NEED_EXTRA_CHAR(extra_char))
		len++;

	if (NEED_WIDTH_PADDING(width, len))
	{
		for (i = 1; i < width - len + 1; i++)
			buffer[i] = padd;
		buffer[i] = '\0';
	}

	if (NEED_EXTRA_CHAR(extra_char))
		buffer[--idx] = extra_char;

	return (write_buffer(buffer, idx, len, flags, padd));

}


/**
 * write_buffer - Writes the contents of the buffer to stdout.
 *
 * @buffer: The buffer containing the data to write.
 * @start: The index of the first character in the buffer to write.
 * @len: The number of characters in the buffer to write.
 * @flags: The formatting flags to apply.
 * @padd: The padding character to use.
 *
 * Return: The number of characters written.
 */
int write_buffer(char buffer[], int start, int len, int flags, char padd)
{
	int written = 0;

	if (flags & F_MINUS)
	{
		written += write(1, &buffer[start], len);
		while (written < width)
			written += write(1, &padd, 1);
	}
	else
	{
		while (written < width - len)
			written += write(1, &padd, 1);
		written += write(1, &buffer[start], len);
	}

	return (written);
}

/**
 * write_unsgnd - writes unsigned number
 *
 * @is_negative_flag: Flag indicating if the number is negative
 * @idx: Index at which the number starts in the buffer
 * @buffer: Array of characters
 * @flags: Flags specifiers
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of characters written
 */
int write_unsgnd(int is_negative_flag, int idx, char buffer[],
		int flags, int width, int precision, int size)
{
	int i = 0, len = BUFF_SIZE - idx - 1;
	char pad = IS_ZERO_PADDING(flags) ? '0' : ' ';

	UNUSED(size);
	UNUSED(is_negative_flag);

	if (IS_ZERO_PRECISION(precision, idx, buffer))
		return (0);
	while (IS_PRECISION_GT_LENGTH(precision, len))
	{
		buffer[--idx] = '0';
		len++;
	}

	if (IS_WIDTH_GT_LENGTH(width, len))
	{
		for (i = 0; i < width - len; i++)
			buffer[i] = padd;

		buffer[i] = '\0';

		if (IS_FLAG_SET(flags, F_MINUS))
			return (write(1, &buffer[idx], len) + write(1,
						&buffer[0], i));
		else
			return (write(1, &buffer[0], i) + write(1, &buffer[idx],
						len));
	}

	return (write(1, &buffer[idx], len));

}

/**
 * write_pointer - Write a memory address of pointer
 *
 * @buffer: Arrays of chars
 * @idx: Index at which the number starts in the buffer
 * @len: Length of number
 * @width: Width specifier
 * @flags: Flags specifier
 * @padd: Char representing the padding
 * @extra_c: Char representing extra char
 * @padd_start: Index at which padding should start
 *
 * Return: Number of written chars.
 */
int write_pointer(char buffer[], int idx, int len, int width, int flags,
		char padd, char extra_c, int padd_start)
{
	int i;

	if (IS_WIDTH_GT_LENGTH)
	{
		for (i = 3; i < width - len + 3; i++)
			buffer[i] = padd;
		buffer[i] = '\0';
		if (IS_FLAG_MINUS(flags) && padd == ' ')
		{
			buffer[--idx] = 'x';
			buffer[--idx] = '0';
			if (IS_VALID_EXTRA_CHAR(extra_c))
				buffer[--idx] = extra_c;
			return (write(1, &buffer[idx], len) + write(1, &buffer[3],
						i - 3));
		} else if (!IS_FLAG_MINUS(flags) && padd == '0')
		{
			if (IS_VALID_EXTRA_CHAR(extra_c))
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], i - padd_start) +
					write(1, &buffer[idx], len - (1 -
							padd_start) - 2));
		}
	}
	buffer[--idx] = 'x';
	buffer[--idx] = '0';
	if (IS_VALID_EXTRA_CHAR(extra_c))
		buffer[--idx] = extra_c;
	return (write(1, &buffer[idx], BUFF_SIZE - idx - 1));
}
