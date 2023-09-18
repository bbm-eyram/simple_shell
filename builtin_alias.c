/*
 * File: builtin.c
 * Coding Team: 
 *    - Ephraim Eyram (Lead Developer)
 *    - Abigail Nyakoh (Development Team Member)
 */

#include "shell.h"

int shellby_alias(char **args, char __attribute__((__unused__)) **front);
void set_alias(char *var_name, char *value);
void print_alias(alias_t *alias);

/**
 * shellby_alias - A built-in command that manages aliases in the shell.
 *
 * This function can be used to perform various operations related to shell aliases,
 * including printing all aliases, printing a specific alias, or setting a new alias.
 *
 * @args: An array of arguments containing the command and its arguments.
 * @front: A double pointer to the beginning of the args array.
 *
 * Return:
 *   - If an error occurs during execution, it returns -1.
 *   - Otherwise, it returns 0.
 */
int shellby_alias(char **args, char __attribute__((__unused__)) **front)
{
        alias_t *temp = alias_t;
        int i, ret = 0;
        char *value;

        if (!args[0])
        {
                while (temp)
                {
                        print_alias(temp);
                        temp = temp->next;
                }
                return (ret);
        }
        for (i = 0; args[i]; i++)
        {
                temp = alias_t;
                value = my_strchr(args[i], '=');
                if (!value)
                {
                        while (temp)
                        {
                                if (my_strcmp(args[i], temp->name) == 0)
                                {
                                        print_alias(temp);
                                        break;
                                }
                                temp = temp->next;
                        }
                        if (!temp)
                                ret = create_error(args + i, 1);
                }
                else
                        set_alias(args[i], value);
        }
        return (ret);
}
/**
 * set_alias - Manage aliases by either creating a new one or updating an existing one.
 *
 * This function sets an alias with a given name and value. If an alias with the
 * same name already exists, its value is updated; otherwise, a new alias is created.
 *
 * @var_name: The name of the alias.
 * @value: The value of the alias, starting with '='.
 */
void set_alias(char *var_name, char *value)
{
        alias_t *temp = alias_t;
        int len, j, k;
        char *new_value;

        *value = '\0';
        value++;
        len = my_strlen(value) - my_strspn(value, "'\"");
        new_value = malloc(sizeof(char) * (len + 1));
        if (!new_value)
                return;
        for (j = 0, k = 0; value[j]; j++)
        {
                if (value[j] != '\'' && value[j] != '"')
                        new_value[k++] = value[j];
        }
        new_value[k] = '\0';
        while (temp)
        {
                if (my_strcmp(var_name, temp->name) == 0)
                {
                        free(temp->value);
                        temp->value = new_value;
                        break;
                }
                temp = temp->next;
        }
        if (!temp)
                add_alias_to_end(&alias_t, var_name, new_value);
}
/**
 * print_alias - Outputs an alias in the following format: name='value'.
 * @alias: A pointer to an alias structure.
 */
void print_alias(alias_t *alias)
{
        char *alias_string;
        int len = my_strlen(alias->name) + my_strlen(alias->value) + 4;

        alias_string = malloc(sizeof(char) * (len + 1));
        if (!alias_string)
                return;
        my_strcpy(alias_string, alias->name);
        my_strcat(alias_string, "='");
        my_strcat(alias_string, alias->value);
        my_strcat(alias_string, "'\n");

        write(STDOUT_FILENO, alias_string, len);
        free(alias_string);
}
/**
 * replace_aliases - A function that scans through an array of arguments
 *                   and replaces any matching aliases with their corresponding values.
 * @args: A double pointer to the array of arguments.
 *
 * This function iterates through the array of arguments, checks for aliases in a linked list,
 * and if a match is found, replaces the alias with its associated value. It ensures proper memory
 * allocation and management during the replacement process.
 *
 * Return: A double pointer to the modified array of arguments.
 */
char **replace_aliases(char **args)
{
        alias_t *temp;
        int i;
        char *new_value;

        if (my_strcmp(args[0], "alias") == 0)
                return (args);
        for (i = 0; args[i]; i++)
        {
                temp = alias_t;
                while (temp)
                {
                        if (my_strcmp(args[i], temp->name) == 0)
                        {
                                new_value = malloc(sizeof(char) * (my_strlen(temp->value) + 1));
                                if (!new_value)
                                {
                                        free_args(args, args);
                                        return (NULL);
                                }
                                my_strcpy(new_value, temp->value);
                                free(args[i]);
                                args[i] = new_value;
                                i--;
                                break;
                        }
                        temp = temp->next;
                }
        }

        return (args);
}
