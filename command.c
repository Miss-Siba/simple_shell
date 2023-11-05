#include "shell.h"
/**
 * execute_command - command line interpter.
 * @argv: command.
 */

void execute_command(char **argv)
{
	char *command = NULL;

	if (argv)
	{
		command = argv[0];

		if (execve(command, argv, NULL) == -1)
		{
			perror("Command not found");
		};
	}
}
