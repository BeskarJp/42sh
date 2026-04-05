/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Error handling for minishell
*/

#include "shell.h"

/**
 * @brief Displays an error by an execution error code
 *
 * @param path Path of the command failed
 */
void check_execve_output_error(char *path)
{
    if (errno == EACCES)
        my_printf("%s: Permission denied.\n", path);
    if (errno == ENOEXEC)
        my_printf("%s: Exec format error. Binary file not executable.\n", path);
}

/**
 * @brief Displays a message if a process ended with a signal
 *
 * @param status Status code returned by waitpid()
 */
void check_strsignal(int status)
{
    char *message_output = NULL;
    int nb_signal = 0;

    if (WIFSIGNALED(status)) {
        nb_signal = WTERMSIG(status);
        message_output = strsignal(nb_signal);
        write(2, message_output, strlen(message_output));
        if (WCOREDUMP(status))
            write(2, " (core dumped)", 14);
        write(2, "\n", 1);
    }
}
