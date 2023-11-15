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
	int exit_flag = 0;


	ShellState state;

	initialize_shell_state(&state);


	while (1)
	{
		printf("$ "), fflush(stdout);
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
		
		tokens = tokenize_line(line, &token_count);
		if (tokens == NULL)
		{
			perror("Tokenization failed");
			continue;
		}
		if (strcmp(tokens[0], "exit") == 0)
		{
			handle_exit(tokens, &exit_flag);
			free_tokens(tokens, token_count);
			break;
		}
		if (strcmp(line, "env") == 0)
		{
			print_env();
		}

		execute_command(tokens);
		free_tokens(tokens, token_count);
	}
	free(line);
	return (0);
}
