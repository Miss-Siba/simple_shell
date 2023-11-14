#include "shell.h"
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
		char *file = argv[i];
		pid_t pid = fork();

		if (pid == -1)
		{
			perror("Fork failed");
			return (-1);
		}
		else if (pid == 0)
		{
			char *cmd[] = {NULL, NULL};
			cmd[0] = "which";
			cmd[1] = file;
			execvp("which", cmd);
			perror("Execvp Failed");
			exit(EXIT_FAILURE);
		}
		else
		{
			int status;

			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
			{
				int exit_status = WEXITSTATUS(status);
				if (exit_status != 0)
				{
					fprintf(stderr, "Command failed with exit status %d\n", exit_status);
					return (-1);
				}
			}
			else
			{
				fprintf(stderr, "Command terminated abnormally\n");
				return (-1);
			}
		}
	}
	return (0);
}
