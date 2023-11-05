#include "shell.h"

int main(int i, char **argv)
{
	char *line = NULL;
	size_t length = 0;
	ssize_t nchars_read;
	int token_count = 0;

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
			free(line);
			free(argv);
			return (0);
		}
		else
		{
			execute_command(argv);
		}

		for (i = 0; i < token_count; i++)
		{
			free(argv[i]);
		}
		free(argv);
		}
	free(line);
	return (0);
}
