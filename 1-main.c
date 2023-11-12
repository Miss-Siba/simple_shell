#include "shell.h"
/**
 * main - main function.
 * Return: 0
 */
int main(void)
{
	char *line = NULL, **tokens;
	size_t len = 0;
	ssize_t nchars_read;
	int token_count = 0, i;

	while (1)
	{
		printf("Dreamteam$ "), fflush(stdout);
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
		line[strcspn(line, "\n")] = '\0';
		tokens = tokenize_line(line, &token_count);
		if (tokens == NULL)
		{
			perror("Tokenization failed");
			return (-1);
		}
		if (tokens[0] != NULL)
		{
			if (strcmp(tokens[0], "cd") == 0)
			{
				handle_cd(tokens);
			}
		}
		execute_command(tokens);
		for (i = 0; i < token_count; free(tokens[i++]))

		free(tokens);
	}
	free(line);
	return (0);
}
