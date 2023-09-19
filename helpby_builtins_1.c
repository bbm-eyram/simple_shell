#include "shell.h"

void help_env(void);
void help_setenv(void);
void help_unsetenv(void);
void help_history(void);

/**
 * help_env - Provides a concise description and
 * useful information for the 'env' shell built-in command.
 */
void help_env(void)
{
	char *msg = "env: env\n\tPrints the current environment.\n";

	write(STDOUT_FILENO, msg, my_strlen(msg));
}

/**
 * help_setenv - Documentation for the 'setenv' built-in
 * command in the shellby shell.
 */
void help_setenv(void)
{
	char *msg = "setenv: setenv [VARIABLE] [VALUE]\n\tInitializes a new";

	write(STDOUT_FILENO, msg, my_strlen(msg));
	msg = "environment variable, or modifies an existing one.\n\n";
	write(STDOUT_FILENO, msg, my_strlen(msg));
	msg = "\tUpon failure, prints a message to stderr.\n";
	write(STDOUT_FILENO, msg, my_strlen(msg));
}

/**
 * Description: The 'help_unsetenv' function serves as a helpful guide
 * for users of the shellby built-in command 'unsetenv'.
 *
 * It provides essential info on the use of the command:
 * 'unsetenv [VARIABLE]' is the expected syntax, and its job is to
 * remove an environmental variable.
 *
 * Additionally, this function specifies that upon encountering an error,
 * it will prints an error message to the standard error (stderr) stream.
 */
void help_unsetenv(void)
{
	char *msg = "unsetenv: unsetenv [VARIABLE]\n\tRemoves an ";

	write(STDOUT_FILENO, msg, my_strlen(msg));
	msg = "environmental variable.\n\n\tUpon failure, prints a ";
	write(STDOUT_FILENO, msg, my_strlen(msg));
	msg = "message to stderr.\n";
	write(STDOUT_FILENO, msg, my_strlen(msg));
}
