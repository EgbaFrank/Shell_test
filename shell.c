#include "shell.h"

/**
 * main - A unix interpreter
 * @ac: argument counter
 * @av: argument vector
 *
 * Return: 0 if succuessful, -1 otherwise
 */

int main(int ac __attribute__((unused)), char **av __attribute__((unused)))
{
	char *lineptr = NULL;
	size_t n = 0;
	ssize_t nread, mode = 1;

	while (mode)
	{
		mode = isatty(STDIN_FILENO);

		if (mode == 1)
		{
			write(STDOUT_FILENO, "$ ", 3);
			/*print prompt*/
		}

		nread = getline(&lineptr, &n, stdin);
		if (nread == -1)
			break;
		/*get user's input*/

		lineptr[nread - 1] = '\0';
		/*remove newline character*/
		printf("%s\n", lineptr);
		/*differentiate commands, options and arguments*/
		/*create child proccess*/
		/*execute command*/
	}
	free(lineptr);

	return 0;
}
