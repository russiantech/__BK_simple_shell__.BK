#include "shell.h"

/**
 * _strlen - gives length of str
 * @s: str in question
 *
 * Return: length of str as int
 */

int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * _strcmp - compares of 2 strs.
 * @s1: 1st str
 * @s2: 2nd str
 *
 * Return: -(negative)if s1 < s2,positive if s1 > s2,zero(0) if s1 == s2
 */

int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - sees if needle begins with haystack
 * @haystack: str in question
 * @needle: substr to find
 *
 * Return: adrs of next char of haystack else null
 */

char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - adds 2 strs
 * @dest: dest buffer
 * @src: src buffer
 *
 * Return: pointer to @dest
 */

char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
