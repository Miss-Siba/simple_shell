#include "shell.h"

#define MAX_INPUT_SIZE 1024
#define MAX_PATH_SIZE 4090
char prev_dir[MAX_PATH_SIZE];

void update_pwd(void)
{
	char current_dir[MAX_PATH_SIZE];
	getcwd(current_dir, sizeof(current_dir));
	setenv("PWD", current_dir, 1);
}

void update_prompt(void)
{
	printf("\n%sDreamteam$ ", getenv("PWD"));
	fflush(stdout);
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
				else
				{
				update_pwd();
				getcwd(prev_dir, sizeof(prev_dir));
				}
		}
	}
	else
	{
		if (args[1][0] == '~')
		{
			char expanded_path[MAX_PATH_SIZE];
			snprintf(expanded_path, sizeof(expanded_path), "%s%s", getenv("HOME"), args[1] + 1);
			if (chdir(expanded_path) != 0)
			{
				perror("cd");
			}
				else
				{
					update_pwd();
					getcwd(prev_dir, sizeof(prev_dir));
				}

			}
			else if (strcmp(args[1], "-") == 0)
			{
				if (prev_dir[0] != '\0')
				{
					if (chdir(prev_dir) != 0)
					{
						perror("cd");
					}
					else
					{
						update_pwd();
						getcwd(prev_dir, sizeof(prev_dir));
					}
				}
				else
				{
					fprintf(stderr, "cd: no previous directory\n");
				}
			}
			else
			{	if (chdir(args[1]) != 0)
				{
					perror("cd");
				}
				else
				{
					update_pwd();
					getcwd(prev_dir, sizeof(prev_dir));
				}
			}
		}
	update_prompt();
}

