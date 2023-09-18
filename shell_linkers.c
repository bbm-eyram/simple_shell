/*
 * File: shell_linkers.c
 * Coding Team:
 *    - Ephraim Eyram (Lead Developer)
 *    - Abigail Nyakoh (Development Team Member)
 */

#include "shell.h"

alias_t *add_alias_end(alias_t **head, char *name, char *value);
void free_alias_list(alias_t *head);
list_t *add_node_end(list_t **head, char *dir);
void free_list(list_t *head);

/**
 * Function: add_alias_end
 * -----------------------
 * Description: Adds a new alias to the end of an alias_t linked list.
 *
 * @head: A pointer to the head of the alias_t linked list.
 * @name: The name of the new alias to be added.
 * @value: The value of the new alias to be added.
 *
 * Returns: If an error occurs - Null.
 *          Otherwise - a pointer to the newly added node.
 */
alias_t *add_alias_end(alias_t **head, char *name, char *value)
{
	alias_t *new_node = malloc(sizeof(alias_t));
	alias_t *last;

	if (!new_node)
		return (NULL);

	new_node->next = NULL;
	new_node->name = malloc(sizeof(char) * (_strlen(name) + 1));
	if (!new_node->name)
	{
		free(new_node);
		return (NULL);
	}
	new_node->value = value;
	_strcpy(new_node->name, name);

	if (*head)
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new_node;
	}
	else
		*head = new_node;

	return (new_node);
}

/**
 * add_node_end - Append a node to the end of a list_t linked list.
 *
 * This adds a new node to the end of an existing list_t linked
 * list. It makes a new node which contains a directory path
 * and appends it to the
 * end of the list. If the list is initially empty, it initializes a new list
 * with the given directory path as the first node.
 *
 * @head: A pointer to the head of the list_t list.
 * @dir: The directory path for the new node.
 *
 * Return: If memory allocation fails - Null.
 *         Otherwise - a pointer to the node which is newly added.
 */
list_t *add_node_end(list_t **head, char *dir)
{
	list_t *new_node = malloc(sizeof(list_t));
	list_t *last;

	if (!new_node)
		return (NULL);

	new_node->dir = dir;
	new_node->next = NULL;

	if (*head)
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new_node;
	}
	else
		*head = new_node;

	return (new_node);
}

/**
 * free_alias_list - Deallocates memory for an alias_t linked list.
 * @head: Pointer to the head of the alias_t list.
 */
void free_alias_list(alias_t *head)
{
	alias_t *next;

	while (head)
	{
		next = head->next;
		free(head->name);
		free(head->value);
		free(head);
		head = next;
	}
}

/**
 * free_list - frees memory resources associated with a list_t linked list.
 * @head: Pointer to the start of the list_t list.
 */
void free_list(list_t *head)
{
	list_t *next;

	while (head)
	{
		next = head->next;
		free(head->dir);
		free(head);
		head = next;
	}
}
