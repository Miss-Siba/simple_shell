#include "shell.h"
/**
 * main - main function.
 * Return: 0
 */

int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nchars_read;
	int token_count = 0;
	char **tokens;
	int i;

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
		tokens = tokenize_line(line, &token_count);

		if (tokens == NULL)
		{
			perror("Tokenization failed");
			return (-1);
		}
		execute_command(tokens);
		for (i = 0; i < token_count; i++)
		{
			free(tokens[i]);
		}
		free(tokens);
	}
	free(line);
	return (0);
}
