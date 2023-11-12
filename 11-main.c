#include "shell.h"

int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nchars_read;

	while (1)
	{
		printf("Dreamteam$ ");
		nchars_read = getline(&line, &len, stdin);

		if (nchars_read == -1)
		{
			perror("unable to getline");
			break;
		}
		line[strcspn(line, "\n")] = '\0';

		if (strcmp(line, "exit") == 0)
		{
			printf("Exititng the shell\n.");
			break;
		}
		parse_and_execute(line);
	}
	free(line);
	return (0);
}
