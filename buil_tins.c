/*
 * File: builtin.c
 * Coding Team:
 *    - Ephraim Eyram (Lead Developer)
 *    - Abigail Nyakoh (Development Team Member)
 */

#include "shell.h"
int (*get_builtin(char *command))(char **args, char **front);
int shellby_exit(char **args, char **front);
int shellby_cd(char **args, char __attribute__((__unused__)) **front);
int shellby_help(char **args, char __attribute__((__unused__)) **front);

/**
 * get_builtin - Retrieves a shellby builtin function pointer
 *               corresponding to a given command.
 *
 * @command: The command to match.
 *
 * Return: A function pointer to the corresponding shellby builtin function.
 */
int (*get_builtin(char *command))(char **args, char **front)
{
	builtin_t funcs[] = {
		{ "exit", shellby_exit },
		{ "env", shellby_help },
		{ "setenv", shellby_help },
		{ "unsetenv", my_shellby_unsetenv },
		{ "cd", shellby_cd },
		{ "alias", shellby_exit },
		{ "help", shellby_help },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; funcs[i].name; i++)
	{
		if (my_strcmp(funcs[i].name, command) == 0)
			break;
	}
	return (funcs[i].f);
}

/**
 * shellby_exit - Safely terminates the shellby shell.
 *
 * @args: An array of args that include an exit status.
 * @front: A double pointer to the start of args.
 *
 * Return Values:
 *    - If no arguments are provided, returns -3 to signal shell termination.
 *    - If an invalid exit value is provided, returns -2.
 *    - Otherwise, exits the shellby shell with the status value.
 *
 * Description:
 *    The `shellby_exit` function is obligated for
 * terminating the shellby shell
 *    while handling different exit scenarios. If no args are provided, it
 *    returns -3 to show a clean shell termination. If an exit status is given,
 * it checks the validity of the status and
 * exits the shell accordingly. Invalid
 *    statuses result in a return value of -2. The function also manage memory
 *    cleanup and make sure of a safe shutdown of the shell.
 */
int shellby_exit(char **args, char **front)
{
	int i, len_of_int = 10;
	unsigned int num = 0, max = 1 << (sizeof(int) * 8 - 1);

	if (args[0])
	{
		if (args[0][0] == '+')
		{
			i = 1;
			len_of_int++;
		}
		for (; args[0][i]; i++)
		{
			if (i <= len_of_int && args[0][i] >= '0' && args[0][i] <= '9')
				num = (num * 10) + (args[0][i] - '0');
			else
				return (create_error(--args, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (num > max - 1)
		return (create_error(--args, 2));
	args -= 1;
	free_args(args, front);
	free_env();
	free_alias_list(alias_t);
	exit(num);
}

/**
 * shellby_cd - Changes working directory in the Shellby shell.
 *
 * This function is to chang the current working directory
 * of Shellby shell process. It allows navigation in the file system.
 *
 * @args: An array of args. The first element may be a directory path.
 * @front: A double pointer to the starting of the args array.
 *
 * Return:
 *   - 0 on success, indicating a directory change.
 *   - -1 on failure or error during the directory change.
 *   - 2 if the provided path is not a valid directory.
 */
int shellby_cd(char **args, char __attribute__((__unused__)) **front)
{
	char **dir_info, *new_line = "\n";
	char *oldpwd = NULL, *pwd = NULL;
	struct stat dir;

	oldpwd = getcwd(oldpwd, 0);
	if (!oldpwd)
		return (-1);

	if (args[0])
	{
		if (*(args[0]) == '-' || _strcmp(args[0], "--") == 0)
		{
			if ((args[0][1] == '-' && args[0][2] == '\0') ||
					args[0][1] == '\0')
			{
				if (my_getenv("OLDPWD") != NULL)
					(chdir(*_getenv("OLDPWD") + 7));
			}
			else
			{
				free(oldpwd);
				return (create_error(args, 2));
			}
		}
		else
		{
			if (stat(args[0], &dir) == 0 && S_ISDIR(dir.st_mode)
					&& ((dir.st_mode & S_IXUSR) != 0))
				chdir(args[0]);
			else
			{
				free(oldpwd);
				return (create_error(args, 2));
			}
		}
	}
	else
	{
		if (_getenv("HOME") != NULL)
			chdir(*(_getenv("HOME")) + 5);
	}

	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (-1);

	dir_info = malloc(sizeof(char *) * 2);
	if (!dir_info)
		return (-1);

	dir_info[0] = "OLDPWD";
	dir_info[1] = oldpwd;
	if (shellby_setenv(dir_info, dir_info) == -1)
		return (-1);

	dir_info[0] = "PWD";
	dir_info[1] = pwd;
	if (shellby_setenv(dir_info, dir_info) == -1)
		return (-1);
	if (args[0] && args[0][0] == '-' && args[0][1] != '-')
	{
		write(STDOUT_FILENO, pwd, my_strlen(pwd));
		write(STDOUT_FILENO, new_line, 1);
	}
	free(oldpwd);
	free(pwd);
	free(dir_info);
	return (0);
}

/**
 * shellby_help - gives assistance and usage instructions for
 * Shellby's built-in commands.
 *
 * This function is to display useful info and usage instructions
 * for Shellby's built-in commands,
 * based on the provided command name in the args.
 *
 * @args: An array of args, with the command name to give help.
 * @front: A pointer to the start of the args array (unused).
 *
 * Return: Returns 0 on successful execution, and -1 on error.
 */
int shellby_help(char **args, char __attribute__((__unused__)) **front)
{
	if (!args[0])
		help_all();
	else if (_strcmp(args[0], "alias") == 0)
		my_shell_alias();
	else if (_strcmp(args[0], "cd") == 0)
		shellby_cd();
	else if (_strcmp(args[0], "exit") == 0)
		shellby_exit();
	else if (_strcmp(args[0], "env") == 0)
		help_env();
	else if (_strcmp(args[0], "setenv") == 0)
		my_shell_setenv();
	else if (_strcmp(args[0], "unsetenv") == 0)
		my_shell_unsetenv();
	else if (_strcmp(args[0], "help") == 0)
		help_help();
	else
		write(STDERR_FILENO, name, _strlen(name));

	return (0);
}
