/*
 * File: env_builtin.c
 * Coding Team:
 *    - Ephraim Eyram (Lead Developer)
 *    - Abigail Nyakoh (Development Team Member)
 */

#include "shell.h"

int shellby_env(char **args, char __attribute__((__unused__)) **front);
int shellby_setenv(char **args, char __attribute__((__unused__)) **front);
int shellby_unsetenv(char **args, char __attribute__((__unused__)) **front);

/**
 * shellby_env - Displays the current environ variables.
 * @args: An array of args passed to the shell.
 * @front: A double pointer to the starting of args (not used here).
 *
 * Return: If an error occurs, returns -1. Otherwise, returns 0.
 *
 * Description: This function prints the current env variables,
 *              with each variable and its corresponding value displayed
 *              on separate lines in the format 'variable'='value'.
 */
int shellby_env(char **args, char __attribute__((__unused__)) **front)
{
	int index;
	char nc = '\n';

	if (!environ)
		return (-1);

	for (index = 0; environ[index]; index++)
	{
		write(STDOUT_FILENO, environ[index], my_strlen(environ[index]));
		write(STDOUT_FILENO, &nc, 1);
	}

	(void)args;
	return (0);
}

/**
 * shellby_setenv - Modify or add an environment variable to the shell's PATH.
 *
 * @args: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of args.
 *
 * Description:
 *   The shellby_setenv function is responsible for modifying or adding an
 *   environment variable to the shell's PATH. It takes two arguments:
 *   - args[1]: The name of the environment variable to be modified or added.
 *   - args[2]: The value to set for the specified environment variable.
 *
 * Return:
 *   - If an error occurs during the process, the function returns -1.
 *   - Otherwise, it returns 0 to indicate successful completion.
 */
int shellby_setenv(char **args, char __attribute__((__unused__)) **front)
{
	char **env_var = NULL, **new_environ, *new_value;
	size_t size;
	int index;

	if (!args[0] || !args[1])
		return (create_error(args, -1));

	new_value = malloc(my_strlen(args[0]) + 1 + my_strlen(args[1]) + 1);
	if (!new_value)
		return (create_error(args, -1));
	my_strcpy(new_value, args[0]);
	my_strcat(new_value, "=");
	my_strcat(new_value, args[1]);

	env_var = my_getline(args[0]);
	if (env_var)
	{
		free(*env_var);
		*env_var = new_value;
		return (0);
	}
	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * (size + 2));
	if (!new_environ)
	{
		free(new_value);
		return (create_error(args, -1));
	}

	for (index = 0; environ[index]; index++)
		new_environ[index] = environ[index];

	free(environ);
	environ = new_environ;
	environ[index] = new_value;
	environ[index + 1] = NULL;

	return (0);
}

/**
 * Function: shellby_unsetenv
 *
 * Description:
 *   This function removes an environmental variable from the PATH.
 *
 * Parameters:
 *   @args: An array of args passed to the shell.
 *   @front: A double pointer to the beginning of args (not used).
 *
 * Return Value:
 *   On error, it returns -1.
 *   On success, it returns 0.
 */
int shellby_unsetenv(char **args, char __attribute__((__unused__)) **front)
{
	char **env_var, **new_environ;
	size_t size;
	int index, index2;

	if (!args[0])
		return (create_error(args, -1));
	env_var = getenv(args[0]);
	if (!env_var)
		return (0);

	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * size);
	if (!new_environ)
		return (create_error(args, -1));

	for (index = 0, index2 = 0; environ[index]; index++)
	{
		if (*env_var == environ[index])
		{
			free(*env_var);
			continue;
		}
		new_environ[index2] = environ[index];
		index2++;
	}
	free(environ);
	environ = new_environ;
	environ[size - 1] = NULL;

	return (0);
}
