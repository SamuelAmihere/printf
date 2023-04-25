#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#define UNUSED(x) (void)(x)
#define BUFF_SIZE 1024

/* write_buffer - CONDTIONALS*/
#define IS_ZERO_PREC_IND_WIDTH(prec, ind, width)\
	(prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
#define IS_ZERO_PREC_IND(prec, ind)\
	(prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
#define NEED_PADDING(prec, length)\
	(prec > 0 && prec < length)
#define NEED_EXTRA_CHAR(extra_c)\
	(extra_c != 0)
#define NEED_WIDTH_PADDING(width, length)\
	(width > length)

/* write_unsgned - CONDTIONALS */
#define IS_ZERO_PRECISION(prec, idx, buffer)\
	((prec) == 0 && (idx) == BUFF_SIZE - 2 && (buffer)[idx] == '0')
#define IS_FLAG_SET(flags, flag) ((flags) & (flag))
#define IS_ZERO_PADDING(flags) (IS_FLAG_SET(flags, F_ZERO) &&\
		!IS_FLAG_SET(flags, F_MINUS))
#define IS_PRECISION_GT_LENGTH(precision, len) ((precision) > (len))
#define IS_WIDTH_GT_LENGTH(width, len) ((width) > (len))

/* write_pointer - CONDTIONALS*/
#define IS_FLAG_MINUS(flags) ((flags) & F_MINUS)
#define IS_FLAG_ZERO(flags) ((flags) & F_ZERO)
#define IS_VALID_EXTRA_CHAR(c) ((c) != '\0')

/* print_string -  CONDITIONALS*/
#define IS_NULL_STRING(str) (str == NULL)
#define HAS_PRECISION(precision) (precision >= 0 && precision < length)
#define NEED_PADDING_W(width, length) (width > length)

/* FLAGS */
#define F_MINUS 1
#define F_PLUS 2
#define F_ZERO 4
#define F_HASH 8
#define F_SPACE 16

/* SIZES */
#define S_LONG 2
#define S_SHORT 1

/**
 * struct fmt - Struct op
 *
 * @fmt: The format.
 * @fn: The function associated.
 */
struct fmt
{
	char fmt;
	int (*fn)(va_list, char[], int, int, int, int);
};


/**
 * typedef struct fmt fmt_t - Struct op
 *
 * @fmt: The format.
 * @fm_t: The function associated.
 */
typedef struct fmt fmt_t;

int _printf(const char *format, ...);
int handle_print(const char *fmt, int *i,
va_list list, char buffer[], int flags, int width, int precision, int size);

/****************** FUNCTIONS ******************/

/* Funtions to print chars and strings */
int print_char(va_list args, char buffer[],
	int flags, int width, int precision, int size);
int print_string(va_list args, char buffer[],
	int flags, int width, int precision, int size);
int print_percent(va_list args, char buffer[],
	int flags, int width, int precision, int size);

/* Functions to print numbers */
int print_int(va_list args, char buffer[],
	int flags, int width, int precision, int size);
int print_binary(va_list args, char buffer[],
	int flags, int width, int precision, int size);
int print_unsigned(va_list args, char buffer[],
	int flags, int width, int precision, int size);
int print_octal(va_list args, char buffer[],
	int flags, int width, int precision, int size);
int print_hexadecimal(va_list args, char buffer[],
	int flags, int width, int precision, int size);
int print_hexa_upper(va_list args, char buffer[],
	int flags, int width, int precision, int size);

int print_hexa(va_list args, char map_to[],
char buffer[], int flags, char flag_ch, int width, int precision, int size);

/* Function to print non printable characters */
int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size);

/* Funcion to print memory address */
int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size);

/* Funciotns to handle other specifiers */
int get_flags(const char *format, int *i);
int get_width(const char *format, int *i, va_list list);
int get_precision(const char *format, int *i, va_list list);
int get_size(const char *format, int *i);

/*Function to print string in reverse*/
int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size);

/*Function to print a string in rot 13*/
int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size);

/* width handler */
int handle_write_char(char c, char buffer[],
	int flags, int width, int precision, int size);
int write_number(int is_positive, int ind, char buffer[],
		int flags, int width, int precision, int size);
int write_num(int idx, char buffer[], int flags, int width, int precision,
		int len, char padd, char extra_char);
int write_buffer(char buffer[], int start, int len, *int flags, char padd);
int write_pointer(char buffer[], int idx, int len,
	int width, int flags, char padd, char extra_c, int padd_start);

int write_unsgnd(int is_negative_flag, int idx, char buffer[],
	int flags, int width, int precision, int size);

/****************** UTILS ******************/
int is_printable(char);
int append_hexa_code(char, char[], int);
int is_digit(char);

long int convert_size_number(long int num, int size);
long int convert_size_unsgnd(unsigned long int num, int size);

#endif
