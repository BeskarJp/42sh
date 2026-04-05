/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Utils for redirection in minishell
*/

#include "shell.h"

/**
 * @brief Displays a '>' prompt
 */
void print_line_left_double_redirection(void)
{
    if (isatty(0))
        my_putchar('>');
}

/**
 * @brief Handles the '<<' redirection by writing into a pipe
 *
 * @param delimiter word to compare
 */
void left_double_redirection(char *delimiter)
{
    char *line = NULL;
    int pipefd[2];
    size_t len = 0;

    if (pipe(pipefd) == -1)
        return;
    while (1) {
        print_line_left_double_redirection();
        if (getline(&line, &len, stdin) == -1)
            break;
        if (my_strncmp(line, delimiter, my_strlen(delimiter)) == 0 &&
            line[my_strlen(delimiter)] == '\n')
            break;
        write(pipefd[1], line, my_strlen(line));
    }
    dup2(pipefd[0], 0);
    close(pipefd[0]);
    close(pipefd[1]);
    if (line)
        free(line);
}
