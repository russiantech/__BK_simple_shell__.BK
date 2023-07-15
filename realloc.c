#include "shell.h"

/**
 * _memset - fill memory with constant byte
 * @s: pointer to memory area
 * @b: byte to be filled with *s
 * @n: num of bytes to fill there
 * Return: (s) as pointer to memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * ffree - frees a str of strs
 * @pp: str of strs in question
 */

void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloc - allocate a block of memory again
 * @ptr: pointer to former malloc'ated block
 * @old_size: byte size of former block
 * @new_size: byte size of this new block
 *
 * Return: pointer to da old block name.
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}

