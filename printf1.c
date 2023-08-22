#include "main.h"

int print_normal(const char *text, int *count);
int print_string(const char *str, int *count);

/**
 * print_number - Print a signed integer
 * @num: The integer to print
 * @count: Pointer to the character count
 */
void print_number(int num, int *count)
{
	char digit;

	if (num < 0)
	{
		write(1, "-", 1);
		(*count)++;
		num = -num;
	}

	if (num / 10)
	{
		print_number(num / 10, count);
	}

	digit = num % 10 + '0';
	write(1, &digit, 1);
	(*count)++;
}

/**
 * handle_conversion - Handle conversion specifiers for _printf function
 * @format: Pointer to the format specifier character
 * @count: Pointer to the character count
 * @args: va_list of arguments
 *
 * This function handles different conversion specifiers for the custom _printf
 * function and performs appropriate actions based on the specifier.
 *
 * Return: Pointer to the next character in the format string
 */
const char *handle_conversion(const char *format, int *count, va_list args)
{
	if (*format == 'c')
	{
		char c = va_arg(args, int);

		write(1, &c, 1);
		(*count)++;
	}
	else if (*format == 's')
	{
		char *str = va_arg(args, char *);

		print_string(str, count);
	}
	else if (*format == 'd' || *format == 'i')
	{
		int num = va_arg(args, int);

		print_number(num, count);
	}

	return (format);
}

/**
 * 
 * _printf1 - our custom printf function
 * @format: The format string
 * Return: Number of the characters printed
 */
int _printf1(const char *format, ...)
{
	int print_character = 0;

	va_list list_of_args;

	if (format == NULL)
		return (-1);

	va_start(list_of_args, format);

	while (*format)
	{
		if (*format != '%')
			print_normal(format, &print_character);
		else
		{
			format++;
			if (*format == '\0')
				break;

			if (*format == '%')
			{
				print_normal(format, &print_character);
			}
			else
			{
				format = handle_conversion(format, &print_character, list_of_args);
			}
		}
		format++;
	}

	va_end(list_of_args);
	return (print_character);
}

