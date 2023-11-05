#include "shell.h"

int main(int c, char **argv)
{
	char *line = NULL;
	char *line_copy = NULL;
	size_t len = 0;
	ssize_t nchars_read;
	int token_count = 0;
	char *token;
	int i;
	(void)c;


	while (1)
	{
		printf("Dreamteam$ ");
		nchars_read = getline(&line, &len, stdin);

		if (nchars_read == -1)
		{
			perror("Input error.\n");
			return (-1);
		}
		if (feof(stdin))
		{
			return (-1);
		}

		line_copy = malloc(sizeof(char) * nchars_read);
		if (line_copy == NULL)
		{
			perror("Failed to allocate memory");
			return (-1);
		}
		strcpy(line_copy, line);

		token = strtok(line, " \t\n");

		while (token != NULL)
		{
			token_count++;
			token = strtok(NULL, " \t\n");
		}
		token_count++;

		argv = malloc(sizeof(char *) * token_count);

		token = strtok(line, " \t\n");

		for (i = 0; token != NULL; i++)
		{
			argv[i] = malloc(sizeof(char) * strlen(token));
			strcpy(argv[i], token);

			token = strtok(NULL, " \t\n");
		}
		argv[i] = NULL;

		execute_command(argv);
	}
	free(line_copy);
	free(line);
	return (0);
}
