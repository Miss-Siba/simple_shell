#include "shell.h"
/**
 * handle_builtin - hand;es builtin commands
 * @tokens: tokens
 * @token_count: counts tokens
 * Return: 0
 */
int handle_builtin(char **tokens, int token_count)
{
	int status = -1;
	int temp_status;

	if (token_count == 1)
	{
		free(tokens);
		status = 0;
	}
	else if (token_count == 2)
	{
		temp_status = atoi(tokens[1]);
		if (temp_status != 0)
		{
			status = temp_status;
			free(tokens);
		}

		else
		{
			perror("Invalid exit status");
		}
	}
	else
	{
		perror("Too many arguments");
	}
	return (status);
}
/**
 * main - main
 * Return: 0
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nchars_read;
	int token_count = 0;
	char **tokens;
	int status = 0;

	while (1)
	{
		printf("Dreamteam$ ");
		nchars_read = getline(&line, &len, stdin);

		if (nchars_read == -1)
		{
			perror("Unable to get line.\n");
			return (-1);
		}
		if (feof(stdin))
		{
			return (-1);
		}
		tokens = tokenize_line(line, &token_count);
		if (is_builtin(tokens[0]))
		{
			handle_builtin(tokens, token_count);
			if (status != -1)
			{
				return (status);
			}
		}
		else
		{
			execute_command(tokens);
		}
		free_tokens(tokens, token_count);
	}
	free(line);
	return (0);
}
