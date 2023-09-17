/*
 * File: str_func2.c
 * Coding Team: 
 *    - Ephraim Eyram (Lead Developer)
 *    - Abigail Nyakoh (Development Team Member)
 */

#include "shell.h"

char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);

/**
 * _strchr - Find the first occurrence of a char in a str.
 *
 * This function looks for the first occurrence of the specified char 'c' 
 * within the given string 's'.
 *
 * @s: The str to be searched.
 * @c: The char to be located.
 *
 * Return: If 'c' is found - a pointer to the first occurrence.
 *         If 'c' is not found - NULL.
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
 * _strspn - Calculate the length of a prefix substring in a str
 *            made solely of chars from another str.
 *
 * @s: The str to be analyzed.
 * @accept: The set of chars to compare against.
 *
 * Return: The num of consecutive chars at the start of 's'
 *         that are found in 'accept'.
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
 * _strcmp - Custom str comparison function.
 * @s1: The first str to be compared.
 * @s2: The second str to be compared.
 *
 * This function compares two strs and returns a positive byte difference
 * if s1 is lexicographically greater than s2, 0 if they are the same, and a
 * negative byte difference if s1 is lexicographically smaller than s2.
 *
 * Return: Positive byte difference if s1 > s2
 *         0 if s1 = s2
 *         Negative byte difference if s1 < s2
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
 * _strncmp - Compare segments of two strs.
 *
 * This function compares the first 'n' chars of two strings, 's1' and 's2',
 * in a lexicographical manner. It returns:
 *   - A negative value if 's1' is lexicographically less than 's2'.
 *   - 0 if the first 'n' characters of 's1' and 's2' match.
 *   - A positive value if 's1' is lexicographically greater than 's2'.
 *
 * @s1: Pointer to the first str.
 * @s2: Pointer to the second str.
 * @n: The number of characters to compare.
 *
 * Return: An integer representing the lexicographical comparison result.
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
