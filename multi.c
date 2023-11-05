#include "shell.h"

int read_and_parse_input(char *line, size_t len, char *args[])
{
ssize_t nread;
int i;

nread = getline(&line, &len, stdin);
if (nread == -1)
{
perror("getline");
return (0);
}
line[nread - 1] = '\0';
if (strcmp(line, "exit") == 0)
{
return (0);
}
else
{
i = 0;
args[i] = strtok(line, " \t");
while (args[i] != NULL)
{
i++;
args[i] = strtok(NULL, " \t");
}
args[i] = NULL;
return (1);
}
}


int main(void)
{
char *line;
size_t len = MAX_LINE;
char *args[MAX_LINE / 2 + 1];
int should_run = 1;
line = malloc(len);

if (line == NULL)
{
perror("malloc");
exit(1);
}

while (should_run)
{
printf(PROMPT);
fflush(stdout);
should_run = read_and_parse_input(line, len, args);
if (should_run)
{
pid_t pid = fork();
if (pid < 0)
{
perror("fork");
exit(1);
}
else if (pid == 0)
{
if (execvp(args[0], args) < 0)
{
perror(args[0]);
exit(1);
}
}
else
{
wait(NULL);
}
}
}

}

