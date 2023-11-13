#include "shell.h"
/**
 * main - learning about the shell
 * @ac: argument counter
 * @av: argument vector
 *
 * Return: always return 0
 */
int main(int ac __attribute__((unused)), char **av __attribute__((unused))) {
	char *lineptr = NULL, *strt, *ret = "\n", **ext;
	size_t n = 0, i;
	ssize_t nread, mode = 1;
	pid_t fo;
	(void)ac;

	while (mode) {
		/* Display prompt */
		write(STDOUT_FILENO, "$ ", 2);
		/* Read user input */
		nread = getline(&lineptr, &n, stdin);

		if (nread == -1) {
			/* Handle end of file (Ctrl+D) */
			write(STDOUT_FILENO, "\n", 1);
			break;
		}
		/* Tokenize the input line into command and arguments */
		strt = strtok(lineptr, ret);
		/* Allocate memory for arguments array */
		ext = malloc(sizeof(char*) * (nread + 1));
		if (ext == NULL) {
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		i = 0;
		while (strt != NULL) {
			/* Allocate memory for each argument */
			ext[i] = malloc(strlen(strt) + 1);
			if (ext[i] == NULL) {
				perror("malloc");
				exit(EXIT_FAILURE);
			}
			/* Copy each argument */
			strcpy(ext[i], strt);
			i++;
			strt = strtok(NULL, ret);
		}
		/* Null-terminate the arguments array */
		ext[i] = NULL;
		/* Fork a child process */
		fo = fork();
		if (fo == -1) {
			perror("fork");
			exit(EXIT_FAILURE);
		} else if (fo == 0) {
			/* Child process: execute the command */
			if (execve(ext[0], ext, NULL) == -1) {
				perror(av[0]);
			}
		}
		/* Parent process: wait for the child to finish */
		wait(NULL);
		/* Free memory allocated for arguments */
		for (i = 0; ext[i] != NULL; i++) {
			free(ext[i]);
		}
		free(ext);
	}
	/* Free memory allocated for the input line */
	free(lineptr);
	return 0;
}

