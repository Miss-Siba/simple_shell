#include "shell.h"

/**
 * read_and_parse_input -  Reads line from stdin and parses into arguments
 * @line: pointer to buffer
 * @len: size of buffer
 * @args: array of pointers to store parsed arguments
 * Return: 1 if input is valid or 0 if it's exit
 */

int read_and_parse_input(char *line, size_t len, char *args[])
{
	ssize_t nread;
	int i;

	nread = getline(&line, &len, stdin);
	if (nread == -1)
	{
		perror("getline");
		return (0);
	}
	line[nread - 1] = '\0';
	if (strcmp(line, "exit") == 0)
	{
		return (0);
	}
	else
	{
		i = 0;
		args[i] = strtok(line, " \t");
		while (args[i] != NULL)
		{
			i++;
			args[i] = strtok(NULL, " \t");
		}
		args[i] = NULL;
		return (1);
	}
}

