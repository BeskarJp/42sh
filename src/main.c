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
    shell->aliases = NULL;
    shell->history = NULL;
}

/**
 * @brief Main loop of the shell for input and execution
 *
 * @param shell Shell structure
 * @param len Size of the allocated buffer for line
 * @param line Buffer for the command line input
 */
void shell_loop(shell_t *shell, size_t *len, char **line)
{
    while (shell->continue_shell) {
        print_shell_line(shell->copy_env);
        if (getline(line, len, stdin) == -1)
            break;
        if ((*line)[0] != '\0' && (*line)[my_strlen(*line) - 1] == '\n')
            (*line)[my_strlen(*line) - 1] = '\0';
        *line = check_history_feature(shell, *line);
        if (*line == NULL) {
            *len = 0;
            continue;
        }
        if ((*line)[0] != '\0') {
            add_to_history_linked_list(shell, *line);
            line_executor(shell, *line);
        }
    }
}

/**
 * @brief Free all allocated variables in the shell structure
 *
 * @param shell Shell structure to clean
 */
void free_shell(shell_t *shell, char *line)
{
    if (shell->aliases)
        free_aliases(shell->aliases);
    if (shell->history)
        free_history(shell->history);
    if (shell->copy_env)
        free_array(shell->copy_env);
    if (shell->oldpwd)
        free(shell->oldpwd);
    if (line)
        free(line);
}

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

    (void)argc;
    (void)argv;
    initilize_struct(env, &shell);
    shell_loop(&shell, &len, &line);
    free_shell(&shell, line);
    return 0;
}
