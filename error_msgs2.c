/*
 * File_name: err_msgs2.c
 * Auth: Ephraim Eyram  and Abigail Nyarkoh
 */

#include "shell.h"

char *error_126(char **args);
char *error_127(char **args);

/**
 * generate_permission_error - Constructs a custom error message for
 * permission denied errors.
 * @args: An array containing the command arguments.
 *
 * Description:
 * This function takes an array of command arguments and
 * generates a user-friendly error message
 * specifically designed for permission denied errors that may
 * occur during command execution.
 * The error message provides information about the
 * failed command and its associated error.
 *
 * Parameters:
 * @args: An array of strings representing command and its arguments.
 *
 * Return:
 * A dynamically allocated string containing constructed error message.
 */
char *error_126(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	len = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 24;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": Permission denied\n");

	free(hist_str);
	return (error);
}

/**
 * generate_command_not_found_error - Constructs an error message for command
 * not found failures.
 * @args: An array of arguments provided to the command.
 *
 * Description:
 * This function creates a custom error message for situations
 * where a specified command is not found.
 *
 * Return: A string containing the error message.
 */
char *error_127(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	len = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 16;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": not found\n");

	free(hist_str);
	return (error);
}
