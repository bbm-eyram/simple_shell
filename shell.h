#ifndef _MY_UNIQUE_SHELL_H_
#define _MY_UNIQUE_SHELL_H_

/*
 * File: builtin.c
 * Coding Team:
 *    - Ephraim Eyram (Lead Developer)
 *    - Abigail Nyakoh (Development Team Member)
 */


/*
 * File: my_unique_shell.h
 * Authors: Alex Yu
 *          Brennan D Baraban
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>

#define END_OF_FILE -2
#define EXIT -3



/**
 * struct list_node - Defines a linked list node for directory paths.
 * @dir: A directory path.
 * @next: A pointer to the next struct list_node.
 */
typedef struct list_node
{
	char *dir;
	struct list_node *next;
} list_node_t;

/**
 * struct builtin_command - Defines a structure for builtin commands.
 * @name: The name of the builtin command.
 * @function: A function pointer to the builtin command's function.
 */
typedef struct builtin_command
{
	char *name;
	int (*function)(char **args, char **front);
} builtin_command_t;

/**
 * struct alias - Defines a structure for aliases.
 * @name: The name of the alias.
 * @value: The value of the alias.
 * @next: A pointer to the next struct alias.
 */
typedef struct alias
{
	char *name;
	char *value;
	struct alias *next;
} alias_t;

/* Global linked list of aliases */
alias_t *alias_list;

/* Main Helpers */
ssize_t my_getline(char **lineptr, size_t *n, FILE *stream);
void *my_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **my_strtok(char *line, char *delim);
char *get_command_location(char *command);
list_node_t *get_path_directories(char *path);
int execute_command(char **args, char **front);
void free_directory_list(list_node_t *head);
char *int_to_string(int num);

/* Shell Helpers */
void handle_input_line(char **line, ssize_t read);
void replace_variables(char **args, int *exit_code);
char *parse_arguments(char *line, int *exit_code);
int call_builtin_commands(char **args, char **front, int *exit_code);
int run_command(char **args, char **front, int *exit_code);
int handle_input_arguments(int *exit_code);
int validate_arguments(char **args);
void free_input_arguments(char **args, char **front);
char **replace_aliases_with_values(char **args);

/* String functions */
int my_strlen(const char *s);
char *my_strcat(char *dest, const char *src);
char *my_strncat(char *dest, const char *src, size_t n);
char *my_strcpy(char *dest, const char *src);
char *my_strchr(char *s, char c);
int my_strspn(char *s, char *accept);
int my_strcmp(char *s1, char *s2);
int my_strncmp(const char *s1, const char *s2, size_t n);

/* Builtins */
int (*get_builtin_command(char *command))(char **args, char **front);
int my_shell_exit(char **args, char **front);
int my_shell_env(char **args, char __attribute__((__unused__)) **front);
int my_shell_setenv(char **args, char __attribute__((__unused__)) **front);
int my_shell_unsetenv(char **args, char __attribute__((__unused__)) **front);
int my_shell_cd(char **args, char **front);
int my_shell_alias(char **args, char **front);
int my_shell_help(char **args, char **front);

/* Builtin Helpers */
char **copy_environment(void);
void free_environment(void);
char **get_environment_variable(const char *var);

/* Error Handling */
int create_error_message(char **args, int err);
char *get_error_message_environment(char **args);
char *get_error_message_1(char **args);
char *get_error_message_2_exit(char **args);
char *get_error_message_2_cd(char **args);
char *get_error_message_2_syntax(char **args);
char *get_error_message_126(char **args);
char *get_error_message_127(char **args);

/* Linked List Helpers */
alias_t *add_alias_to_end(alias_t **head, char *name, char *value);
void free_alias_list(alias_t *head);
list_node_t *add_node_to_end(list_node_t **head, char *dir);
void free_directory_list(list_node_t *head);

void print_all_help_messages(void);
void print_alias_help(void);
void print_cd_help(void);
void print_exit_help(void);
void print_help_help(void);
void print_env_help(void);
void print_setenv_help(void);
void print_unsetenv_help(void);
void print_history_help(void);

int process_file_commands(char *file_path, int *exit_code);
#endif /* _MY_UNIQUE_SHELL_H_ */
