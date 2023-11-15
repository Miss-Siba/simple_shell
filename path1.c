#include "shell.h"
/**
 * execute_single_command - single command execution
 * @file: file
 */
void execute_single_command(char *file)
{
	char *cmd[3];

	cmd[0] = "which";
	cmd[1] = file;
	cmd[2] = NULL;

	execvp(cmd[0], cmd);
	perror("Command execution failed");
	exit(EXIT_FAILURE);
}

/**
 * handle_execution_result - handles result
 * @status: status
 * Return: 0
 */
int handle_execution_result(int status)
{
	int exit_status = WEXITSTATUS(status);

	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		printf(stderr, "Command failed with exit status %d\n", exit_status);
		return (-1);
	}
	else if (!WIFEXITED(status))
	{
		printf(stderr, "Command terminated abnormally\n");
		return (-1);
	}
	return (0);
}

