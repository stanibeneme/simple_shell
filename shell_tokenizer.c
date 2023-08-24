#include "shell.h"

/**
 * tokenize - it tokenizes the buffer with delimiter
 * @buffer: the buffer to tokenize
 * @delimiter: the delimiter to tokenize
 * by Stanley Ibeneme and Philadelphia Olawale-Adedotun
 * Return: this points to an array of pointers to the tokens
 */
char **tokenize(char *buffer, char *delimiter)
{
	char **tokens = NULL;
	size_t s = 0, mcount = 10;

	if (buffer == NULL)
		return (NULL);
	tokens = malloc(sizeof(char *) * mcount);
	if (tokens == NULL)
	{
		perror("Fatal Error");
		return (NULL);
	}
	while ((tokens[s] = new_strtok(buffer, delimiter)) != NULL)
	{
		s++;
		if (s == mcount)
		{
			tokens = _realloc(tokens, &mcount);
			if (tokens == NULL)
			{
				perror("Fatal Error");
				return (NULL);
			}
		}
		buffer = NULL;
	}
	return (tokens);
}
