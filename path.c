#include "shell.h"
/**
 * execute_single_command - single command execution
 * @file: file
 */
void execute_single_command(char *file)
{
	char *cmd[] = {"which", file, NULL};

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
	if (WIFEXITED(status) && WEXITEDSTATUS(status) != 0)
	{
		fprintf(stderr, "Command failed with exit status %d\n", exit_status);
		return (-1);
	}
	else
	{
		fprintf(stderr, "Command terminated abnormally\n");
		return (-1);
	}
	return (0);
}
/**
 * main - handles the path.
 * @argc: argument count,
 * @argv: array
 * Return: 0 (success) or -1(failure)
 */

int main(int argc, char *argv[])
{
	int i;

	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s filename", argv[0]);
		return (-1);
	}
	for (i = 1; i < argc; i++)
	{
		pid_t pid = fork();

		if (pid == -1)
		{
			perror("Fork failed");
			return (-1);
		}
		else if (pid == 0)
		{
			execute_command(argv[i]);

		}
		else
		{
			int status;

			waitpid(pid, &status, 0);

			if (handle_execution_result(status) != 0)
			{
				return (-1);
			}
		}
	}
	return (0);
}
