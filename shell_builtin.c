#include "shell.h"

/**
 * check_for_builtins - it checks if the command is a builtin
 * @vars: variable
 * by Stanley Ibeneme and Philadelphia Olawale-Adedotun
 * Return: the pointer to NULL or the particular function
 */
void (*check_for_builtins(vars_t *vars))(vars_t *vars)
{
	unsigned int s;
	builtins_t check[] = {
		{"exit", new_exit},
		{"env", _env},
		{"setenv", new_setenv},
		{"unsetenv", new_unsetenv},
		{NULL, NULL}
	};

	for (s = 0; check[s].f != NULL; s++)
	{
		if (_strcmpr(vars->av[0], check[s].name) == 0)
			break;
	}
	if (check[s].f != NULL)
		check[s].f(vars);
	return (check[s].f);
}

/**
 * new_exit - to exit program
 * @vars: variables
 * by Stanley Ibeneme and Philadelphia Olawale-Adedotun
 * Return: void.
 */
void new_exit(vars_t *vars)
{
	int status;

	if (_strcmpr(vars->av[0], "exit") == 0 && vars->av[1] != NULL)
	{
		status = _atoi(vars->av[1]);
		if (status == -1)
		{
			vars->status = 2;
			print_error(vars, ": illegal numbers: ");
			_puts2(vars->av[1]);
			_puts2("\n");
			free(vars->commands);
			vars->commands = NULL;
			return;
		}
		vars->status = status;
	}
	free(vars->buffer);
	free(vars->av);
	free(vars->commands);
	free_env(vars->env);
	exit(vars->status);
}

/**
 * _env - it prints the current environment
 * @vars: the structure of variables
 * by Stanley Ibeneme and Philadelphia Olawale-Adedotun
 * Return: void
 */
void _env(vars_t *vars)
{
	unsigned int s;

	for (s = 0; vars->env[s]; s++)
	{
		_puts(vars->env[s]);
		_puts("\n");
	}
	vars->status = 0;
}

/**
 * new_setenv - this edits existing variable or create new environment
 * @vars: it points to struct of the variable
 * by Stanley Ibeneme and Philadelphia Olawale-Adedotun
 * Return: void.
 */
void new_setenv(vars_t *vars)
{
	char **key;
	char *var;

	if (vars->av[1] == NULL || vars->av[2] == NULL)
	{
		print_error(vars, ": number of arguments Incorrect\n");
		vars->status = 2;
		return;
	}
	key = find_key(vars->env, vars->av[1]);
	if (key == NULL)
		add_key(vars);
	else
	{
		var = add_value(vars->av[1], vars->av[2]);
		if (var == NULL)
		{
			print_error(vars, NULL);
			free(vars->buffer);
			free(vars->commands);
			free(vars->av);
			free_env(vars->env);
			exit(127);
		}
		free(*key);
		*key = var;
	}
	vars->status = 0;
}

/**
 * new_unsetenv - it removes an environment variable
 * @vars: this points to struct of variables
 * by Stanley Ibeneme and Philadelphia Olawale-Adedotun
 * Return: void.
 */
void new_unsetenv(vars_t *vars)
{
	char **key, **newenv;

	unsigned int s, t;

	if (vars->av[1] == NULL)
	{
		print_error(vars, ": number of arguments Incorrect\n");
		vars->status = 2;
		return;
	}
	key = find_key(vars->env, vars->av[1]);
	if (key == NULL)
	{
		print_error(vars, ": No variable available to unset");
		return;
	}
	for (s = 0; vars->env[s] != NULL; s++)
		;
	newenv = malloc(sizeof(char *) * s);
	if (newenv == NULL)
	{
		print_error(vars, NULL);
		vars->status = 127;
		new_exit(vars);
	}
	for (s = 0; vars->env[s] != *key; s++)
		newenv[s] = vars->env[s];
	for (t = s + 1; vars->env[t] != NULL; t++, s++)
		newenv[s] = vars->env[t];
	newenv[s] = NULL;
	free(*key);
	free(vars->env);
	vars->env = newenv;
	vars->status = 0;
}
