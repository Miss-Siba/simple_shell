#include "shell.h"
/**
 * print_env - prints the current environment
 */

void print_env(void)
{

	int i = 0;

	for (i = 0; environ != NULL; i++)
	{
		printf("%s\n", environ[i]);
	}
}
