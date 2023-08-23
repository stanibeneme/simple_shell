#include "shell.h"

/**
 * _realloc - this reallocates pointer to double iis space
 * @ptr: it points to the old array
 * @size: it points to number of elements in the old array
 * by Stanley Ibeneme and Philadelphia Olawale-Adedotun
 * Return: points to the new array
 */

char **_realloc(char **ptr, size_t *size)
{
	char **new;
	size_t s;

	new = malloc(sizeof(char *) * ((*size) + 10));
	if (new == NULL)
	{
		free(ptr);
		return (NULL);
	}
	for (s = 0; s < (*size); s++)
	{
		new[s] = ptr[s];
	}
	*size += 10;
	free(ptr);
	return (new);
}
