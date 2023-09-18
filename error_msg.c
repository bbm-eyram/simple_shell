/*
 * File: err_msgs1.c
 * Coding Team: 
 *    - Ephraim Eyram (Lead Developer)
 *    - Abigail Nyakoh (Development Team Member)
 */

#include "shell.h"

char *error_env(char **args);
char *error_1(char **args);
char *error_2_exit(char **args);
char *error_2_cd(char **args);
char *error_2_syntax(char **args);
/**
 * error_env – Creates an error message for shellby_env errors.
 * @args: An array of args passed to function.
 *
 * This function makes an error message for handling shellby_env errors,
 * wwith details about the command and the issue faced.
 *
 * Return: A dynamically allocated string containing the error message.
 */
char *error_env(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	args--;
	len = my_strlen(name) + my_strlen(hist_str) + my_strlen(args[0]) + 45;
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
	my_strcat(error, ": Unable to add/remove from environment\n");

	free(hist_str);
	return (error);
}

/**
 * error_1 - Create a custom error message for alias-related errors within the shell.
 * @args: Array of args passed to the command.
 *
 * This function dynamically constructs an error message when a specified shell alias is not found.
 *
 * Return: A dynamically allocated string containing the error message.
 */
char *error_1(char **args)
{
	char *error;
	int len;

	len = my_strlen(name) + my_strlen(args[0]) + 13;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
		return (NULL);

	my_strcpy(error, "alias: ");
	my_strcat(error, args[0]);
	my_strcat(error, " not found\n");

	return (error);
}

/**
 * error_2_exit - Generates an error message for shellby_exit errors.
 *
 * @args: An array of args passed to the command.
 *
 * Return: A dynamically allocated string containing the error message.
 */
char *error_2_exit(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	len = my_strlen(name) + my_strlen(hist_str) + my_strlen(args[0]) + 27;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	my_strcpy(error, name);
	my_strcat(error, ": ");
	my_strcat(error, hist_str);
	my_strcat(error, ": exit: Illegal number: ");
	my_strcat(error, args[0]);
	my_strcat(error, "\n");

	free(hist_str);
	return (error);
}

/**
 * error_2_cd - Makes Error Message for shellby_cd Command
 * @args: An array of args passed to the command.
 *
 * Description:
 * This function is obligated for generating error messages related to the shellby_cd command.
 * It creates informative error messages based on the given args and returns them as
 * dynamically allocated strings.
 *
 * Parameters:
 * @args: An array of args passed to the shellby_cd command.
 *
 * Return:
 * The error message as a dynamically allocated string.
 */
char *error_2_cd(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	if (args[0][0] == '-')
		args[0][2] = '\0';
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
	if (args[0][0] == '-')
		my_strcat(error, ": cd: Illegal option ");
	else
		my_strcat(error, ": cd: can't cd to ");
	my_strcat(error, args[0]);
	my_strcat(error, "\n");

	free(hist_str);
	return (error);
}

/**
 * generate_syntax_error_message - Constructs an error message for handling syntax errors.
 *
 * This function takes an array of command args and makes an informative error
 * message for syntax errors faced during command execution.
 *
 * @args: An array of command args.
 *
 * Return: A dynamically allocated error message string or NULL on memory allocation failure.
 */
char *error_2_syntax(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	len = my_strlen(name) + my_strlen(hist_str) + my_strlen(args[0]) + 33;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	my_strcpy(error, name);
	my_strcat(error, ": ");
	my_strcat(error, hist_str);
	my_strcat(error, ": Syntax error: \"");
	my_strcat(error, args[0]);
	my_strcat(error, "\" unexpected\n");

	free(hist_str);
	return (error);
}
