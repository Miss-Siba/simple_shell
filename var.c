#include "shell.h"
#define MAX_LINE_LENGTH 1024

char *replace_var(char *command)
{
	char *result = malloc(strlen(command) + 1);
	int result_index = 0;
	int command_index = 0;
	
	if  (result == NULL)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	result[0] = '\0';
	
	while (command[command_index] != '\0')
	{
		if (command[command_index] == '$' && command[command_index + 1] == '?')
		{
			int simulated_exit_status = 98; 
			char exit_status_str[10];
			sprintf(exit_status_str, "%d", simulated_exit_status);
			strcat(result, exit_status_str);
			command_index += 2;
		}
		else if (command[command_index] == '$'&& command[command_index + 1] == '$')
		{
			pid_t pid = getpid();
			char pid_str[10];
			sprintf(pid_str, "%d", pid);
			strcat(result, pid_str);
			result_index += strlen(pid_str);
			command_index += 2;
		}
		else
		{
			result[result_index] = command[command_index];
			result_index++;
			command_index++;
		}
	}

	return (result);
}

int main(void)
{
	char *input = NULL;
	size_t len = 0;
	ssize_t nchars;
	char *result;

	while (1)
	{
		printf("Dreamteam$ ");
		nchars = getline(&input, &len, stdin);

		if (nchars == -1)
		{
			break;
		}
		input[strcspn(input, "\n")] = '\0';

		result = replace_var(input);

		printf("Command with special variables: %s\n", result);

		free(result);
	}
	free(input);
	return (0);
}
