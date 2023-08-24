#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/stat.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

/**
 * struct variables - The variables
 * @status: The exit status
 * @av: The command line arguments
 * @env: The environment variables
 * @buffer: The buffer of command
 * @argv: The arguments at opening of shell
 * @commands: The double pointer to commands
 * @count: The count of commands entered
 * By Stanley Ibeneme and Philadelphia Olawale-Adedotun
 */
typedef struct variables
{
	int status;
	char **av;
	char **env;
	char *buffer;
	char **argv;
	char **commands;
	size_t count;
} vars_t;

/**
 * struct builtins - struct for the particular builtin functions
 * @name: name of the builtin command
 * @f: function for its corresponding builtin
 * By Stanley Ibeneme and Philadelphia Olawale-Adedotun
 */
typedef struct builtins
{
	char *name;
	void (*f)(vars_t *);
} builtins_t;

void free_env(char **env);
char **make_env(char **env);

char *_uitoa(unsigned int count);
void _puts2(char *str);
void print_error(vars_t *vars, char *msg);

char **tokenize(char *buffer, char *delimiter);
char *new_strtok(char *str, const char *delim);
char **_realloc(char **ptr, size_t *size);

ssize_t _puts(char *str);
int _strcmpr(char *strcmp1, char *strcmp2);
char *_strdup(char *strtodup);
char *_strcat(char *strc1, char *strc2);
unsigned int _strlen(char *str);

int _atoi(char *str);
char *add_value(char *key, char *value);
char **find_key(char **env, char *key);
void add_key(vars_t *vars);

int execute_cwd(vars_t *vars);
int path_execute(char *command, vars_t *vars);
char *find_path(char **env);
void check_for_path(vars_t *vars);
int check_for_dir(char *str);

void (*check_for_builtins(vars_t *vars))(vars_t *vars);
void new_setenv(vars_t *vars);
void _env(vars_t *vars);
void new_exit(vars_t *vars);
void new_unsetenv(vars_t *vars);

#endif /* _SHELL_H_ */
