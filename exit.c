#include "shell.h"
/**
 * handle_exit - handles exit.
 * @args: arguments
 * Return: 0
 */
int handle_exit(char **args, int *exit_flag)
{
	int status = 0;

	if (args[1] != NULL)
	{
		status = atoi(args[1]);
	}

	printf("Exiting the shell with status %d.\n", status);
	*exit_flag = 1;
	return (status);
}
