#include "shell.h"

/**
 * _puts - it writes a string to the standard output
 * @str: the string to write
 * by Stanley Ibeneme and Philadelphia Olawale-Adedotun
 * Return: the number of chars printed or -1 on failure
 */
ssize_t _puts(char *str)
{
	ssize_t num, len;

	num = _strlen(str);
	len = write(STDOUT_FILENO, str, num);
	if (len != num)
	{
		perror("Fatal Error");
		return (-1);
	}
	return (len);
}

/**
 * _strdup - this returns pointer to new mem alloc space
 * @strtodup: the string to be duplicated
 * by Stanley Ibeneme and Philadelphia Olawale-Adedotun
 * Return: pointer to the duplicated string
 */
char *_strdup(char *strtodup)
{
	char *copy;

	int len, s;

	if (strtodup == 0)
		return (NULL);

	for (len = 0; strtodup[len]; len++)
		;
	copy = malloc((len + 1) * sizeof(char));

	for (s = 0; s <= len; s++)
		copy[s] = strtodup[s];

	return (copy);
}

/**
 * _strcmpr - this compares two strings
 * @strcmp1: first string of the two strings to be compared
 * @strcmp2: second string of the two strings to be compared
 * by Stanley Ibeneme and Philadelphia Olawale-Adedotun
 * Return: 0 on success, else is a failure
 */
int _strcmpr(char *strcmp1, char *strcmp2)
{
	int s;

	s = 0;
	while (strcmp1[s] == strcmp2[s])
	{
		if (strcmp1[s] == '\0')
			return (0);
		s++;
	}
	return (strcmp1[s] - strcmp2[s]);
}

/**
 * _strcat - this concatenates two strings
 * @strc1: the first string
 * @strc2: the second string
 * by Stanley Ibeneme and Philadelphia Olawale-Adedotun
 * Return: pointer
 */

char *_strcat(char *strc1, char *strc2)
{
	char *newstring;
	unsigned int len1, len2, newlen, s, t;

	len1 = 0;
	len2 = 0;
	if (strc1 == NULL)
		len1 = 0;
	else
	{
		for (len1 = 0; strc1[len1]; len1++)
			;
	}
	if (strc2 == NULL)
		len2 = 0;
	else
	{
		for (len2 = 0; strc2[len2]; len2++)
			;
	}
	newlen = len1 + len2 + 2;
	newstring = malloc(newlen * sizeof(char));
	if (newstring == NULL)
		return (NULL);
	for (s = 0; s < len1; s++)
		newstring[s] = strc1[s];
	newstring[s] = '/';
	for (t = 0; t < len2; t++)
		newstring[s + 1 + t] = strc2[t];
	newstring[len1 + len2 + 1] = '\0';
	return (newstring);
}

/**
 * _strlen - this returns the length of the string
 * @str: the string to be measured
 * by Stanley Ibeneme and Philadelphia Olawale-Adedotun
 * Return: the length of string
 */
unsigned int _strlen(char *str)
{
	unsigned int len;

	len = 0;

	for (len = 0; str[len]; len++)
		;
	return (len);
}
