/*
 * File_name: str_funcs1.c
 * Auth: Epharim Eyram and Abigail Nyarkoh
 */

#include "shell.h"

int _strlen(const char *s);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);

/**
 * _strlen - Calculate the length of a given string.
 *
 * This function computes and returns the length of a null-terminated string.
 *
 * @s: A pointer to the null-terminated string.
 *
 * Return: The length of the string.
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
 * _strcpy - Copy a string from src to dest.
 *
 * This function copies the null-terminated string pointed to by 'src'
 * (including the null terminator) to the buffer pointed to by 'dest'.
 *
 * @dest: Pointer to the destination buffer.
 * @src: Pointer to the source string.
 *
 * Return: Pointer to the destination buffer 'dest'.
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
 * _strcat - Concatenates two strings.
 *
 * This function concatenates the string pointed to by 'src' to the end of the
 * string pointed to by 'dest'.
 *
 * @dest: The destination string.
 * @src: The source string.
 *
 * Return: A pointer to the destination string.
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
 * _strncat - Concatenates two strings with a limit on the number of bytes
 *            copied from the source string.
 *
 * @dest: Pointer to the destination string.
 * @src: Pointer to the source string.
 * @n: Number of bytes to copy from the source.
 *
 * Return: A pointer to the destination string.
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
