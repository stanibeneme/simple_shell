#include "shell.h"

/**
 * add_key - creates new environment var
 * @vars: points to struct of var
 * by Stanley Ibeneme and Philadelphia Olawale-Adedotun
 * Return: void
 */
void add_key(vars_t *vars)
{
	unsigned int s;
	char **newenv;

	for (s = 0; vars->env[s] != NULL; s++)
		;
	newenv = malloc(sizeof(char *) * (s + 2));
	if (newenv == NULL)
	{
		print_error(vars, NULL);
		vars->status = 127;
		new_exit(vars);
	}
	for (s = 0; vars->env[s] != NULL; s++)
		newenv[s] = vars->env[s];
	newenv[s] = add_value(vars->av[1], vars->av[2]);
	if (newenv[s] == NULL)
	{
		print_error(vars, NULL);
		free(vars->buffer);
		free(vars->commands);
		free(vars->av);
		free_env(vars->env);
		free(newenv);
		exit(127);
	}
	newenv[s + 1] = NULL;
	free(vars->env);
	vars->env = newenv;
}

/**
 * find_key - finds environment variable
 * @env: the array of environment variables
 * @key: the environment variables to find
 * by Stanley Ibeneme and Philadelphia Olawale-Adedotun
 * Return: points to address of the environment var
 */
char **find_key(char **env, char *key)
{
	unsigned int s, t, len;

	len = _strlen(key);
	for (s = 0; env[s] != NULL; s++)
	{
		for (t = 0; t < len; t++)
			if (key[t] != env[s][t])
				break;
		if (t == len && env[s][t] == '=')
			return (&env[s]);
	}
	return (NULL);
}

/**
 * add_value - creates new environment var string
 * @key: the variable name
 * @value: the variable value
 * by Stanley Ibeneme and Philadelphia Olawale-Adedotun
 * Return: points to the new string;
 */
char *add_value(char *key, char *value)
{
	unsigned int len1, len2, s, t;
	char *new;

	len1 = _strlen(key);
	len2 = _strlen(value);
	new = malloc(sizeof(char) * (len1 + len2 + 2));
	if (new == NULL)
		return (NULL);
	for (s = 0; key[s] != '\0'; s++)
		new[s] = key[s];
	new[s] = '=';
	for (t = 0; value[t] != '\0'; t++)
		new[s + 1 + t] = value[t];
	new[s + 1 + t] = '\0';
	return (new);
}

/**
 * _atoi - converts a string to an integer
 * @str: string to be converted
 * by Stanley Ibeneme and Philadelphia Olawale-Adedotun
 * Return: the int value, or -1 if encountered error
 */
int _atoi(char *str)
{
	unsigned int s, digits;
	int num = 0, num_test;

	num_test = INT_MAX;
	for (digits = 0; num_test != 0; digits++)
		num_test /= 10;
	for (s = 0; str[s] != '\0' && s < digits; s++)
	{
		num *= 10;
		if (str[s] < '0' || str[s] > '9')
			return (-1);
		if ((s == digits - 1) && (str[s] - '0' > INT_MAX % 10))
			return (-1);
		num += str[s] - '0';
		if ((s == digits - 2) && (str[s + 1] != '\0') && (num > INT_MAX / 10))
			return (-1);
	}
	if (s > digits)
		return (-1);
	return (num);
}
