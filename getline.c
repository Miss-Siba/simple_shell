#include "shell.h"
/**
 * _getline - gets line from stdin.
 * @buffer: buffer
 * @size: size
 * @stream: file
 * Return: total_chars
 */
ssize_t _getline(char **buffer, size_t *size, FILE *stream)
{
	ssize_t read_chars = 0;
	static ssize_t	total_chars;
	int ch;
	char *temp;

	if (*buffer == NULL)
	{
		*size = 128;
		*buffer = (char *)malloc(*size);
		if (*buffer == NULL)
		{
			perror("malloc");
			return (-1);
		}
	}
	while ((ch = getc(stream)) != EOF)
	{
		if (read_chars >= (ssize_t)(*size - 1))
		{
			*size *= 2;
			temp = (char *)realloc(*buffer, *size);
			if (temp == NULL)
			{
				perror("realloc");
				return (-1);
			}
			*buffer = temp;
		}
		(*buffer)[read_chars] = ch, read_chars++, total_chars++;
		if (ch == '\n')
		{
			break;
		}
	}
	if (read_chars == 0 && ch == EOF)
	{
		return (-1);
	}
	(*buffer)[read_chars] = '\0', total_chars += read_chars;
	return (total_chars);
}
