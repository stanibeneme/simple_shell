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
