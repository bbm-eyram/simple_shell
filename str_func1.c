/*
 * File: str_func1.c
 * Coding Team:
 *    - Ephraim Eyram (Lead Developer)
 *    - Abigail Nyakoh (Development Team Member)
 */

#include "shell.h"

int _strlen(const char *s);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);

/**
 * _strlen - Compute the length of a char str.
 * @s: A pointer to the input str.
 *
 * This function calculates and returns the length of the char str
 * pointed to by 's'. If 's' is NULL, it returns 0.
 *
 * Return: The length of the char str, or 0 if 's' is Null.
 */
int _strlen(const char *s)
{
	int length = 0;

	if (!s)
		return (length);
	for (length = 0; s[length]; length++)
		;
	return (length);
}

/**
 * _strcpy - Custom str copying function that duplicates the source str
 * including the null terminator and stores it in the
 * destination buffer.
 *
 * @dest: Pointer to the destination buffer where the string should be copied.
 * @src: Pointer to the source str to be duplicated.
 *
 * Return: Pointer to the destination buffer (i.e., 'dest').
 */
char *_strcpy(char *dest, const char *src)
{
	size_t i;

	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

/**
 * _strcat - Concatenates two strs efficiently.
 * @dest: A pointer to the destination str.
 * @src: A pointer to the source str.
 *
 * This function appends the chars of the source str to the end of the
 * destination str. It does so efficiently by iterating through both strs
 * and making sure that the resulting destination str is Null-terminated.
 *
 * Returns: A pointer to the specified destination string.
 */
char *_strcat(char *dest, const char *src)
{
	char *destTemp;
	const char *srcTemp;

	destTemp = dest;
	srcTemp =  src;

	while (*destTemp != '\0')
		destTemp++;

	while (*srcTemp != '\0')
		*destTemp++ = *srcTemp++;
	*destTemp = '\0';
	return (dest);
}

/**
 * _strncat - Concatenate 'n' bytes from the source to destination str.
 *
 * @dest: A pointer to the destination str.
 * @src: A pointer to the source str.
 * @n: The num of bytes to append from source.
 *
 * Description:
 * This function appends up to 'n' bytes from the 'src' str to the end of
 * the 'dest' str, ensuring proper null-termination. It modifies the
 * 'dest' string in place and returns a pointer to the modified destination.
 *
 * Return: A pointer to the modified destination string.
 */
char *_strncat(char *dest, const char *src, size_t n)
{
	size_t dest_len = _strlen(dest);
	size_t i;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[dest_len + i] = src[i];
	dest[dest_len + i] = '\0';

	return (dest);
}
