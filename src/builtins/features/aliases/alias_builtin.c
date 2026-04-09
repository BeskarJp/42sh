/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Aliases in shell
*/

#include "shell.h"

void display_aliases(shell_t *shell)
{
    alias_t *aliases = shell->aliases;

    if (shell->arg_col[1] == NULL) {
        while (aliases) {
            my_printf("%s\t%s\n", aliases->name, aliases->command);
            aliases = aliases->next;
        }
    } else {
        aliases = find_alias_by_name(shell->aliases, shell->arg_col[1]);
        if (aliases)
            my_printf("%s\n", aliases->command);
    }
}

char *get_full_command(char **args)
{
    char *full_command = NULL;
    int len = 0;

    for (int i = 2; args[i]; i++)
        len += my_strlen(args[i]) + 1;
    full_command = malloc(sizeof(char) * (len + 1));
    if (!full_command)
        return NULL;
    full_command[0] = '\0';
    for (int i = 2; args[i]; i++) {
        my_strcat(full_command, args[i]);
        if (args[i + 1])
            my_strcat(full_command, " ");
    }
    return full_command;
}

void exec_alias(shell_t *shell)
{
    char *command = NULL;

    if (!shell->arg_col[1] || !shell->arg_col[2]) {
        display_aliases(shell);
        return;
    }
    command = get_full_command(shell->arg_col);
    if (command) {
        add_alias(shell, shell->arg_col[1], command);
        free(command);
    }
}
