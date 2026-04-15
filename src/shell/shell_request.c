/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Handle shell_line
*/

#include "shell.h"
#include <stdbool.h>

/**
 * @brief Executes an external command in a child process
 *
 * @param shell Shell structure
 */
void execute_command(shell_t *shell)
{
    char *path = find_command_path(shell->arg_col[0], shell->copy_env);
    pid_t pid;
    int status;

    if (path == NULL) {
        write(2, shell->arg_col[0], my_strlen(shell->arg_col[0]));
        write(2, ": Command not found.\n", 21);
        return;
    }
    pid = fork();
    if (pid == 0) {
        if (execve(path, shell->arg_col, shell->copy_env) == -1) {
            check_execve_output_error(path);
            exit(1);
        }
    } else if (pid > 0) {
        waitpid(pid, &status, 0);
        check_strsignal(status);
    }
    free(path);
}

/**
 * @brief Parses and executes a command line entered by the user
 *
 * @param shell Shell structure
 * @param line Command line to process
 */
void line_executor(shell_t *shell, char *line)
{
    token_tree_t *tree = NULL;
    bool is_user = false;

    if (!line || line[0] == '\0')
        return;
    if (check_user(line, shell) == 1)
        is_user = true;
    if (is_user == false) {
        tree = parse_line(line);
        if (tree != NULL) {
            run_tree(shell, tree);
            free_tree(tree);
        }
    }
}
