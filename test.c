#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include "shell.h"

#define MAX_LINE_LENGTH 1024
#define MAX_ARGUMENTS 64

void execute_command(char *command, char *arguments[])
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("Fork failed");
		return;
	}
	else if (pid == 0)
	{
		execv(command, arguments);
		perror("Execv Failed");
		exit(1);
	}
	else
	{
		int status;

		waitpid(pid, &status, 0);
	}
}
void list_files(void)
{
	struct dirent *entry;
	DIR *dp = opendir(".");

	if (dp == NULL)
	{
		perror("file or directory does not exist\n");
		return;
	}
	while ((entry = readdir(dp)) != NULL)
	{
		printf("%s\n", entry->d_name);
	}
	closedir(dp);
}
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	while (1)
	{
		printf("Dreamteam$ ");

		if ((read == getline(&line, &len, stdin))` == -1)
		{
			perror("file or directory does not exist");
			return (1);
	}
	char *token;
	char *command = NULL;
	char *arguments[MAX_ARGUMENTS];
	int argCount = 0;

	token = strtok(line, "\t\n");

	while (token != NULL)
	{
		if (command == NULL)
		{
			command = token;
		}
		else
		{
			arguments[argCount] = token;
			argCount++;
		}
			token = strtok(NULL, "\t\n");
	}
	if (command != NULL)
	{
		arguments[argCount] = NULL;

		if (strcmp(command, "cd") == 0)
		{
			if (argCount > 0)
			{
				if (chdir(arguments[0]) != 0)
				{
					perror("Directory not found");
				}
			}
				else
				{
					perror("Directory not found");
				}
		}
		else if (strcmp(command, "exit") == 0)
		{
			free(line);
			exit(0);
		}
		else if (strcmp(command, "ls") == 0)
		{
			list_files();
		}
		else
		{
			execute_command(command, arguments);
		}
	}
	}
	free(line);
	return (0);

}

