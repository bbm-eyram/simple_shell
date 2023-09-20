/*
 * File_name: errors.c
 * Auth: Ephraim Eyram and Abigail Nyarkoh
 */

#include "shell.h"

int num_len(int num);
char *_itoa(int num);
int create_error(char **args, int err);

/**
 * num_len - Calculates the number of digits in an integer.
 * @num: The integer to analyze.
 *
 * This function determines the number of digits in the given integer.
 *
 * Return: The count of digits in the integer.
 */
int num_len(int num)
{
	unsigned int num1;
	int len = 1;

	if (num < 0)
	{
		len++;
		num1 = num * -1;
	}
	else
	{
		num1 = num;
	}
	while (num1 > 9)
	{
		len++;
		num1 /= 10;
	}

	return (len);
}

/**
 * _itoa - Transforms a numeric value into its string representation.
 * @num: The integer to be converted.
 *
 * Description:
 * This function takes an integer 'num' and converts it into a string
 * representation. The resulting string can be used for various purposes,
 * such as printing or manipulating the numeric value as text.
 *
 * Return: A pointer to the newly created string representation of 'num'.
 */
char *_itoa(int num)
{
	char *buffer;
	int len = num_len(num);
	unsigned int num1;

	buffer = malloc(sizeof(char) * (len + 1));
	if (!buffer)
		return (NULL);

	buffer[len] = '\0';

	if (num < 0)
	{
		num1 = num * -1;
		buffer[0] = '-';
	}
	else
	{
		num1 = num;
	}

	len--;
	do {
		buffer[len] = (num1 % 10) + '0';
		num1 /= 10;
		len--;
	} while (num1 > 0);

	return (buffer);
}

/**
 * create_error - Generates a custom error message and outputs it to stderr.
 *
 * This function takes an array of arguments and an error value as input.
 * It constructs a custom error message and writes it
 * to the standard error stream.
 *
 * @args: An array of arguments related to the error.
 * @err: The error value to be returned.
 *
 * Return: The error value passed as an argument.
 */

int create_error(char **args, int err)
{
	char *error;

	switch (err)
	{
	case -1:
		error = error_env(args);
		break;
	case 1:
		error = error_1(args);
		break;
	case 2:
		if (*(args[0]) == 'e')
			error = error_2_exit(++args);
		else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
			error = error_2_syntax(args);
		else
			error = error_2_cd(args);
		break;
	case 126:
		error = error_126(args);
		break;
	case 127:
		error = error_127(args);
		break;
	}
	write(STDERR_FILENO, error, _strlen(error));

	if (error)
		free(error);
	return (err);

}
