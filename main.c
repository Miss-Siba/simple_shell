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
	int token_count = 0;

	while (1)
	{
		printf("Dreamteam$ "), fflush(stdout);
		nchars_read = getline(&line, &len, stdin);
		if (nchars_read == -1)
		{
			perror("Input error.\n");
			break;
		}
		if (feof(stdin))
		{
			break;
		}
		line[strcspn(line, "\n")] = '\0';
		if (strcmp(line, "exit") == 0)
		{
			printf("Exiting the shell.\n");
			break;
		}
		tokens = tokenize_line(line, &token_count);
		if (tokens == NULL)
		{
			perror("Tokenization failed");
			continue;
		}
		execute_command(tokens);
		free_tokens(tokens, token_count);
	}
	free(line);
	return (0);
}
