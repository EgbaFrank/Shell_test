#include "shell.h"

/**
 * execute_command - Executes a command given an array of arguments.
 * @args: Array of arguments, with the last element being NULL.
 */
void execute_command(char *args[])
{
    pid_t child_pid = fork();

    if (child_pid == -1)
{
        perror("fork");
        exit(EXIT_FAILURE);
    } 
else if (child_pid == 0)
{
        if (execve(args[0], args, NULL) == -1)
{
            perror("Command not found");
            exit(EXIT_FAILURE);
        }
    }
else
{
        if (wait(NULL) == -1)
{
            perror("wait");
            exit(EXIT_FAILURE);
        }
    }
}

/**
 * main - Simple shell that takes and executes commands.
 *
 * Return: Always 0.
 */
int main(void)
{
    char *lineptr = NULL;
    size_t n = 0;
    ssize_t nread;

    while (write(STDOUT_FILENO, "$ ", 2) && (nread = getline(&lineptr, &n, stdin)) != -1)
{
        if (nread > 1)
{
            lineptr[nread - 1] = '\0';

            char *args[MAX_ARGS];
            size_t arg_count = 0;
            char *token = strtok(lineptr, " ");

            while (token != NULL && arg_count < MAX_ARGS - 1)
{
                args[arg_count++] = token;
                token = strtok(NULL, " ");
            }

            args[arg_count] = NULL;
            execute_command(args);
        }
    }

    free(lineptr);
    return 0;
}
