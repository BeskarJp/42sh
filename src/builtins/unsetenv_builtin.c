/*
** EPITECH PROJECT, 2026
** Minishell 2
** File description:
** Execute unsetenv
*/

#include "shell.h"

/**
 * @brief Shifts the environment array after removing an entry
 *
 * @param env Modifiable environment array
 * @param deleted_line Deleted index
 */
void fill_the_void(char **env, int deleted_line)
{
    for (int i = deleted_line; env[i] != NULL; i++) {
        env[i] = env[i + 1];
    }
}

/**
 * @brief Removes an environment variable if it exists
 *
 * @param shell Shell structure
 * @param var_name Name of the variable to remove
 */
void delete_var(shell_t *shell, char *var_name)
{
    int len = my_strlen(var_name);

    if (shell->copy_env == NULL)
        return;
    for (int i = 0; shell->copy_env[i] != NULL; i++) {
        if (my_strncmp(shell->copy_env[i], var_name, len) == 0
            && shell->copy_env[i][len] == '=') {
            free(shell->copy_env[i]);
            fill_the_void(shell->copy_env, i);
            return;
        }
    }
}

/**
 * @brief Executes the unsetenv command to remove variables
 *
 * @param shell Shell structure
 */
void exec_unsetenv(shell_t *shell)
{
    if (shell->arg_col[1] == NULL) {
        write(2, "unsetenv: Add one argument after.\n", 35);
        return;
    }
    for (int i = 1; shell->arg_col[i] != NULL; i++) {
        delete_var(shell, shell->arg_col[i]);
    }
}
