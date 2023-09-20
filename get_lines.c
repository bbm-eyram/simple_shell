/*
 * File_name: getline.c
 * Auth: Ephraim Eyram and Abigail Nyarkoh
 */

#include "shell.h"

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t b);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);

/**
 * _realloc - Dynamically adjusts the size of a memory block.
 * @ptr: A pointer to the previously allocated memory.
 * @old_size: The original size of the allocated memory block.
 * @new_size: The desired size for the reallocated memory block.
 *
 * This function reallocates a memory block previously
 * allocated with malloc
 * or calloc to a new size specified by new_size.
 * It ensures the data from the
 * original block is preserved to the extent possible.
 *
 * Return: If new_size == old_size - returns ptr (no change).
 *         If new_size == 0 and ptr is not NULL - returns NULL (frees memory).
 *         Otherwise - returns a pointer to the reallocated memory block.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *mem;
	char *ptr_copy, *filler;
	unsigned int index;

	if (new_size == old_size)
		return (ptr);

	if (ptr == NULL)
	{
		mem = malloc(new_size);
		if (mem == NULL)
			return (NULL);

		return (mem);
	}

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	ptr_copy = ptr;
	mem = malloc(sizeof(*ptr_copy) * new_size);
	if (mem == NULL)
	{
		free(ptr);
		return (NULL);
	}

	filler = mem;

	for (index = 0; index < old_size && index < new_size; index++)
		filler[index] = *ptr_copy++;

	free(ptr);
	return (mem);
}

/**
 * assign_lineptr - Refreshes the lineptr buffer for _getline
 * with a new string.
 *
 * This function updates the lineptr and its size (n) with the provided buffer
 * and its size (b).
 *
 * @lineptr: A pointer to the line buffer.
 * @n: The size of lineptr.
 * @buffer: The string to assign to lineptr.
 * @b: The size of buffer.
 */
void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t b)
{
	if (*lineptr == NULL)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*lineptr = buffer;
	}
	else if (*n < b)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
}

/**
 * _getline - Retrieve and store input from a specified stream.
 *
 * This function reads input from a given stream and stores it in a buffer.
 *
 * @lineptr: A buffer to store the input data.
 * @n: The size of the buffer.
 * @stream: The stream to read from.
 *
 * Return: The number of bytes read.
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	static ssize_t input;
	ssize_t ret;
	char c = 'x', *buffer;
	int r;

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * 120);
	if (!buffer)
		return (-1);

	while (c != '\n')
	{
		r = read(STDIN_FILENO, &c, 1);
		if (r == -1 || (r == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (r == 0 && input != 0)
		{
			input++;
			break;
		}

		if (input >= 120)
			buffer = _realloc(buffer, input, input + 1);

		buffer[input] = c;
		input++;
	}
	buffer[input] = '\0';

	assign_lineptr(lineptr, n, buffer, input);

	ret = input;
	if (r != 0)
		input = 0;
	return (ret);
}
