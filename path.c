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
		perror("Usage: ./path filename");
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
			char *cmd[] = {"which", file, NULL};

			execvp("which", cmd);
			perror("Execvp Failed");
				return (-1);
			}
		else
		{
		int status;

		waitpid(pid, &status, 0);
		}
	}
	return (0);
}
