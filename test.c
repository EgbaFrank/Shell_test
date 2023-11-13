#include "shell.h"

/**
 * main - A simple UNIX command line interpreter
 *
 * Return: 0 if succuessful, -1 otherwise
 */
int main(void)
{
	char *lineptr = NULL;
	size_t n = 0;
	ssize_t nread, mode = 1;

	while (mode)
	{
		mode = isatty(STDIN_FILENO);

		if (mode == 1)
		{
			write(STDOUT_FILENO, "$ ", 2);
		}
		nread = getline(&lineptr, &n, stdin);

		if (nread == -1)
		{
			if (feof(stdin))
			{
				write(STDOUT_FILENO, "\n", 1);
			}
			else
			{
				perror("getline");
			}
			break;
		}
		lineptr[nread - 1] = '\0';

		if (execlp(lineptr, lineptr, (char *)NULL) == -1)
		{
			write(STDOUT_FILENO, "Command not found\n", 18);
		}
	}
	free(lineptr);
	return (0}
