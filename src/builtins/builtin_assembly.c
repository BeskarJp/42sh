/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Assembly all builtins
*/

#include "shell.h"

/**
 * @brief Executes a builtin among alias/unalias if recognized
 *
 * @param shell Shell structure
 * @return int. 1 if builtin is handled, 0 if not
 */
int builtin_exec_continue(shell_t *shell)
{
    if (my_strcmp(shell->arg_col[0], "alias") == 0) {
        exec_alias(shell);
        return 1;
    }
    if (my_strcmp(shell->arg_col[0], "unalias") == 0) {
        exec_unalias(shell);
        return 1;
    }
    return 0;
}

/**
 * @brief Executes a builtin among setenv/unsetenv/cd/history if recognized
 *
 * @param shell Shell structure
 * @return int. 1 if builtin is handled, 0 if not
 */
int builtin_exec(shell_t *shell)
{
    if (my_strcmp(shell->arg_col[0], "setenv") == 0) {
        exec_setenv(shell);
        return 1;
    }
    if (my_strcmp(shell->arg_col[0], "unsetenv") == 0) {
        exec_unsetenv(shell);
        return 1;
    }
    if (my_strcmp(shell->arg_col[0], "cd") == 0) {
        exec_cd(shell);
        return 1;
    }
    if (my_strcmp(shell->arg_col[0], "history") == 0) {
        display_history(shell);
        return 1;
    }
    if (builtin_exec_continue(shell) == 1)
        return 1;
    return 0;
}

/**
 * @brief Handles all builtin commands recognized by the shell
 *
 * @param shell Shell structure
 * @return int. 1 if builtin is handled, 0 if not
 */
int builtin_assembly(shell_t *shell)
{
    if (my_strcmp(shell->arg_col[0], "exit") == 0) {
        shell->continue_shell = 0;
        return 1;
    }
    if (my_strcmp(shell->arg_col[0], "env") == 0) {
        display_env(shell);
        return 1;
    }
    if (builtin_exec(shell) == 1)
        return 1;
    return 0;
}
