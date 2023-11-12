#include "shell.h"

/**
 * parse_line - Parses a line of input into tokens
 * @line: a pointer to a string containing the input
 * Return: A pointer to an array of strings containing the tokens
 */
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
return (tokens);
}

/**
 * execute_command - Executes a command given by a user
 * @args: a pointer to an array of strings containing a command and arguments
 * Return: None
 */
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
		do {
			waitpid(pid, &status, WUNTRACED);
		}

		while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
}

/**
 * is_comment -  Checks if a line of input is a comment
 * @line: a pointer to a string containing the input
 * Return: 1 if line is a comment or 0 if it is not
 */
int is_comment(char *line)
{
	return (line[0] == '#');
}

/**
 * main - main function of the simple shell program
 *
 * Return: 0 if the program exits normally, non-zero otherwise
 */
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
return (0);
}
