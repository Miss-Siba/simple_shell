#include "shell.h"

int main(void)
{
	char *buffer = NULL;
	size_t size = 0;
	ssize_t chars_read;

	chars_read = _getline(&buffer, &size, stdin);

	if (chars_read > 0)
	{
		printf("Read %ld character: %s\n",(long)chars_read, buffer);
	}
		else if (chars_read == 0)
		{
			printf("No characters read.\n");
		}
		else
		{
			printf("Error reading.\n");
		}
	free(buffer);
	return (0);
}
