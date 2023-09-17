/*
 * File: shell-split.c
 * Coding Team: 
 *    - Ephraim Eyram (Lead Developer)
 *    - Abigail Nyakoh (Development Team Member)
 */
#include "shell.h"

int token_len(char *str, char *delim);
int count_tokens(char *str, char *delim);
char **_strtok(char *line, char *delim);

/**
 * token_len - Calculates the length of the first token in a str delimited by a specified char.
 *
 * This function looks for a provided str for the initial token, where tokens are separated by a specified delimiter.
 *
 * @str: The string to search.
 * @delim: The delimiter character.
 *
 * Returns: The length of the initial token within the string.
 */
int token_len(char *str, char *delim)
{
	int index = 0, len = 0;

	while (*(str + index) && *(str + index) != *delim)
	{
		len++;
		index++;
	}

	return (len);
}

/**
 * count_tokens - A function that calculates the num of words delimited
 *                by a specified char within a given str.
 * @str: The str to be examined.
 * @delim: The delimiter char used for spliting the str.
 *
 * Return: The count of delimited words within the input str.
 */
int count_tokens(char *str, char *delim)
{
	int index, tokens = 0, len = 0;

	for (index = 0; *(str + index); index++)
		len++;

	for (index = 0; index < len; index++)
	{
		if (*(str + index) != *delim)
		{
			tokens++;
			index += token_len(str + index, delim);
		}
	}

	return (tokens);
}

/**
 * _strtok - Str Tokenizer Function
 *
 * @line: The input str to be tokenized.
 * @delim: The delimiter char used to split the str to tokens.
 *
 * Description:
 * This function tokenizes a particular input str using the specified delimiter
 * char and returns an array of tokenized substrings.
 *
 * Return:
 * A dynamically allocated array of tokenized substrings or NULL if memory
 * allocation fails or no tokens are found.
 */

char **_strtok(char *line, char *delim)
{
	char **ptr;
	int index = 0, tokens, t, letters, l;

	tokens = count_tokens(line, delim);
	if (tokens == 0)
		return (NULL);

	ptr = malloc(sizeof(char *) * (tokens + 2));
	if (!ptr)
		return (NULL);

	for (t = 0; t < tokens; t++)
	{
		while (line[index] == *delim)
			index++;

		letters = token_len(line + index, delim);

		ptr[t] = malloc(sizeof(char) * (letters + 1));
		if (!ptr[t])
		{
			for (index -= 1; index >= 0; index--)
				free(ptr[index]);
			free(ptr);
			return (NULL);
		}

		for (l = 0; l < letters; l++)
		{
			ptr[t][l] = line[index];
			index++;
		}

		ptr[t][l] = '\0';
	}
	ptr[t] = NULL;
	ptr[t + 1] = NULL;

	return (ptr);
}
