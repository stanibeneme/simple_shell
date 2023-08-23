#include "shell.h"

/**
 * make_env - make shell environment from the one passed to the main
 * @env: the environment passed to the main
 * by Stanley Ibeneme and Philadelphia Olawale-Adedotun
 * Return: point to new environment
 */

char **make_env(char **env)
{
	char **newenv = NULL;
	size_t s;

	for (s = 0; env[s] != NULL; s++)
		;
	newenv = malloc(sizeof(char *) * (s + 1));
	if (newenv == NULL)
	{
		perror("Fatal Error");
		exit(1);
	}
	for (s = 0; env[s] != NULL; s++)
		newenv[s] = _strdup(env[s]);
	newenv[s] = NULL;
	return (newenv);
}

/**
 * free_env - free the shell environment
 * @env: the shell environment
 * by Stanley Ibeneme and Philadelphia Olawale-Adedotun
 * Return: void
 */

void free_env(char **env)
{
	unsigned int s;

	for (s = 0; env[s] != NULL; s++)
		free(env[s]);
	free(env);
}

—--------------------------------------------------------------------------------------------------------------------------
error_handler.c

#include "shell.h"

/**
 * print_error - it prints error message to the standard error
 * @vars: points to variables struct
 * @msg: the message to print out
 * by Stanley Ibeneme and Philadelphia Olawale-Adedotun
 * Return: void
 */
void print_error(vars_t *vars, char *msg)
{
	char *count;

	_puts2(vars->argv[0]);
	_puts2(": ");
	count = _uitoa(vars->count);
	_puts2(count);
	free(count);
	_puts2(": ");
	_puts2(vars->av[0]);
	if (msg)
	{
		_puts2(msg);
	}
	else
		perror("");
}

/**
 * _puts2 - prints string to the standard error
 * @str: string to be printed
 * by Stanley Ibeneme and Philadelphia Olawale-Adedotun
 * Return: void
 */
void _puts2(char *str)
{
	ssize_t num, len;

	num = _strlen(str);
	len = write(STDERR_FILENO, str, num);
	if (len != num)
	{
		perror("Fatal Error");
		exit(1);
	}

}

/**
 * _uitoa - it converts an unsigned integer to string
 * @count: unsigned int to be converted
 * by Stanley Ibeneme and Philadelphia Olawale-Adedotun
 * Return: the pointer to converted string
 */
char *_uitoa(unsigned int count)
{
	char *numstr;
	unsigned int tmp, digits;

	tmp = count;
	for (digits = 0; tmp != 0; digits++)
		tmp /= 10;
	numstr = malloc(sizeof(char) * (digits + 1));
	if (numstr == NULL)
	{
		perror("Fatal Error1");
		exit(127);
	}
	numstr[digits] = '\0';
	for (--digits; count; --digits)
	{
		numstr[digits] = (count % 10) + '0';
		count /= 10;
	}
	return (numstr);
}
