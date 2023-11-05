#include "shell.h"

int main(void)
{
	char *line;
	size_t len = MAX_LINE;
	char *args[MAX_LINE / 2 + 1];
	int should_run = 1;
	int i;
	ssize_t nread;

	line = malloc(len);
	if (line == NULL)
	{
	perror("malloc");
	exit(1);
	}

	while (should_run)
	{
		printf("dreamteam$ ");
		fflush(stdout);
		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			perror("getline");
			break;
		}
		line[nread - 1] = '\0';
		if (strcmp(line, "exit") == 0)
		{
			should_run = 0;
		}
		else
		{
			i = 0;
			args[i] = strtok(line, " \t");

			while (args[i] != NULL)
			{
				i++;
				args[i] = strtok(NULL, " \t");
			}
			args[i] = NULL;
			pid_t pid = fork();

			if (pid < 0)
			{
				perror("fork");
				exit(1);
			}
			else if (pid == 0)
			{
				if (execvp(args[0], args) < 0)
				{
					perror(args[0]);
					exit(1);
				}
			}
			else
			{
				wait(NULL);
			}
		}
	}
	free(line);
	return (0);
}

