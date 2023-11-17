#include "shell.h"
/**
 * handle_exit - handles exit.
 * @args: arguments
 * @exit_flag: exit
 * Return: Status
 */
int handle_exit(char **args, int *exit_flag)
{
	int status = 0;

	if (args[1] != NULL)
	{
		status = atoi(args[1]);
	}

	*exit_flag = 1;
	return (status);
}
