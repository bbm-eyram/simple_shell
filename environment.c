/*
 * File_name: environ.c
 * Auth: Seiyefa Abornyuie and Abigail Nyarkoh
 */

#include "shell.h"

char **_copyenv(void);
void free_env(void);
char **_getenv(const char *var);

/**
 * _copyenv - Duplicate the current environment variables.
 *
 * This function duplicates the current environment variables and
 * returns a double pointer to the new copy.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - A double pointer to the
 *         duplicated environment.
 */
char **_copyenv(void)
{
	char **new_environ;
	size_t size;
	int index;

	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * (size + 1));
	if (!new_environ)
		return (NULL);

	for (index = 0; environ[index]; index++)
	{
		new_environ[index] = malloc(_strlen(environ[index]) + 1);

		if (!new_environ[index])
		{
			for (index--; index >= 0; index--)
				free(new_environ[index]);
			free(new_environ);
			return (NULL);
		}
		_strcpy(new_environ[index], environ[index]);
	}
	new_environ[index] = NULL;

	return (new_environ);
}

/**
 * release_env - Deallocates the memory used by the environment copy.
 *
 * This function is responsible for releasing the memory allocated to
 * hold a copy of the environment variables.
 * It ensures that resources are freed properly to
 * prevent memory leaks.
 */
void free_env(void)
{
	int index;

	for (index = 0; environ[index]; index++)
		free(environ[index]);
	free(environ);
}

/**
 * Function: _getenv
 *
 * Description:
 *   Retrieve the value of an environmental variable from the PATH.
 *
 * Parameters:
 *   @var: The name of the environmental variable to retrieve.
 *
 * Return:
 *   - NULL if the environmental variable does not exist.
 *   - A pointer to the environmental variable's value if it exists.
 */
char **_getenv(const char *var)
{
	int index, len;

	len = _strlen(var);
	for (index = 0; environ[index]; index++)
	{
		if (_strncmp(var, environ[index], len) == 0)
			return (&environ[index]);
	}

	return (NULL);
}
