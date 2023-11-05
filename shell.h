#ifndef SHELL_H
#define SHELL_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

#define MAX_LINE_LENGTH 1024
#define MAX_ARGUMENTS 64
#define MAX_LINE 80
#define MAX_TOKENS 32
#define PROMPT "dreamteam$"

extern char **environ;
int is_builtin(char *cmd);
int read_and_parse_input(char *line, size_t len, char *args[]);
char **tokenize_line(char *line, int *token_count);
void execute_command(char **argv);
void free_tokens(char **tokens, int token_count);
void print_env(void);
#endif 