#include "shell.h"

#define MAX_TOKENS 32
/**
 * tokenize_line -tokenizes line.
 * @line: line
 * @token_count: token count.
 * Return: tokens
 */

char **tokenize_line(char *line, int *token_count)
{
	char **tokens = (char **)malloc(MAX_TOKENS * sizeof(char *));
	int i;
	char *token;

	if (tokens == NULL)
	{
		perror("Memory allocation failed");
		return (NULL);
	}

	token = strtok(line, " \t\n");
	*token_count = 0;
	while (token != NULL)
	{
		tokens[*token_count] = strdup(token);
		if (tokens[*token_count] == NULL)
		{
			perror("Memory allocation for token failed");
			for (i = 0; i < *token_count; i++)
			{
				free(tokens[i]);
			}
			free(tokens);
			return (NULL);
		}
		(*token_count)++;
		if (*token_count >= MAX_TOKENS)
		{
			perror("Too many tokens in input");
			for (i = 0; i < *token_count; i++)
			{
				free(tokens[i]);
			}
			free(tokens);
			return (NULL);
		}
		token = strtok(NULL, " \t\n");
	}
	tokens[*token_count] = NULL;
	return (tokens);
}
/**
 * free_tokens - frees tokens.
 * @tokens: tokens.
 * @token_count: token count
 */
void free_tokens(char **tokens, int token_count)
{
	int i;

	for (i = 0; i < token_count; i++)
	{
		free(tokens[i]);
	}
	free(tokens);
}
