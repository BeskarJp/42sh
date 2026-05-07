/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** set builtin
*/

#include "shell.h"

int set_builtin(shell_t *shell)
{
    char **temp = NULL;
    int j = 0;

    if (shell->arg_col[1] == NULL) {
        write(2, "set: Not enough arguments.\n", 27);
        return 0;
    }
    while (shell->arg_col[j] != NULL) {
        j++;
    }
    temp = malloc(sizeof(char *) * j);
    if (!temp)
        return 84;
    for (int i = 0; shell->arg_col[i] != NULL; i++)
        temp[i] = my_strdup(shell->arg_col[i + 1]);
    shell->arg_col = temp;
    local_var_only(shell);
    free_array(temp);
    return 0;
}

int unset_builtin(shell_t *shell)
{
    if (shell->arg_col[1] == NULL) {
        write(2, "unset: Not enough arguments.\n", 29);
        return 0;
    }
    for (int i = 1; shell->arg_col[i] != NULL; i++)
        rm_local_env_var(shell, shell->arg_col[i]);
    return 0;
}
