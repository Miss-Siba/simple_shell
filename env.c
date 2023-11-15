#include "shell.h"
/**
 * print_env - prints the current environment
 */

void print_env(void)
{
	char **env = environ;

	while (*env)
	{
	write(1, *env, strlen(*env));
	write(1, "\n", 1);
	env++;
	}
}
