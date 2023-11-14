#include "shell.h"
/**
 * initialize_shell_state - initialization
 * @state: shell state
 */
void initialize_shell_state(ShellState *state)
{
	state->count = 0;
}
/**
 * process_command - processes command
 * @line: line
 * @state: shell state
 */
void process_command(char *line, ShellState *state)
{
	char *alias_name, *alias_value;

	if (strcmp(line, "exit") == 0)
	{
		printf("Exiting the shell.\n");
		exit(0);
	}
	else if (strncmp(line, "alias", 5) == 0)
	{
		alias_name = strtok(line + 6, "=");
		alias_value = strtok(NULL, "\0");

		if (alias_name != NULL)
		{
			if (alias_value != NULL)
			{
				add_alias(state, alias_name, alias_value);
			}
			else
			{
				list_aliases(state);
			}
		}
	}
	else
	{
		parse_and_execute(line);
	}
}
/**
 * main - main
 * Return: 0
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nchars_read;
	int i;

	ShellState state;

	initialize_shell_state(&state);

	while (1)
	{
		printf("Dreamteam$ ");
		nchars_read = getline(&line, &len, stdin);

		if (nchars_read == -1)
		{
			perror("Unable to get line");
			return (-1);
		}
		line[strcspn(line, "\n")] = '\0';

		process_command(line, &state);
	}
	for (i = 0; i < state.count; i++)
	{
		free(state.aliases[i].name);
		free(state.aliases[i].value);
	}
	free(line);
	return (0);
}
