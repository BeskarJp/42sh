/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Unaliases in shell
*/

#include "shell.h"

/**
 * @brief Deletes an alias node from the linked list
 *
 * @param shell Shell structure
 * @param aliases The aliases structure
 * @param old The old linked list or NULL if head
 */
void delete_alias_node(shell_t *shell, alias_t *aliases, alias_t *old)
{
    if (old)
        old->next = aliases->next;
    else
        shell->aliases = aliases->next;
    free(aliases->name);
    free(aliases->command);
    free(aliases);
}

/**
 * @brief Executes the unalias builtin command
 *
 * @param shell Shell structure
 */
void exec_unalias(shell_t *shell)
{
    alias_t *aliases = shell->aliases;
    alias_t *old = NULL;

    if (shell->arg_col[1] == NULL)
        return;
    while (aliases) {
        if (my_strcmp(aliases->name, shell->arg_col[1]) == 0) {
            delete_alias_node(shell, aliases, old);
            return;
        }
        old = aliases;
        aliases = aliases->next;
    }
}
