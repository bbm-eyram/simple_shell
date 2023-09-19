/*
 * File: err_msgs2.c
 * Coding Team:
 *    - Ephraim Eyram (Lead Developer)
 *    - Abigail Nyakoh (Development Team Member)
 */
#include "shell.h"

char *error_126(char **args);
char *error_127(char **args);

/**
 * error_126 - Constructs a descriptive error message for
 * permission denied errors.
 * @args: An array of args passed to the command.
 *
 * Return: A dynamically allocated error message string.
 */
char *error_126(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	len = my_strlen(name) + my_strlen(hist_str) + my_strlen(args[0]) + 24;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	my_strcpy(error, name);
	my_strcat(error, ": ");
	my_strcat(error, hist_str);
	my_strcat(error, ": ");
	my_strcat(error, args[0]);
	my_strcat(error, ": Permission denied\n");

	free(hist_str);
	return (error);
}

/**
 * error_127 - Generates an error message for command not found scenarios.
 * @args: An array of arguments passed to the command.
 *
 * This function creates an informative error message when
 * a command is not found
 * in the system. It includes details such as the command name,
 * its history index,
 * and the reason for the failure.
 *
 * Return: A dynamically allocated string containing the error message.
 */
char *error_127(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	len = my_strlen(name) + my_strlen(hist_str) + my_strlen(args[0]) + 16;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	my_strcpy(error, name);
	my_strcat(error, ": ");
	my_strcat(error, hist_str);
	my_strcat(error, ": ");
	my_strcat(error, args[0]);
	my_strcat(error, ": not found\n");

	free(hist_str);
	return (error);
}
