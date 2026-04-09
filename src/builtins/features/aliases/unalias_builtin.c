/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Unaliases in shell
*/

#include "shell.h"

void delete_alias_node(shell_t *shell, alias_t *aliases, alias_t *temp)
{
    if (temp)
        temp->next = aliases->next;
    else
        shell->aliases = aliases->next;
    free(aliases->name);
    free(aliases->command);
    free(aliases);
}

void exec_unalias(shell_t *shell)
{
    alias_t *aliases = shell->aliases;
    alias_t *temp = NULL;

    if (shell->arg_col[1] == NULL)
        return;
    while (aliases) {
        if (my_strcmp(aliases->name, shell->arg_col[1]) == 0) {
            delete_alias_node(shell, aliases, temp);
            return;
        }
        temp = aliases;
        aliases = aliases->next;
    }
}
