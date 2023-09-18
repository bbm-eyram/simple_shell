#include "shell.h"

void help_all(void);
void help_alias(void);
void help_cd(void);
void help_exit(void);
void help_help(void);

/**
 * help_all - Display a comprehensive list of built-in commands for Shellby shell.
 *
 * This function is to educate users about the built-in commands available in the
 * Shellby shell. It prints out a list of these commands and offers guidance on how
 * to access more information about each command when using  'help' command.
 *
 * Overview:
 *   - alias    : Display aliases for commands.
 *   - cd       : Change the current working directory.
 *   - exit     : Terminate the Shellby shell with an optional status code.
 *   - env      : Show the current environ variables.
 *   - setenv   : Set or modify the value of an environ variable.
 *   - unsetenv : Remove an environ variable.
 *
 * Usage:
 *   - Type 'help' to view this list of built-in commands.
 *   - For detailed info on a particular command, use 'help <command>'.
 */    
void help_all(void)
{
	char *msg = "Shellby\nThese shell commands are defined internally.\n";

	write(STDOUT_FILENO, msg, my_strlen(msg));
	msg = "Type 'help' to see this list.\nType 'help name' to find ";
	write(STDOUT_FILENO, msg, my_strlen(msg));
	msg = "out more about the function 'name'.\n\n  alias   \t";
	write(STDOUT_FILENO, msg, my_strlen(msg));
	msg = "alias [NAME[='VALUE'] ...]\n  cd    \tcd   ";
	write(STDOUT_FILENO, msg, my_strlen(msg));
	msg = "[DIRECTORY]\n  exit    \texit [STATUS]\n  env     \tenv";
	write(STDOUT_FILENO, msg, my_strlen(msg));
	msg = "\n  setenv  \tsetenv [VARIABLE] [VALUE]\n  unsetenv\t";
	write(STDOUT_FILENO, msg, my_strlen(msg));
	msg = "unsetenv [VARIABLE]\n";
	write(STDOUT_FILENO, msg, my_strlen(msg));
}

/**
 * help_alias - Shows usage info for the 'alias' built-in command.
 */
void help_alias(void)
{
	char *msg = "alias: alias [NAME[='VALUE'] ...]\n\tHandles aliases.\n";

	write(STDOUT_FILENO, msg, my_strlen(msg));
	msg = "\n\talias: Prints a list of all aliases, one per line, in ";
	write(STDOUT_FILENO, msg, my_strlen(msg));
	msg = "the format NAME='VALUE'.\n\talias name [name2 ...]:prints";
	write(STDOUT_FILENO, msg, my_strlen(msg));
	msg = " the aliases name, name2, etc. one per line, in the ";
	write(STDOUT_FILENO, msg, my_strlen(msg));
	msg = "form NAME='VALUE'.\n\talias NAME='VALUE' [...]: Defines";
	write(STDOUT_FILENO, msg, my_strlen(msg));
	msg = " an alias for each NAME whose VALUE is given. If NAME ";
	write(STDOUT_FILENO, msg, my_strlen(msg));
	msg = "is already an alias, replace its value with VALUE.\n";
	write(STDOUT_FILENO, msg, my_strlen(msg));
}

/**
 * help_cd - Display info about the 'cd' built-in command in Shellby.
 */
void help_cd(void)
{
	char *msg = "cd: cd [DIRECTORY]\n\tChanges the current directory of the";

	write(STDOUT_FILENO, msg, my_strlen(msg));
	msg = " process to DIRECTORY.\n\n\tIf no argument is given, the ";
	write(STDOUT_FILENO, msg, my_strlen(msg));
	msg = "command is interpreted as cd $HOME. If the argument '-' is";
	write(STDOUT_FILENO, msg, my_strlen(msg));
	msg = " given, the command is interpreted as cd $OLDPWD.\n\n";
	write(STDOUT_FILENO, msg, my_strlen(msg));
	msg = "\tThe environment variables PWD and OLDPWD are updated ";
	write(STDOUT_FILENO, msg, my_strlen(msg));
	msg = "after a change of directory.\n";
	write(STDOUT_FILENO, msg, my_strlen(msg));
}

/**
 * help_exit - gives info about the 'exit' built-in command in the shell.
 *
 * This function shows usage details and info about the behavior of the 'exit' command.
 * It explains how the 'STATUS' arg can be used to exit the shell and what happens when
 * no argument is given, which defaults to 'exit 0'.
 */
void help_exit(void)
{
	char *msg = "exit: exit [STATUS]\n\tExits the shell.\n\n\tThe ";

	write(STDOUT_FILENO, msg, my_strlen(msg));
	msg = "STATUS argument is the integer used to exit the shell.";
	write(STDOUT_FILENO, msg, my_strlen(msg));
	msg = " If no argument is given, the command is interpreted as";
	write(STDOUT_FILENO, msg, my_strlen(msg));
	msg = " exit 0.\n";
	write(STDOUT_FILENO, msg, my_strlen(msg));
}

/**
 * Shellby Builtin Help
 *
 * Description:
 * This function, help_help(), gives information about the Shellby shell's built-in command 'help'.
 * It gives an overview of available Shellby built-in commands and allows users to retrieve particular 
 * info on each built-in command by providing its name as an arg.
 *
 * Usage:
 * - `help`: provides a list of all availables Shellby built-in commands.
 * - `help [BUILTIN NAME]`: displays detailed information on a built-in command.
 */
void help_help(void)
{
	char *msg = "help: help\n\tSee all possible Shellby builtin commands.\n";

	write(STDOUT_FILENO, msg, my_strlen(msg));
	msg = "\n      help [BUILTIN NAME]\n\tSee specific information on each ";
	write(STDOUT_FILENO, msg, my_strlen(msg));
	msg = "builtin command.\n";
	write(STDOUT_FILENO, msg, my_strlen(msg));
}
