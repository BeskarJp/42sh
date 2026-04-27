/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Assembly all builtins
*/

#include "shell.h"

/**
 * @brief Executes a bonus builtin among EpiClaude if recognized
 *
 * @param shell Shell structure
 * @return int. 1 if builtin is handled, 0 if not
 */
int bonus_builtin_exec(shell_t *shell)
{
    if (my_strcmp(shell->arg_col[0], "help") == 0 ||
        my_strcmp(shell->arg_col[0], "./claude") == 0) {
        start_claude(shell);
        return 1;
    }
    if (my_strcmp(shell->arg_col[0], "cactus") == 0 ||
        my_strcmp(shell->arg_col[0], "travis") == 0){
        bonus_builtin_ascii_art_cactus();
        shell->exit_status = 0;
        return 1;
    }
    if (my_strcmp(shell->arg_col[0], "echo") == 0) {
        exec_echo(shell);
        return 1;
    }
    return 0;
}

/**
 * @brief Executes a builtin among alias/unalias/which/where if recognized
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
    if (my_strcmp(shell->arg_col[0], "which") == 0) {
        exec_which(shell);
        return 1;
    }
    if (my_strcmp(shell->arg_col[0], "where") == 0) {
        exec_where(shell);
        return 1;
    }
    if (bonus_builtin_exec(shell) == 1)
        return 1;
    return 0;
}

/**
 * @brief Executes job-control builtins if the command matches
 *
 * @param shell Shell structure
 * @return int. 1 if a job builtin was handled, 0 if not
 */
static int job_builtin_exec(shell_t *shell)
{
    if (my_strcmp(shell->arg_col[0], "jobs") == 0)
        return exec_jobs(shell);
    if (my_strcmp(shell->arg_col[0], "fg") == 0)
        return exec_fg(shell);
    if (my_strcmp(shell->arg_col[0], "bg") == 0)
        return exec_bg(shell);
    return 0;
}

/**
 * @brief Executes the builtins tied to shell state management
 *
 * @param shell Shell structure
 * @return int. 1 if a builtin was handled, 0 if not
 */
static int shell_state_builtin_exec(shell_t *shell)
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
    if (job_builtin_exec(shell) == 1)
        return 1;
    if (shell_state_builtin_exec(shell) == 1)
        return 1;
    if (builtin_exec_continue(shell) == 1)
        return 1;
    return 0;
}

/**
 * @brief Executes a builtin among set/unset/local/export
 *
 * @param shell Shell structure
 * @return int. 1 if builtin is handled, 0 if not
 */
int builtin_local(shell_t *shell)
{
    if (my_strcmp(shell->arg_col[0], "set") == 0) {
        set_builtin(shell);
        return 1;
    }
    if (my_strcmp(shell->arg_col[0], "unset") == 0) {
        unset_builtin(shell);
        return 1;
    }
    if (my_strcmp(shell->arg_col[0], "local") == 0) {
        display_local_env(shell);
        return 1;
    }
    if (my_strcmp(shell->arg_col[0], "export") == 0) {
        export_builtin(shell);
        return 1;
    }
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
        shell->exit_status = 0;
        return 1;
    }
    if (builtin_local(shell) == 1)
        return 1;
    if (builtin_exec(shell) == 1)
        return 1;
    return 0;
}
