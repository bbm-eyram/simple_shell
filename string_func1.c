/*
 * File_name: str_funcs2.c
 * Auth: Ephraim Eyram and Abigail Nyarkoh
 */

#include "shell.h"

char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);

/**
 * _strchr - Find character in string.
 *
 * Searches for the first occurrence of the character 'c' in the string 's'.
 *
 * @s: The string to search.
 * @c: The character to find.
 *
 * Return: A pointer to the first occurrence of 'c' in 's', or NULL if 'c'
 *         is not found.
 */
char *_strchr(char *s, char c)
{
	int index;

	for (index = 0; s[index]; index++)
	{
		if (s[index] == c)
			return (s + index);
	}

	return (NULL);
}

/**
 * _strspn - Calculate the length of a prefix substring.
 *
 * @s: The string to be searched.
 * @accept: The prefix to be measured.
 *
 * Return: The number of bytes in s containing only characters from accept.
 */
int _strspn(char *s, char *accept)
{
	int bytes = 0;
	int index;

	while (*s)
	{
		for (index = 0; accept[index]; index++)
		{
			if (*s == accept[index])
			{
				bytes++;
				break;
			}
		}
		s++;
	}
	return (bytes);
}

/**
 * _strcmp - Compare two strings.
 *
 * Compares the two input strings, s1 and s2, character by character,
 * and returns:
 *   - A positive byte difference if s1 > s2.
 *   - 0 if s1 = s2.
 *   - A negative byte difference if s1 < s2.
 *
 * @s1: The first string to be compared.
 * @s2: The second string to be compared.
 *
 * Return: Comparison result as described above.
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	if (*s1 != *s2)
		return (*s1 - *s2);

	return (0);
}

/**
 * _strncmp - Compare two strings up to a specified number of characters.
 *
 * @s1: Pointer to the first string.
 * @s2: Pointer to the second string.
 * @n: Number of characters to compare.
 *
 * Return:
 *   - Less than 0 if the first n bytes of s1 are lexically less than s2.
 *   - 0 if the first n bytes of s1 and s2 match.
 *   - Greater than 0 if the first n bytes of s1 are lexically greater than s2.
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	for (i = 0; s1[i] && s2[i] && i < n; i++)
	{
		if (s1[i] > s2[i])
			return (s1[i] - s2[i]);
		else if (s1[i] < s2[i])
			return (s1[i] - s2[i]);
	}
	if (i == n)
		return (0);
	else
		return (-15);
}
