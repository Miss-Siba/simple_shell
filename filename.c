#include "shell.h"
/**
 * processFile - processes file.
 * @filename: filename
 * Return: 0
 */
int processFile(const char *filename)
{
	FILE *file;
	char *line;
	size_t len = 0;
	char **argv;
	int argc;

	file = fopen(filename, "r");

	if (file == NULL)
	{
		perror("Error opening file");
		exit(-1);
	}

	while (getline(&line, &len, file) != -1)
	{
		if (line[strlen(line) - 1] == '\n')
		{
			line[strlen(line) - 1] = '\0';
		}
		argv = tokenize_line(line, &argc);

		if (argv != NULL)
		{

			execute_command(argv);
			free_tokens(argv, argc);
		}
	}
	free(line);
	fclose(file);

	return (0);
}
