#include "shell.h"

char **parse_line(char *line)
{
	char **tokens = malloc(MAX_LINE * sizeof(char *));
	char *token;
	int index = 0;

	token = strtok(line, " \t\r\n\a");
	
	while (token != NULL)
	{
		tokens[index] = token;
		index++;
		token = strtok(NULL, "\t\r\n\a");
	}
tokens[index] = NULL;
return tokens;
}

void execute_command(char **args)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			perror("simple shell");
		}
	exit(EXIT_FAILURE);
  	}
	else if (pid < 0)
	{
		perror("shell");
	}
	else
	{
		do
		{
			waitpid(pid, &status, WUNTRACED);
		}
		while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
}

int is_comment(char *line)
{
	return line[0] == '#';
}

int main(void) 
{
	char *line;
	char **args;
	int should_run = 1;

	while (should_run)
	{
		printf("dreamteam$");
		fflush(stdout);

		size_t len = 0;
		getline(&line, &len, stdin);

		if (is_comment(line))
		{
			continue;
		}

		args = parse_line(line);

		if (strcmp(args[0], "exit") == 0)
		{
			should_run = 0;
		}
		else
		{
			execute_command(args);
		}
		free(line);
		free(args);
	}
return 0;
}
