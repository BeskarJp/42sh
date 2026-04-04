/*
** EPITECH PROJECT, 2026
** Minishell 2
** File description:
** Builtin of env
*/

#include "shell.h"

/**
 * @brief Prints all environment variables
 *
 * @param shell Shell structure
 */
void display_env(shell_t *shell)
{
    if (shell->copy_env == NULL)
        return;
    for (int i = 0; shell->copy_env[i] != NULL; i++) {
        my_putstr(shell->copy_env[i]);
        my_putchar('\n');
    }
}
