#include "shell.h"
/**
 * path_execute - this executes a command in path
 * @command: the full path to command
 * @vars: this points to struct of the variables
 * by Stanley Ibeneme and Philadelphia Olawale-Adedotun
 * Return: 0 on success, 1 on failure
 */
int path_execute(char *command, vars_t *vars)
{
	pid_t child_pid;

	if (access(command, X_OK) == 0)
	{
		child_pid = fork();
		if (child_pid == -1)
			print_error(vars, NULL);
		if (child_pid == 0)
		{
			if (execve(command, vars->av, vars->env) == -1)
				print_error(vars, NULL);
		}
		else
		{
			wait(&vars->status);
			if (WIFEXITED(vars->status))
				vars->status = WEXITSTATUS(vars->status);
			else if (WIFSIGNALED(vars->status) && WTERMSIG(vars->status) == SIGINT)
				vars->status = 130;
			return (0);
		}
		vars->status = 127;
		return (1);
	}
	else
	{
		print_error(vars, ": Permission denied\n");
		vars->status = 126;
	}
	return (0);
}

/**
 * find_path - this finds PATH variable
 * @env: the array of environment variables
 * by Stanley Ibeneme and Philadelphia Olawale-Adedotun
 * Return: this pounts to the node that contains NULL on failure or the PATH
 */
char *find_path(char **env)
{
	char *path = "PATH=";
	unsigned int s, t;

	for (s = 0; env[s] != NULL; s++)
	{
		for (t = 0; t < 5; t++)
			if (path[t] != env[s][t])
				break;
		if (t == 5)
			break;
	}
	return (env[s]);
}
/**
 * check_for_path - this checks if command is in the PATH
 * @vars: variables
 * by Stanley Ibeneme and Philadelphia Olawale-Adedotun
 * Return: void
 */
void check_for_path(vars_t *vars)
{
	char *path, *path_dup = NULL, *check = NULL;
	unsigned int s = 0, r = 0;
	char **path_tokens;
	struct stat buf;

	if (check_for_dir(vars->av[0]))
		r = execute_cwd(vars);
	else
	{
		path = find_path(vars->env);
		if (path != NULL)
		{
			path_dup = _strdup(path + 5);
			path_tokens = tokenize(path_dup, ":");
			for (s = 0; path_tokens && path_tokens[s]; s++, free(check))
			{
				check = _strcat(path_tokens[s], vars->av[0]);
				if (stat(check, &buf) == 0)
				{
					r = path_execute(check, vars);
					free(check);
					break;
				}
			}
			free(path_dup);
			if (path_tokens == NULL)
			{
				vars->status = 127;
				new_exit(vars);
			}
		}
		if (path == NULL || path_tokens[s] == NULL)
		{
			print_error(vars, ": not found\n");
			vars->status = 127;
		}
		free(path_tokens);
	}
	if (r == 1)
		new_exit(vars);
}
/**
 * execute_cwd - this executes the command in current working directory
 * @vars: the pointer to struct of variables
 * by Stanley Ibeneme and Philadelphia Olawale-Adedotun
 * Return: 0 on success, 1 on failure
 */
int execute_cwd(vars_t *vars)
{
	pid_t child_pid;
	struct stat buf;

	if (stat(vars->av[0], &buf) == 0)
	{
		if (access(vars->av[0], X_OK) == 0)
		{
			child_pid = fork();
			if (child_pid == -1)
				print_error(vars, NULL);
			if (child_pid == 0)
			{
				if (execve(vars->av[0], vars->av, vars->env) == -1)
					print_error(vars, NULL);
			}
			else
			{
				wait(&vars->status);
				if (WIFEXITED(vars->status))
					vars->status = WEXITSTATUS(vars->status);
				else if (WIFSIGNALED(vars->status) && WTERMSIG(vars->status) == SIGINT)
					vars->status = 130;
				return (0);
			}
			vars->status = 127;
			return (1);
		}
		else
		{
			print_error(vars, ": Permission denied\n");
			vars->status = 126;
		}
		return (0);
	}
	print_error(vars, ": not found\n");
	vars->status = 127;
	return (0);
}
/**
 * check_for_dir - this checks if command is part of a path
 * @str: command
 * by Stanley Ibeneme and Philadelphia Olawale-Adedotun
 * Return: 1 on success, 0 on failure
 */
int check_for_dir(char *str)
{
	unsigned int s;

	for (s = 0; str[s]; s++)
	{
		if (str[s] == '/')
			return (1);
	}
	return (0);
}
