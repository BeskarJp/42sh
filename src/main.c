/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Main file of the project
*/

#include "shell.h"

/**
 * @brief Initializes Shell structure with the environment
 *
 * @param env Array which represente environment variables
 * @param shell Shell structure to initialize
 */
void initilize_struct(char **env, shell_t *shell)
{
    shell->copy_env = copy_environment(env);
    shell->oldpwd = NULL;
    shell->continue_shell = 1;
}

/**
 * @brief Entry point of the Minishell application
 *
 * @param argc Number of command-line arguments
 * @param argv Array of arguments
 * @param env Array of environment variables
 * @return int
 */
int main(int argc, char **argv, char **env)
{
    char *line = NULL;
    size_t len = 0;
    shell_t shell;

    (void)argc;
    (void)argv;
    initilize_struct(env, &shell);
    while (shell.continue_shell) {
        print_shell_line(shell.copy_env);
        if (getline(&line, &len, stdin) == -1)
            break;
        line_executor(&shell, line);
    }
    free_cd(&shell);
    free_array(shell.copy_env);
    free(line);
    return 0;
}
