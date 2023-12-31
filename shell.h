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
#define MAX_INPUT_SIZE 1024
#define MAX_ARGUMENTS 64
#define MAX_LINE 80
#define MAX_TOKENS 32
#define MAX_ALIASES 100
#define PROMPT "dreamteam$"
#define MAX_VARS 100

/**
 * struct ShellState - Represents the state of the shell, including aliases.
 * @structaliases: array of structs that store the name and value of each alias
 * @count: The count of aliases stored in the state.
 * Return: Nothing
 */
typedef struct ShellState
{

	int count;
	struct
	{
		char *name;
		char *value;
	}
	aliases[MAX_ALIASES];
}
ShellState;

/**
 * struct variable - Represents a variable with a name and a value.
 * @name: The name of the variable.
 * @value: The value of the variable.
 * Return: Nothing
 */
typedef struct variable
{

	char *name;
	char *value;
}
variable;

extern char **environ;
int is_builtin(char *cmd);
void initialize_shell_state(ShellState *state);
int handle_execution_result(int status);
int read_and_parse_input(char *line, size_t len, char *args[]);
char **tokenize_line(char *line, int *token_count);
void free_tokens(char **tokens, int token_count);
void print_env(void);
void handle_cd(char *args[]);
void remove_alias(ShellState *state, char *alias_name);
void update_pwd(void);
void process_command(char *line, ShellState *state);
void update_prompt(void);
char *replace_var(char *command);
void parse_and_execute(char *input);
void list_aliases(ShellState *state);
void add_alias(ShellState *state, char *alias_name, char *alias_value);
ssize_t _getline(char **buffer, size_t *size, FILE *stream);
char **parse_line(char *line);
void execute_command(char **argv);
int is_comment(char *line);
void execute_single_command(char *file);
char *read_line(void);
int handle_builtin(char **tokens, int token_count);
int setenv_unsetenv(void);
int processFile(const char *filename);
int handle_exit(char **args, int *exit_flag);
void execute_parent(pid_t pid);
void execute_child(char **argv);

#endif
