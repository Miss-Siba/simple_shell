#include "shell.h"
/**
 * handle_builtin - handles builtin commands
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

