/*
** EPITECH PROJECT, 2026
** G-PSU-200-LIL-2-1-42sh-1
** File description:
** temp_var
*/

#include "shell.h"

static void apply_temp_var_loop(shell_t *shell, char **saved_values,
    char **var_names, int i)
{
    env_t *temp = NULL;
    int len_name = 0;

    add_to_local_env(shell, shell->arg_col[i], 1);
    temp = find_var_by_name(shell->local_env, shell->arg_col[i]);
    if (!temp)
        return;
    var_names[i] = my_strdup(temp->var);
    len_name = my_strlen(temp->var);
    saved_values[i] = NULL;
    for (int k = 0; shell->copy_env && shell->copy_env[k] != NULL; k++) {
        if (my_strncmp(shell->copy_env[k], temp->var, len_name) == 0
            && shell->copy_env[k][len_name] == '=') {
            saved_values[i] = my_strdup(shell->copy_env[k]);
            break;
        }
    }
    export_helper(shell, temp);
}

int apply_temp_variables(shell_t *shell, char **saved_values,
    char **var_names, int var_count)
{
    int i = 0;

    for (i = 0; i < var_count; i++) {
        apply_temp_var_loop(shell, saved_values, var_names, i);
    }
    var_names[var_count] = NULL;
    saved_values[var_count] = NULL;
    return i;
}

void exec_with_new_args(shell_t *shell, int i)
{
    int count = 0;
    char **args = NULL;
    char **arg_col = NULL;

    while (shell->arg_col[i + count] != NULL)
        count++;
    if (count == 0)
        return;
    args = malloc(sizeof(char *) * (count + 1));
    if (!args)
        return;
    for (int k = 0; k < count; k++)
        args[k] = shell->arg_col[i + k];
    args[count] = NULL;
    arg_col = shell->arg_col;
    shell->arg_col = args;
    execute_command(shell);
    shell->arg_col = arg_col;
    free(args);
}

static void change_env_var(shell_t *shell, char **saved_values, int n, int k)
{
    if (saved_values[n]) {
        shell->copy_env[k] = saved_values[n];
    } else {
        for (int m = k; shell->copy_env[m] != NULL; m++)
            shell->copy_env[m] = shell->copy_env[m + 1];
    }
}

static void restore_env_loop(shell_t *shell, char **saved_values,
    char **var_names, int n)
{
    int len_name = my_strlen(var_names[n]);

    for (int k = 0; shell->copy_env[k] != NULL; k++) {
        if (my_strncmp(shell->copy_env[k], var_names[n], len_name) == 0
            && shell->copy_env[k][len_name] == '=') {
            free(shell->copy_env[k]);
            change_env_var(shell, saved_values, n, k);
            break;
        }
    }
}

void restore_env(shell_t *shell, char **saved_values,
    char **var_names, int var_count)
{
    for (int n = 0; n < var_count; n++) {
        if (shell->copy_env) {
            restore_env_loop(shell, saved_values, var_names, n);
        }
        rm_local_env_var(shell, var_names[n]);
        free(var_names[n]);
    }
}

void local_and_cmd(shell_t *shell)
{
    int i = 0;
    char **saved_values = NULL;
    char **var_names = NULL;
    int var_count = 0;

    while (shell->arg_col[var_count] != NULL &&
        var_declared(shell, var_count) == 0)
        var_count++;
    saved_values = malloc(sizeof(char *) * (var_count + 1));
    var_names = malloc(sizeof(char *) * (var_count + 1));
    if (!saved_values || !var_names)
        return;
    i = apply_temp_variables(shell, saved_values, var_names, var_count);
    exec_with_new_args(shell, i);
    restore_env(shell, saved_values, var_names, var_count);
    free(saved_values);
    free(var_names);
}
