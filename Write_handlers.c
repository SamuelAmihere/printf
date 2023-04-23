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
 * write_num - Writes a number to a buffer array
 *
 * @is_negative: Whether the number is negative (1) or not (0)
 * @buffer_index: The index of the buffer array to write to
 * @buffer: The buffer array to write the number to
 * @flags: The active flags for formatting the number
 * @width: The width specifier for the number
 * @precision: The precision specifier for the number
 * @size: The size specifier for the number
 * Return: The number of characters written
 */
int write_num(int is_negative, int buffer_index, char buffer[],
		int flags, int width, int precision, int size)
{
	int i, padd_start = 1;

	if (IS_ZERO_PREC_IND_WIDTH(prec, ind, width))
		return (0);

	if (IS_ZERO_PREC_IND(prec, ind))
		buffer[ind] = padd = ' ';
	if (NEED_PADDING(prec, length))
	{
		while (prec > length)
			buffer[--ind] = '0', length++;
	}

	if (NEED_EXTRA_CHAR(extra_c))
		length++;

	if (NEED_WIDTH_PADDING(width, length))
	{
		for (i = 1; i < width - length + 1; i++)
			buffer[i] = padd;
		buffer[i] = '\0';
	}

	if (NEED_EXTRA_CHAR(extra_c))
		buffer[--ind] = extra_c;

	return (write_buffer(buffer, ind, length, flags, padd));

}


/**
 * write_buffer - Writes the contents of the buffer to stdout.
 * @buffer: The buffer containing the data to write.
 * @start: The index of the first character in the buffer to write.
 * @len: The number of characters in the buffer to write.
 * @flags: The formatting flags to apply.
 * @padd: The padding character to use.
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

/** TO DO
 * 1. Add protopyte: int write_buffer(char buffer[], int start, int len,
 * int flags, char padd) to the [main.h] (---width handler----)
 *
 * 2. Add conditional macros used by write_num function in [main.h]. Get them
 * at CGPT.
 *
 * 3. Add int write_unsgnd(int is_negative, int ind,char buffer[], int flags,
 * int width, int precision, int size) [here].
 *
 * 4. Add int write_pointer(char buffer[], int ind, int length,int width,
 * int flags, char padd, char extra_c, int padd_start) [here].
 * Return: nothing
 */
