#include "shell.h"

/**
 * main - exits the program.
 * Return: 0
 */
int main(void)
{
	char *line = NULL;
	size_t length = 0;
	ssize_t nchars_read;
	int token_count;
	char **argv;

	while (1)
	{
		printf("Dreamteam$ ");
		nchars_read = getline(&line, &length, stdin);
		if (nchars_read == -1)
		{
			perror("Command not found.\n");
			return (-1);
		}
		if (feof(stdin))
		{
			return (-1);
		}
		argv = tokenize_line(line, &token_count);

		if (argv == NULL)
		{
			perror("Tokenization failed");
			return (-1);
		}
		if (is_builtin(argv[0]))
		{
			free_tokens(argv, token_count);
			free(line);
			return (0);
		}
		else
		{
			execute_command(argv);
			free_tokens(argv, token_count);
		}
	}
	free(line);
	return (0);
}
