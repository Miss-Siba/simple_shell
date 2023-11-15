#include "shell.h"
/**
 * parse_line - Parses a line of input into tokens
 * @line: a pointer to a string containing the input
 * Return: A pointer to an array of strings containing the tokens
 */
char **parse_line(char *line)
{
	char **tokens = malloc(MAX_LINE * sizeof(char *));
	char *token;
	int index = 0;

	token = strtok(line, " \t\r\n\a");
	while (token != NULL)
	{
		tokens[index] = token;
		index++;
		token = strtok(NULL, "\t\r\n\a");
	}
tokens[index] = NULL;
return (tokens);
}

/**
 * is_comment -  Checks if a line of input is a comment
 * @line: a pointer to a string containing the input
 * Return: 1 if line is a comment or 0 if it is not
 */
int is_comment(char *line)
{
	return (line[0] == '#');
}

