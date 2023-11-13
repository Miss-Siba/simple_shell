#include "shell.h"
/**
 * add_alias - add alias.
 * @state: shell state
 * @alias_name: name
 * @alias_value: value of alias
 */
void add_alias(ShellState *state, char *alias_name, char *alias_value)
{
	int i = 0;

	if (state->count < MAX_ALIAS)
	{
		for (i = 0; i < state->count; i++)
		{
			if (strcmp(alias_name, state->aliases[i].name) == 0)
			{
				free(state->aliases[i].value);
				state->aliases[i].value = strdup(alias_value);
				printf("Alias '%s' updated: %s\n", alias_name, alias_value);
				return;
			}
		}
		state->aliases[state->count].name = strdup(alias_name);
		state->aliases[state->count].value = strdup(alias_value);
		(state->count)++;
		printf("Alias '%s' added: %s\n", alias_name, alias_value);
	}
	else
	{
		fprintf(stderr, "Max alias reached.\n");
	}
}
/**
 * list_aliases - lists alias.
 * @state: shell state
 */
void list_aliases(ShellState *state)
{
	int i;


	if (state->count > 0)
	{
		printf("List of aliases:\n");
		for (i = 0; i < state->count; i++)
		{
			printf("%s='%s'\n", state->aliases[i].name, state->aliases[i].value);
		}
	}
		else
		{
			printf("No aliases.\n");
		}
}
/**
 * remove_alias - remove alias
 * @alias_name: name
 * @state: shell state
 */
void remove_alias(ShellState *state, char *alias_name)
{
	int i;
	int j;

	for (i = 0; i < state->count; i++)
	{
		if (strcmp(alias_name, state->aliases[i].name) == 0)
		{
			free(state->aliases[i].name);
			free(state->aliases[i].value);

			for (j = i; j < state->count - 1; j++)
			{
				state->aliases[j] = state->aliases[j + 1];
			}
			(state->count)--;
			printf("Alias '%s' removed. \n", alias_name);
			return;
		}
	}
	fprintf(stderr, "Alias '%s' not found.\n", alias_name);
}
