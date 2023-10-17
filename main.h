#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#define UNUSED(x) (void)(x)
#define BUFF_SIZE 1024

/* FLAG */
#define F_MINUS 1
#define F_PLUS 2
#define F_ZERO 4
#define F_HASH 8
#define F_SPACE 16

/* SIZES */
#define S_LONG 2
#define S_SHORT 1

/**
 * struct frmt - Struct op
 *
 * @frmt: The format.
 * @fn: The function associated.
 */
struct frmt
{
	char frmt;
	int (*fn)(va_list, char[], int, int, int, int);
};


/**
 * typedef struct frmt frmt_t - Struct op
 *
 * @frmt: The format.
 * @fm_t: The function associated.
 */
typedef struct frmt frmt_t;

int _printf(const char *format, ...);
int handle_print(const char *frmt, int *i,
va_list list_of_arg, char buffer[], int flag, int width, int precision, int size);

/****************** FUNCTIONS ******************/

/* Funtions to print chars and strings */
int print_char(va_list arg_types, char buffer[],
	int flag, int width, int precision, int size);
int print_str(va_list arg_types, char buffer[],
	int flag, int width, int precision, int size);
int print_percent(va_list arg_types, char buffer[],
	int flag, int width, int precision, int size);
int pukmat(char c);
/* Functions to print numbers */
int print_int(va_list arg_types, char buffer[],
	int flag, int width, int precision, int size);
int print_bin(va_list arg_types, char buffer[],
	int flag, int width, int precision, int size);
int print_unsigned(va_list arg_types, char buffer[],
	int flag, int width, int precision, int size);
int print_oct(va_list arg_types, char buffer[],
	int flag, int width, int precision, int size);
int print_hexadec(va_list arg_types, char buffer[],
	int flag, int width, int precision, int size);
int print_hex_upper(va_list arg_types, char buffer[],
	int flag, int width, int precision, int size);

int print_hexa(va_list arg_types, char maps[],
char buffer[], int flag, char act_flag, int width, int precision, int size);

/* Function to print non printable characters */
int print_non_printable(va_list arg_types, char buffer[],
	int flag, int width, int precision, int size);

/* Funcion to print memory address */
int print_pointer(va_list arg_types, char buffer[],
	int flag, int width, int precision, int size);

/* Funciotns to handle other specifiers */
int get_flag(const char *format, int *i);
int get_width(const char *format, int *i, va_list list_of_arg);
int get_precision(const char *format, int *i, va_list list_of_arg);
int get_size(const char *format, int *i);

/*Function to print string in reverse*/
int print_reverse(va_list arg_types, char buffer[],
	int flag, int width, int precision, int size);

/*Function to print a string in rot 13*/
int print_rot13_string(va_list arg_types, char buffer[],
	int flag, int width, int precision, int size);

/* width handler */
int write_handler_char(char c, char buffer[],
	int flag, int width, int precision, int size);
int write_numb(int is_positive, int ind, char buffer[],
	int flag, int width, int precision, int size);
int write_num(int ind, char bff[], int flag, int width, int precision,
	int len, char pad, char ext_c);
int write_pointer(char buffer[], int ind, int len,
	int width, int flag, char pad, char ext_c, int pad_start);

int write_unsgnd(int for_negative, int ind,
char buffer[],
	int flag, int width, int precision, int size);

/****************** UTILS ******************/
int for_printable(char);
int append_hex_code(char, char[], int);
int for_digit(char);

long int convert_size_number(long int num, int size);
long int convert_size_unsgnd(unsigned long int num, int size);

#endif
