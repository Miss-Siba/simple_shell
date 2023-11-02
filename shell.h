#ifndef SHELL_H
#define SHELL_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_LINE_LENGTH 1024
#define MAX_ARGUMENTS 64

void list_files(void);
void execute_command(char *command, char *arguments[]);

#endif           
