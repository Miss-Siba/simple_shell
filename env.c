#include "shell.h"
/**
 * print_env - prints the current environment
 */

void print_env(void)
{
	char **env = environ;

	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}
