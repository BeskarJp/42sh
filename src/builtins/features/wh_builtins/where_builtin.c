/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Which in shell
*/

#include "shell.h"

/**
 * @brief Find a single command for the where builtin
 *
 * @param shell Shell structure
 * @param command Command name to find
 */
void process_where_command(shell_t *shell, char *command)
{
    alias_t *alias = find_alias_by_name(shell->aliases, command);
    char *pathway_env = find_word_in_env(shell->copy_env, "PATH");
    char *copy_pathway = NULL;

    if (alias != NULL)
        my_printf("%s is aliased to %s\n", command, alias->command);
    if (check_if_builtin(command))
        my_printf("%s is a shell built-in\n", command);
    if (pathway_env != NULL) {
        copy_pathway = my_strdup(pathway_env);
        if (copy_pathway != NULL) {
            print_when_where_match(copy_pathway, command);
            free(copy_pathway);
        }
    }
}

/**
 * @brief Executes the where builtin command
 *
 * @param shell Shell structure
 */
void exec_where(shell_t *shell)
{
    if (shell->arg_col[1] == NULL) {
        write(2, "where: Too few arguments.\n", 26);
        return;
    }
    for (int i = 1; shell->arg_col[i] != NULL; i++)
        process_where_command(shell, shell->arg_col[i]);
}
