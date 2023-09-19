/*
 * File: builtin.c
 * Coding Team:
 *    - Ephraim Eyram (Lead Developer)
 *    - Abigail Nyakoh (Development Team Member)
 */

#include "shell.h"

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t b);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);

/**
 * _realloc - Flexible memory reallocation function.
 *
 * This function reallocates memory, allowing for dynamic structuring of the
 * size of the previously allocated block.
 *
 * @ptr: A pointer to the previously allocated memory block.
 * @old_size: The actual size in bytes of the memory block.
 * @new_size: The preferred size in bytes for the new memory block.
 *
 * Return:
 *   - If new_size equals old_size, then it returns ptr.
 *   - If new_size is 0 and ptr is not NULL,
 * then it frees ptr and returns NULL.
 *   - Otherwise, it returns a pointer to the reallocated memory block.
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
 * Description: This function is for managing the task of the 'lineptr'
 * variable used in the_getline function. It handles resizing the buffer and
 * reassigning it as needed to accommodate input data.
 *
 * @lineptr: A buffer to store an input string.
 * @n: The current size of 'lineptr'.
 * @buffer: The string to assign to 'lineptr'.
 * @b: The size of 'buffer'.
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
		my_strcpy(*lineptr, buffer);
		free(buffer);
	}
}

/**
 * _getline - Read and store input from a stream in a dynamic buffer.
 * @lineptr: A pointer to a buffer to store the input.
 * @n: A pointer to the size of the buffer.
 * @stream: The stream to read input from.
 *
 * This function reads input chars from the specified stream and
 * dynamically allocates memory to save the input in the buffer pointed to
 * by lineptr. It resize the buffer size as needed using the size pointed
 * to by n. When a newline character ('\n') is encountered or the end of
 * the input is reached, then the function returns the number of bytes read. If
 * an error occurs, it returns -1.
 *
 * Return: The number of bytes read, or -1 on failure.
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
