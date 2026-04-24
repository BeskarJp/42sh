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
    shell->local_env = NULL;
    shell->inhibitors = NULL;
    shell->jobs = NULL;
    shell->next_job_id = 1;
    shell->shell_pgid = 0;
    shell->shell_terminal = STDIN_FILENO;
    shell->interactive = 0;
    shell->exit_status = 0;
}

/**
 * @brief Displays the prompt, refreshes jobs and reads one input line
 *
 * @param shell Shell structure
 * @param len Size of the allocated buffer for line
 * @param line Buffer for the command line input
 * @return int. -1 when end of input is reached, 0 otherwise
 */
static int read_user_line(shell_t *shell, size_t *len, char **line)
{
    refresh_jobs(shell);
    notify_done_jobs(shell);
    signal(SIGINT, handle_sigint);
    print_shell_line(shell->copy_env);
    if (getline(line, len, stdin) == -1)
        return -1;
    return 0;
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
        if (read_user_line(shell, len, line) == -1) {
            my_printf("\n");
            break;
        }
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
    if (shell->history)
        free_history(shell->history);
    if (shell->jobs)
        free_jobs(shell->jobs);
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
    init_job_control(&shell);
    signal(SIGINT, handle_sigint);
    shell_loop(&shell, &len, &line);
    free_shell(&shell, line);
    return 0;
}
