#include "shell.h"

int is_valid_path(char *path)
{
	return access(path, F_OK) == 0;
}

void change_directory(char *path)
{
	char *old_pwd = getenv("PWD");
	char *new_pwd = realpath(path, NULL);
	
	if (chdir(path) == 0)
	{
		printf("Directory changed to %s\n", new_pwd);
		setenv("OLDPWD", old_pwd, 1);
		setenv("PWD", new_pwd, 1);
		free(new_pwd);
	}
	else
	{
		perror("cd");
	}
}

void cd_command(char **args)
{
	if (args[1] == NULL)
	{
		char *home = getenv("HOME");
		change_directory(home);
	}
	else if (args[2] != NULL)
	{
		fprintf(stderr, "cd: arguments are too many\n");
	}
	else if (strcmp(args[1], "-") == 0)
	{
		char *old_pwd = getenv("OLDPWD");
		if (old_pwd != NULL)
		{
			change_directory(old_pwd);
		}
		else
		{
			fprintf(stderr, "cd: OLDPWD not set\n");
		}
	}
	else
	{
		if (is_valid_path(args[1]))
		{
			change_directory(args[1]);
		}
		else
		{
			fprintf(stderr, "cd: no such file or directory: %s\n", args[1]);
		}
	}
}
int main(void)
{
	char *line = 0;
	char **args;
	int status = 1;
	int token_count;
	ssize_t nchars_read;
	size_t len = 0;

	do 
	{
		printf("dreamteam$ ");
		nchars_read = getline(&line, &len, stdin);

		if (nchars_read == -1)
		{
			perror("Unable to get line");
			return (-1);
		}
		line[strcspn(line, "\n")] = '\0';

		args = tokenize_line(line, &token_count);
		execute_command(args);
		free_tokens(args, token_count);
	}
	while (status);
free(line);

return (0);
}
