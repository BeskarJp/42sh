/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** cwd_builtin
*/

#include "shell.h"

void cwd_builtin(shell_t *shell)
{
    char *path = find_word_in_env(shell->copy_env, "PWD");

    if (!path)
        return;
    my_printf("%s\n", path);
}
