#include "shell.h"
/**
 * is_builtin - checks for built in function.
 * @cmd: command
 * Return:0
 */

int is_builtin(char *cmd)
{
	return (strcmp(cmd, "env") == 0 || strcmp(cmd, "exit") == 0 ||
			strcmp(cmd, "cd") == 0);
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
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		execv(argv[0], argv);
		perror("Command not found");
		printf(stderr, "Failed to execute command: %s\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	else
	{
		int status;

		waitpid(pid, &status, 0);

		if (WIFEXITED(status))
		{
			printf("Child process exited with status %d\n", WEXITSTATUS(status));
		}
		else if (WIFSIGNALED(status))
		{
			printf("Child process terminted by signal %d\n", WTERMSIG(status));
		}
	}
}

