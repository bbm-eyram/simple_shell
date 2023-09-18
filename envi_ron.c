/*
 * File: environ.c
 * Coding Team: 
 *    - Ephraim Eyram (Lead Developer)
 *    - Abigail Nyakoh (Development Team Member)
 */

#include "shell.h"

char **_copyenv(void);
void free_env(void);
char **_getenv(const char *var);

/**
 * _copyenv - Duplicate the env variables.
 *
 * This function makes a duplicate of the current environ variables.
 *
 * Return:
 *   - If successful, returns a double pointer to the duplicated environment.
 *   - If an error occurs (e.g., memory allocation failure), returns NULL.
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
 * Function: free_env
 * Description: Deallocates memory used for storing environment variables.
 * 
 * This function is responsible for releasing the memory used to store environment
 * variables and the array that holds them. It iterates through the environment
 * variables and deallocates their memory individually before freeing the array itself.
 */
void free_env(void)
{
	int index;

	for (index = 0; environ[index]; index++)
		free(environ[index]);
	free(environ);
}

/**
 * _getenv - Retrieve environmental variable from the system's PATH.
 *
 * This function searches for environmental variable with a specified name
 * within the system's PATH environment. If found, it returns a pointer to the
 * value of the environmental variable.
 *
 * @var: The name of the environmental variable to retrieve.
 *
 * Return: If the environmental variable is found, a pointer to its value is returned.
 *         If the environmental variable does not exist or an error occurs - NULL.
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
