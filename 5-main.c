#include "shell.h"
/**
 * main - main function
 * Return: 0
 */
int main(void)
{
	char *line = NULL;
	size_t length = 0;
	ssize_t nchars_read;
	char **argv;
	int token_count;

	while (1)
	{
		printf("Dreamtean$ ");
		nchars_read = getline(&line, &length, stdin);
		if (nchars_read == -1)
		{
			perror("Command not found\n");
			return (-1);
		}
		if (feof(stdin))
		{
			return (-1);
		}
		line[strcspn(line, "\n")] = '\0';
		if (is_builtin(line))
		{
			if (strcmp(line, "env") == 0)
			{
				print_env();
			}
			free(line);
			continue;
		}
		argv = tokenize_line(line, &token_count);
		if (argv == NULL)
		{
			perror("Tokenization failed");
			free(line);
			return (-1);
		}
		execute_command(argv), free_tokens(argv, token_count);
		}
	free(line);
	return (0);
}
