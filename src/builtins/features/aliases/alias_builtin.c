/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Aliases in shell
*/

#include "shell.h"

void display_aliases(shell_t *shell)
{
    alias_t *temp = shell->aliases;

    if (shell->arg_col[1] == NULL) {
        while (temp) {
            my_printf("%s\t%s\n", temp->name, temp->command);
            temp = temp->next;
        }
    } else {
        temp = find_alias_by_name(shell->aliases, shell->arg_col[1]);
        if (temp)
            my_printf("%s\n", temp->command);
    }
}
