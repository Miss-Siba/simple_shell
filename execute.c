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
 * execute_child - Executes the command in the child process.
 * @argv: Argument vector representing the command and its arguments.
 */
void execute_child(char **argv)
{
	execv(argv[0], argv);
	perror("Failed to execute command");
	exit(EXIT_FAILURE);
}
/**
 * execute_command - executes exit command.
 * @argv: argument vector.
 * Return: 1 if exit command, 0 otherwise.
 */

void execute_command(char **argv)
{


	if (strcmp(argv[0], "exit") == 0)
	{
		exit(EXIT_SUCCESS);
	}
	else if (strcmp(argv[0], "env") == 0)
	{
		print_env();
	}
	else
	{

		pid_t pid = fork();

		if (pid == -1)
		{
			perror("Fork failed");
			exit(EXIT_FAILURE);
		}
		else
		{
			execute_child(argv);
		}

	}
}
