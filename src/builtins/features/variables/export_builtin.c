/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** export_builtin
*/

#include "shell.h"

/**
 * @brief Finds a var by its name in the linked list
 *
 * @param local The local_env structure
 * @param name Name of the variable to find
 * @return env_t. The local_env struct if found or NULL
 */
env_t *find_var_by_name(env_t *local, char *name)
{
    env_t *temp = local;
    int len = 0;

    while (name[len] != '\0' && name[len] != '=')
        len++;
    while (temp) {
        if (my_strlen(temp->var) == len &&
            my_strncmp(temp->var, name, len) == 0)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

static void no_arg_export(shell_t *shell)
{
    if (shell->copy_env == NULL)
        return;
    for (int i = 0; shell->copy_env[i] != NULL; i++)
        my_printf("declare -x %s\n", shell->copy_env[i]);
}

void export_helper(shell_t *shell, env_t *var)
{
    int len_name = my_strlen(var->var);
    char *line = add_line_in_env(var->var, var->value);

    if (shell->copy_env == NULL) {
        make_env_bigger(shell, line);
        return;
    }
    for (int i = 0; shell->copy_env[i] != NULL; i++) {
        if (my_strncmp(shell->copy_env[i], var->var, len_name) == 0
            && shell->copy_env[i][len_name] == '=') {
            free(shell->copy_env[i]);
            shell->copy_env[i] = line;
            return;
        }
    }
    make_env_bigger(shell, line);
}

/**
 * @brief For loop for export command
 *
 * @param shell Shell structure
 * @param arg line ton export
 */
void process_export_arg(shell_t *shell, char *arg)
{
    env_t *temp = find_var_by_name(shell->local_env, arg);
    char *var_name = NULL;

    if (temp == NULL) {
        add_to_local_env(shell, arg, 0);
        temp = find_var_by_name(shell->local_env, arg);
    }
    if (temp == NULL)
        return;
    var_name = my_strdup(temp->var);
    export_helper(shell, temp);
    if (var_name) {
        rm_local_env_var(shell, var_name);
        free(var_name);
    }
}

/**
 * @brief Export (and can define at same time) local variable
 *        to env variable
 *
 * @param shell Shell structure
 */
void export_builtin(shell_t *shell)
{
    if (!shell || !shell->arg_col)
        return;
    if (shell->arg_col[1] == NULL) {
        no_arg_export(shell);
        return;
    }
    for (int i = 1; shell->arg_col[i] != NULL; i++) {
        process_export_arg(shell, shell->arg_col[i]);
    }
}
