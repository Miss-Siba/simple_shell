#include "shell.h"

int is_builtin(char *cmd)
{
	return (strcmp(cmd, "exit") == 0);
}

void execute_command(char **argv)
{


        pid_t pid = fork();

        if (pid == -1)
        {
                perror("Fork failed");
                return;
        }
        else if (pid == 0)
        {
                execv(argv[0], argv);
                perror("Execv Failed");
                exit(1);
        }
        else
        {
                int status;
                waitpid(pid, &status, 0);
        }
}
