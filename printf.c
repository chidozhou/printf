#include "main.h"

/**
 * print_normal - Print normal characters
 * @text: The text to print
 * @count: Pointer to the character count
 * Return: nothing
 */
int print_normal(const char *text, int *count)
{
	write(1, text, 1);
	(*count)++;
	return (0);
}

/**
 * print_string - Print a string
 * @str: The string to print
 * @count: Pointer to the character count
 * Return: nothing
 */
int print_string(const char *str, int *count)
{
	int str_len = 0;

	while (str[str_len] != '\0')
		str_len++;

	write(1, str, str_len);
	(*count) += str_len;
	return (0);
}

/**
 * _printf - Custom printf function
 * @format: The format string
 * Return: Number of characters printed
 */
int _printf(const char *format, ...)
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
				print_normal(format, &print_character);

			else if (*format == 'c')
			{
				char c = va_arg(list_of_args, int);

				write(1, &c, 1);
				print_character++;
			}
			else if (*format == 's')
			{
				char *str = va_arg(list_of_args, char *);

				print_string(str, &print_character);
			}
		}
		format++;
	}
	va_end(list_of_args);
		return (print_character);
}

