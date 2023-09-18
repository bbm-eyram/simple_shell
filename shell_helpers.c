/*
 * File: shell_helpers.c
 * Coding Team:
 *    - Ephraim Eyram (Lead Developer)
 *    - Abigail Nyakoh (Development Team Member)
 */

char *get_args(char *line, int *exe_ret);
int call_args(char **args, char **front, int *exe_ret);
int run_args(char **args, char **front, int *exe_ret);
int handle_args(int *exe_ret);
int check_args(char **args);

/**
 * get_args - Read and preprocess a command from standard input.
 *
 * This function is responsible for reading a command from the standard input,
 * storing it in the 'line' buffer, and performing preprocessing tasks like
 * variable replacement and line handling. It also handles prompts and command
 * history.
 *
 * @line: A buffer to store the retrieved and processed command.
 * @exe_ret: A pointer to the return value of the last executed command.
 *
 * Return: If an error occurs during reading - NULL.
 *         Otherwise - a pointer to the processed command.
 */
char *get_args(char *line, int *exe_ret)
{
	size_t n = 0;
	ssize_t read;
	char *prompt = "$ ";

	if (line)
		free(line);

	read = _getline(&line, &n, STDIN_FILENO);
	if (read == -1)
		return (NULL);
	if (read == 1)
	{
		hist++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		return (get_args(line, exe_ret));
	}

	line[read - 1] = '\0';
	variable_replacement(&line, exe_ret);
	handle_line(&line, read);

	return (line);
}

/**
 * call_args - Command Execution and Operator Handling
 *
 * This function is responsible for executing commands and handling operators
 * like  "||" and "&&" within a particular array of args. It manages command
 * Executes a command and updates the return value based on the
 * executed command's result.
 *
 * @args: An array of args which contains commands and operators.
 * @front: A double pointer to the starting of args.
 * @exe_ret: A pointer to the return value of the
 * parent process' last executed command.
 *
 * Return: The return value of the last executed command.
 */
int call_args(char **args, char **front, int *exe_ret)
{
	int ret, index;

	if (!args[0])
		return (*exe_ret);
	for (index = 0; args[index]; index++)
	{
		if (_strncmp(args[index], "||", 2) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			args = replace_aliases(args);
			ret = run_args(args, front, exe_ret);
			if (*exe_ret != 0)
			{
				args = &args[++index];
				index = 0;
			}
			else
			{
				for (index++; args[index]; index++)
					free(args[index]);
				return (ret);
			}
		}
		else if (_strncmp(args[index], "&&", 2) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			args = replace_aliases(args);
			ret = run_args(args, front, exe_ret);
			if (*exe_ret == 0)
			{
				args = &args[++index];
				index = 0;
			}
			else
			{
				for (index++; args[index]; index++)
					free(args[index]);
				return (ret);
			}
		}
	}
	args = replace_aliases(args);
	ret = run_args(args, front, exe_ret);
	return (ret);
}

/**
 * run_args - Executes commands and handles their behavior.
 *
 * This function is to execute a command, which can be either
 * a built-in command or an external executable. It orchestrates the execution
 * flow, distinguishing between built-ins and external commands, and maintains
 * the return value of the last executed command.
 *
 * @args: An array of args representing the command and its parameters.
 * @front: A double pointer to the beginning
 * of the args array.
 * @exe_ret: A pointer to the return value of the
 * parent process' last executed command.
 *
 * Return: The return value of the last executed command.
 */
int run_args(char **args, char **front, int *exe_ret)
{
	int ret, i;
	int (*builtin)(char **args, char **front);

	builtin = get_builtin(args[0]);

	if (builtin)
	{
		ret = builtin(args + 1, front);
		if (ret != EXIT)
			*exe_ret = ret;
	}
	else
	{
		*exe_ret = execute(args, front);
		ret = *exe_ret;
	}

	hist++;

	for (i = 0; args[i]; i++)
		free(args[i]);

	return (ret);
}

/**
 * handle_args - Orchestrates command execution and arg handling.
 *
 * This function manages the entire process of reading, parsing, and executing
 * commands. It tokenizes the input, performs error checks, and ensures
 * proper execution of single and multiple commands, and handling
 * command chaining with semicolons.
 *
 * @exe_ret: A pointer to the return value of the
 * parent process' last executed command.
 *
 * Return:
 *   - If an end-of-file is read: END_OF_FILE (-2).
 *   - If the input cannot be tokenized: -1.
 *   - Otherwise: The exit value of the last executed command.
 */
int handle_args(int *exe_ret)
{
	int ret = 0, index;
	char **args, *line = NULL, **front;

	line = get_args(line, exe_ret);
	if (!line)
		return (END_OF_FILE);

	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (ret);
	if (check_args(args) != 0)
	{
		*exe_ret = 2;
		free_args(args, args);
		return (*exe_ret);
	}
	front = args;

	for (index = 0; args[index]; index++)
	{
		if (_strncmp(args[index], ";", 1) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			ret = call_args(args, front, exe_ret);
			args = &args[++index];
			index = 0;
		}
	}
	if (args)
		ret = call_args(args, front, exe_ret);

	free(front);
	return (ret);
}

/**
 * check_args - A function that validates the
 * correct placement of special command tokens.
 * @args: A 2D array of tokenized commands and arguments.
 *
 * This function checks if tokens like ';', '&&', and '||'
 * are correctly positioned
 * within the given command args.
 *
 * Return:
 *   - 0 if the special tokens are correctly placed.
 *   - 2 if any of these tokens are in an invalid position.
 */

int check_args(char **args)
{
	size_t i;
	char *cur, *nex;

	for (i = 0; args[i]; i++)
	{
		cur = args[i];
		if (cur[0] == ';' || cur[0] == '&' || cur[0] == '|')
		{
			if (i == 0 || cur[1] == ';')
				return (create_error(&args[i], 2));
			nex = args[i + 1];
			if (nex && (nex[0] == ';' || nex[0] == '&' || nex[0] == '|'))
				return (create_error(&args[i + 1], 2));
		}
	}
	return (0);
}
