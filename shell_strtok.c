shell_strtok.c

#include "shell.h"

/**
 * check_match - it checks if character matches any in string
 * @c: the character to be checked
 * @str: the string to be checked
 * by Stanley Ibeneme and Philadelphia Olawale-Adedotun
 * Return: 1 if match, 0 if not
 */

unsigned int check_match(char c, const char *str)
{
	unsigned int s;

	for (s = 0; str[s] != '\0'; s++)
	{
		if (c == str[s])
			return (1);
	}
	return (0);
}

/**
 * new_strtok - the custom strtok
 * @str: the string to tokenize
 * @delim: the delimiter to tokenize against
 * by Stanley Ibeneme and Philadelphia Olawale-Adedotun
 * Return: points to NULL or the next token
 */
char *new_strtok(char *str, const char *delim)
{
	static char *token_start;
	static char *next_token;
	unsigned int s;

	if (str != NULL)
		next_token = str;
	token_start = next_token;
	if (token_start == NULL)
		return (NULL);
	for (s = 0; next_token[s] != '\0'; s++)
	{
		if (check_match(next_token[s], delim) == 0)
			break;
	}
	if (next_token[s] == '\0' || next_token[s] == '#')
	{
		next_token = NULL;
		return (NULL);
	}
	token_start = next_token + s;
	next_token = token_start;
	for (s = 0; next_token[s] != '\0'; s++)
	{
		if (check_match(next_token[s], delim) == 1)
			break;
	}
	if (next_token[s] == '\0')
		next_token = NULL;
	else
	{
		next_token[s] = '\0';
		next_token = next_token + s + 1;
		if (*next_token == '\0')
			next_token = NULL;
	}
	return (token_start);
}
