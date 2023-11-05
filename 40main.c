#include “shell.h”

int main(int c, char **argv)
{ 
	char *line = NULL;
	size_t len = 0;
	ssize_t nchars_read;
	(void)c;

	while (1)
	{ 
		printf("Dreamteam$ ");
		nchars_read = getline(&line, &len, stdin);
		if (nchars_read == -1)
		{
			perror(“Input error.\n”);
			return (-1);
		}
		if (feof(stdin)) 
		{
			return (-1);
		}
		process_line(line, argv);
	}
	free(line);
	return (0);
}
void process_line(char *line, char **argv)
{
	char *line_copy = NULL;
	int token_count = 0;
	char *token;
	int i;

	line_copy = malloc(sizeof(char) * strlen(line));
	if (line_copy == NULL)
	{
		perror("Failed to allocate memory");
		return;
	}
	strcpy(line_copy, line);
	token_count = count_tokens(line);
	argv = malloc(sizeof(char *) * token_count);
	if (argv == NULL)
	{
		perror("Failed to allocate memory");
		free(line_copy);
		return;
	}
	token = strtok(line, " \t\n");
	for (i = 0; token != NULL; i++)
	{
		argv[i] = malloc(sizeof(char) * strlen(token));
    		if (argv[i] == NULL)
    		{
        		perror("Failed to allocate memory");
			free(line_copy);
			free(argv);
			return;
		}
	strncpy(argv[i], token, strlen(token));
	argv[i][strlen(token)] = '\0';
	token = strtok(NULL, " \t\n");
	}
	argv[i] = NULL;
	execute_command(argv);
	free(line_copy);
	free(argv);
}

int count_tokens(char *line)
{
	int token_count = 0;
	char *token;
	char *line_copy = NULL;

	line_copy = malloc(sizeof(char) * strlen(line));
	if (line_copy == NULL)
	{
		perror("Failed to allocate memory");
		return (-1);
	}
	strcpy(line_copy, line);
	token = strtok(line_copy, " \t\n");
	while (token != NULL)
	{
		token_count++;
		token = strtok(NULL, " \t\n");
	}
	free(line_copy);
	return (token_count);
}
