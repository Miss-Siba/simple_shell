#include "shell.h"
#include <argp.h>

struct arguments
{
        char* com;
        char** files;
        int file_count;

};

static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
        struct arguments *args = (struct arguments*)state->input;

        switch (key)
        {
                case ARGP_KEY_ARG:
                        if (args->file_count < 20)
                        {
                                args->files[args->file_count++] = arg;
                        }
                        else
                        {
                                perror("maximum files reached\n")
                                return ARGP_ERR_UNKNOWN;
                        }
                        break;
                case ARGP_KEY_END:
                        if (args->file_count == 0)
                        {
                                perror("no files or directories\n");
                                return ARGP_ERR_UNKNOWN;
                        }
                        break;
                default:
                        return ARGP_ERR_UNKNOWN;
        }
        return (0);
}
static struct argp_option options[] =
{
    {0}
};

static struct argp argp = {options, parse_opt, "[FILES...]", 0};

int main(int argc, char *argv[])
{
        int i;
        struct arguments args;
        args.command = NULL;
        args.file_count = 0;
        args.files = malloc(20 * sizeof(char*));

        argp_parse(&argp, cargc, argv, 0, 0, &args);

        if(args.command == NULL)
        {
                perror("Command not found\n");
                return (1);
        }
        if (strcmp(args.command, "touch") == 0)
        {
                 for (i = 0; i < args.num_files; i++)
                 {
                         FILE* file = fopen(args.files[i], "w");

                         if (file != NULL)
                         {
                                fclose(file);
                         }
        else if (strcmp(args.command, "mv") == 0)
        {
                if (args.file_count < 2)
                {
                        perror("mv requires at least two arguments\n");
                }
        const char* source = args.files[0];
        const char* destination = args.files[1];

        if (rename(source, destination) == 0) {
            printf("Moved: %s -> %s\n", source, destination);

        else if (strcmp(args.command, "cp") == 0)
        {
                if (args.file_count < 3)
                {
                        perror("cp requires at least three arguments\n");
                }
        else
        {
                perror("Command not found\n");
                return (1);
        }
        free(args.files);
        return (0);
        }

