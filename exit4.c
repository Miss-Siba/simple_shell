#include "shell.h"

/**
 * is_builtin - checks for build in function "exit".
 * @cmd: command
 * Return:0
 */

int is_builtin(char *cmd)
{
	return (strcmp(cmd, "exit") == 0);
}
/**
 * execute_command - executes exit command.
 * @argv: argument vector.
 */

void execute_command(char **argv)
{


	pid_t pid = fork();

	if (pid == -1)
	{
		perror("Fork failed");
		exit(1);
	}
	else if (pid == 0)
	{
		execv(argv[0], argv);
		perror("Command not found");
		exit(1);
	}
	else
	{
		int status;

		waitpid(pid, &status, 0);
	}
}
/**
 * free_tokens - frees tokens.
 * @tokens: tokens.
 * @token_count: token count
 */

void free_tokens(char **tokens, int token_count)
{
	int i;

	for (i = 0; i < token_count; i++)
	{
		free(tokens[i]);
	}
	free(tokens);
}
