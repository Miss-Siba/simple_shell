#include "shell.h"
/**
 * main - main
 * @argc: argument count
 * @argv: argument vector
 * Return: 0
 */
int main(int argc, char *argv[])
{
	const char *filename;
	FILE *file;
	char *line;
	size_t len = 0;

	if (argc != 2)
	{
		fprintf(stderr, "Useage: %s <filename>\n", argv[0]);
		exit(-1);
	}
	filename = argv[1];
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
