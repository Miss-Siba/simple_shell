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
 * execute_parent - Waits for the child process to complete.
 * @pid: Process ID of the child process.
 */
void execute_parent(pid_t pid)
{
	int status;

	if (waitpid(pid, &status, 0) == -1)
	{
		perror("Error waiting for child process");
		exit(EXIT_FAILURE);
	}
	if (WIFEXITED(status))
	{
		printf("Child process exited with status %d\n", WEXITSTATUS(status));
	}
	else if (WIFSIGNALED(status))
	{
		printf("Child process terminated by signal %d\n", WTERMSIG(status));
	}
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
		printf("Exiting the shell.\n");
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
		else if (pid == 0)
		{
			execute_child(argv);
		}
		else
		{
			execute_parent(pid);
		}
	}
}
