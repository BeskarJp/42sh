/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Which in shell
*/

#include "shell.h"

/**
 * @brief Find a single command for the which builtin
 *
 * @param shell Shell structure
 * @param command Command name to find
 */
void process_which_command(shell_t *shell, char *command)
{
    alias_t *alias = find_alias_by_name(shell->aliases, command);
    char *pathway = NULL;

    if (alias != NULL) {
        my_printf("%s: aliased to %s\n", command, alias->command);
        return;
    }
    if (check_if_builtin(command)) {
        my_printf("%s: shell built-in command.\n", command);
        return;
    }
    pathway = find_command_path(command, shell->copy_env);
    if (pathway != NULL) {
        my_printf("%s\n", pathway);
        free(pathway);
    } else
        my_printf("%s: Command not found.\n", command);
}

/**
 * @brief Executes the which builtin command
 *
 * @param shell Shell structure
 */
void exec_which(shell_t *shell)
{
    if (shell->arg_col[1] == NULL) {
        write(2, "which: Too few arguments.\n", 26);
        return;
    }
    for (int i = 1; shell->arg_col[i] != NULL; i++)
        process_which_command(shell, shell->arg_col[i]);
}
