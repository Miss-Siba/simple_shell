#include "shell.h"

/**
 * is_valid_path - checks if gevin path exists
 * @path: the path to check
 * Return: 1 if the path exists 0 if path does not exist
 */
int is_valid_path(char *path)
{
	return (access(path, F_OK) == 0);
}

/**
 * change_directory - changes current directory to given path
 * @path: the path to change to
 * Return: Nothing
 */
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

/**
 * cd_command - Implements the cd command of a shell
 * @args:  arguments of the cd command
 * Return: nothing
 */
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

