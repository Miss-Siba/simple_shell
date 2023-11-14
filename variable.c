#include "shell.h"

variable vars[MAX_VARS];
int var_count = 0;

char *find_var(char *name)
{
	for (int i = 0; i < var_count; i++)
	{
		if (strcmp(vars[i].name, name) == 0)
		{
			return vars[i].value;
		}
	}
	return (NULL);
}

void set_var(char *name, char *value)
{
	char *old_value = find_var(name);

	if (old_value != NULL)
	{
		free(old_value);
		vars[var_count].value = strdup(value);
	}
	else
	{
		vars[var_count].name = strdup(name);
		vars[var_count].value = strdup(value);
		var_count++;
	}
}

char *replace_var(char *str)
{
	int status;

	if (str[0] == '$')
	{
		char *name = str + 1;

		if (strcmp(name, "?") == 0)
		{
			char *value = malloc(10);

			sprintf(value, "%d", WEXITSTATUS(status));
			return value;
		}
		else if (strcmp(name, "$") == 0)
		{
			char *value = malloc(10);
			
			sprintf(value, "%d", getpid());
			return (value);
		}
		else
		{
			char *value = find_var(name);
			
			if (value != NULL)
			{
			return strdup(value);
			}
	}
	return strdup(str);
}

int main(void)
{
	set_var("First name", "Tshilidzi");
	set_var("age", "24");
	set_var("greetings", "Hello, $First name, You are $age years old.");

	char *greetings = replace_var(find_var("greetings"));

	printf("%s\n", greetings);
	free(greetings);

	pid_t pid = fork();
	if (pid == 0)
	{
		execlp("ls", "ls", "-l", NULL);
		exit(1);
	}
	else if (pid > 0)
	{
		wait(&status);
	}
	else
	{
		perror("fork");
		exit(1);
	}

	char *status_str = replace_var("$?");
	
	printf("The exit status of last command was %s\n", status_str);
	free(status_str);

	char *pid_str = replace_var("$$");

	printf("The process ID of current program is %s\n", pid_str);
	free(pid_str);
	return (0);
}
}
