#include "shell.h"

char prev_dir[100];

void update_pwd(void)
{
	char current_dir[100];
	getcwd(current_dir, sizeof(current_dir));
	setenv("PWD", current_dir, 1);
}

void handle_cd(char *args[])
{
	char *home_dir;

	if (args[1] == NULL)
	{
		home_dir = getenv("HOME");
		if (home_dir == NULL)
		{

			fprintf(stderr, "cd: $HOME is not set\n");
		}
		else
		{
			if (chdir(home_dir) != 0)
			{
				perror("cd");
			}
			update_pwd();
			getcwd(prev_dir, sizeof(prev_dir));
		}
	}
	else
	{
		if (strcmp(args[1], "-") ==0)
		{
			if (chdir(prev_dir) != 0)
			{
				perror("cd");
			}
			else
			{
				if (chdir(args[1]) != 0)
				{
					perror("cd");

				}
				update_pwd();
				getcwd(prev_dir, sizeof(prev_dir));
			}
		}
	}
}

int main(void)
{
	char *args[20];
	getcwd(prev_dir, sizeof(prev_dir));

	if (args[0] != NULL)
	{
		if (strcmp(args[0], "cd") == 0)
		{
			handle_cd(args);
		}
	}
	return (0);
}
