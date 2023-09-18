/*
 * File: help.c
 * Coding Team: 
 *    - Ephraim Eyram (Lead Developer)
 *    - Abigail Nyakoh (Development Team Member)
 */

#include "shell.h"

void free_args(char **args, char **front);
char *get_pid(void);
char *get_env_value(char *beginning, int len);
void variable_replacement(char **args, int *exe_ret);

/**
 * free_args - Release memory resource allocated for the array of command args.
 * @args: A null-terminated double pointer which holds command argus.
 * @front: A double pointer pointing to the start of the args array.
 */
void free_args(char **args, char **front)
{
	size_t i;

	for (i = 0; args[i] || args[i + 1]; i++)
		free(args[i]);

	free(front);
}

/**
 * get_pid - Obtain the Process ID (PID) of the current process.
 * Description: This function retrieves the Process ID (PID) of the calling
 *              process by accessing system information from the '/proc/self/stat' file.
 *              It parses the contents of this file to isolate the PID, storing it
 *              as a string in a dynamically allocated buffer.
 *
 * Return: A dynamically allocated string containing the current Process ID,
 *         or NULL if there is an error during the retrieval process.
 */

char *get_pid(void)
{
	size_t i = 0;
	char *buffer;
	ssize_t file;

	file = open("/proc/self/stat", O_RDONLY);
	if (file == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	buffer = malloc(120);
	if (!buffer)
	{
		close(file);
		return (NULL);
	}
	read(file, buffer, 120);
	while (buffer[i] != ' ')
		i++;
	buffer[i] = '\0';

	close(file);
	return (buffer);
}

/**
 * get_env_value - Retrieve the value accompanied with an environmental variable.
 * @beginning: The environmental variable name to search for.
 * @len: The length of the environmental variable name.
 *
 * Returns: If the variable is found – its value.
 * Returns: If not found - an empty string.
 *
 * Description: This function retrieves the value with an environmental
 * variable in the format "VARIABLE=VALUE".
 */
char *get_env_value(char *beginning, int len)
{
	char **var_addr;
	char *replacement = NULL, *temp, *var;

	var = malloc(len + 1);
	if (!var)
		return (NULL);
	var[0] = '\0';
	my_strncat(var, beginning, len);

	var_addr = getenv(var);
	free(var);
	if (var_addr)
	{
		temp = *var_addr;
		while (*temp != '=')
			temp++;
		temp++;
		replacement = malloc(my_strlen(temp) + 1);
		if (replacement)
			my_strcpy(replacement, temp);
	}

	return (replacement);
}

/**
 * variable_replacement - Command Line Variable Substitution
 * @line: Pointer to a command line str with variables to subtitute.
 * @exe_ret: Pointer to the return value of the last executed command.
 *
 * Description:
 * This function performs dynamic variable substitution on a particular command line.
 * It replaces occurrences of $$ with the current Process ID (PID), $? with the
 * return value of the last executed program, and environmental variables
 * prefixed with $ with their corresponding values.
 */
void variable_replacement(char **line, int *exe_ret)
{
	int j, k = 0, len;
	char *replacement = NULL, *old_line = NULL, *new_line;

	old_line = *line;
	for (j = 0; old_line[j]; j++)
	{
		if (old_line[j] == '$' && old_line[j + 1] &&
				old_line[j + 1] != ' ')
		{
			if (old_line[j + 1] == '$')
			{
				replacement = get_pid();
				k = j + 2;
			}
			else if (old_line[j + 1] == '?')
			{
				replacement = _itoa(*exe_ret);
				k = j + 2;
			}
			else if (old_line[j + 1])
			{
				/* extract the variable name to search for */
				for (k = j + 1; old_line[k] &&
						old_line[k] != '$' &&
						old_line[k] != ' '; k++)
					;
				len = k - (j + 1);
				replacement = get_env_value(&old_line[j + 1], len);
			}
			new_line = malloc(j + my_strlen(replacement)
					  + my_strlen(&old_line[k]) + 1);
			if (!line)
				return;
			new_line[0] = '\0';
			my_strncat(new_line, old_line, j);
			if (replacement)
			{
				my_strcat(new_line, replacement);
				free(replacement);
				replacement = NULL;
			}
			my_strcat(new_line, &old_line[k]);
			free(old_line);
			*line = new_line;
			old_line = new_line;
			j = -1;
		}
	}
}
