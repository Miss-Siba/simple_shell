#include "shell.h"
#define MAX_ARGS 64
/**
 * parse_and_execute - parse and execute
 * @input: input
 */
void parse_and_execute(char *input)
{
	char *commands[MAX_ARGS];
	char *args[MAX_ARGS];
	int i, j, k = 0;
	char *token = strtok(input, ";");

	while (token != NULL)
	{
		commands[i++] = token;
		token = strtok(NULL, ";");
	}
	for (j = 0; j < i; j++)
	{
		token = strtok(commands[j], " ");
		while (token != NULL)
		{
			args[k++] = token;
			token = strtok(NULL, " ");
		}
		args[k] = NULL;
		if (strcmp(args[0], "&&") == 0)
		{
			if (j > 0 && WEXITSTATUS(system(NULL)) == 0)
			{
				parse_and_execute(commands[j + 1]);
			}
		}
		else if (strcmp(args[0], "||") == 0)
		{
			if (j > 0 && WEXITSTATUS(system(NULL)) != 0)
			{
				parse_and_execute(commands[j + 1]);
			}
		}
		else
		{
		execute_command(args);
		}
	}
}
