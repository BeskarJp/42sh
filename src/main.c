/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Main file of the project
*/

#include "shell.h"

/**
 * @brief Entry point of the Minishell application
 *
 * @param argc Number of command-line arguments
 * @param argv Array of arguments
 * @param env Array of environment variables
 * @return int. Classical for a main
 */
int main(int argc, char **argv, char **env)
{
    char *line = NULL;
    size_t len = 0;
    shell_t shell;

    if (argc != 1)
        return 1;
    (void)argc;
    (void)argv;
    initilize_struct(env, &shell);
    init_job_control(&shell);
    signal(SIGINT, handle_sigint);
    shell_loop(&shell, &len, &line);
    free_shell(&shell, line);
    return 0;
}
