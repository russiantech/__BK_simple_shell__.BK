#include "shell.h"

/**
 * bfree - will free pointer/NULLIFIES the adrs
 * @ptr: adrs of pointer to free
 *
 * Return: 1 if freed, else 0.
 */

int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

