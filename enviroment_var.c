#include "shell.h"
/**
 * main - setenv and unsetenv.
 * Return: 0
 */

int main(void)
{
	char *value;

	if (setenv("VARIABLE", "dreamteam", 1) != 0)
	{
		fprintf(stderr, "Error setting environment variable\n");
			return (-1);
	}
	else
	{
		value = getenv("VARIABLE");
		printf("VARIABLE = %s\n", value);
	}
	if (unsetenv("VARIABLE") != 0)
	{
		fprintf(stderr, "Error unsetting environment variable\n");
		return (-1);
	}

	value = getenv("VARIABLE");
	printf("New VARIABLE = %s\n", value);

	return (0);
}

