/*
 * File: errors.c
 * Coding Team:
 *    - Ephraim Eyram (Lead Developer)
 *    - Abigail Nyakoh (Development Team Member)
 */

#include "shell.h"

int num_len(int num);
char *_itoa(int num);
int create_error(char **args, int err);

/**
 * num_len - Computes the num of digits in an int.
 * @num: The int for which to calculate the digit count.
 *
 * Return: The count of digits in the provided int.
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
 * _itoa - Int to Str Conversion Function
 *
 * This function takes an integer as an input and converts it to a string. It
 * handles both positive and negative integers and dynamically allocates memory
 * for the resulting string. It is the caller's responsibility to free the
 * allocated memory when it's not needed anymore.
 *
 * @num: The int to be converted.
 *
 * Return: A dynamically allocated string representing the integer.
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
 * create_error - Custom error message handler for stderr.
 *
 * @param args: An array of arguments.
 * @param err: The error code.
 *
 * @return: The error code.
 *
 * Description:
 * This function processes error codes and generates
 * corresponding custom error messages,
 * which are then written to the standard error stream (stderr).
 * It takes an array of
 * arguments and an error code as input, and based on the error code,
 * it selects the
 * appropriate error message generation function to call
 * The generated error message
 * is then written to stderr.
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
	write(STDERR_FILENO, error, my_strlen(error));

	if (error)
		free(error);
	return (err);

}
