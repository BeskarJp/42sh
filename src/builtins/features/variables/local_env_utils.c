/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** local_env
*/

#include "shell.h"

/**
 * @brief Adds a variable to local env
 *
 * @param shell Shell structure
 * @param line VAR=var_value
 */
void add_to_local_env(shell_t *shell, char *line, int state)
{
    env_t *new_node = malloc(sizeof(env_t));
    env_t *temp = shell->local_env;
    char **buff = NULL;

    if (!line || line[0] == '\n' || !new_node)
        return;
    buff = my_str_to_sep_array(line, "=");
    if (!buff || !buff[0] || !buff[1] || buff[2] != NULL)
        return;
    new_node->var = my_strdup(buff[0]);
    new_node->value = my_strdup(buff[1]);
    new_node->temp = state;
    new_node->next = NULL;
    if (!shell->local_env) {
        shell->local_env = new_node;
    } else {
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = new_node;
    }
}

/**
 * @brief Delete the node of local env
 *
 * @param shell Shell structure
 * @param local actual local env
 * @param old old local env
 */
static void delete_local_env_node(shell_t *shell, env_t *local, env_t *old)
{
    if (old)
        old->next = local->next;
    else
        shell->local_env = local->next;
    free(local->var);
    free(local->value);
    free(local);
}

/**
 * @brief Remove a variable of local env
 *
 * @param shell Shell structure
 */
void rm_local_env_var(shell_t *shell, char *name)
{
    env_t *local = shell->local_env;
    env_t *old = NULL;

    if (name == NULL)
        return;
    while (local) {
        if (my_strcmp(local->var, name) == 0) {
            delete_local_env_node(shell, local, old);
            return;
        }
        old = local;
        local = local->next;
    }
}

int var_declared(shell_t *shell, int n)
{
    char *first = shell->arg_col[n];
    int count = 0;
    int i = 0;

    while (first[i] != '\0') {
        if (first[i] == '=')
            count++;
        if ((first[i] >= 'a' && first[i] <= 'z') ||
            (first[i] >= 'A' && first[i] <= 'Z') ||
            (first[i] >= '0' && first[i] <= '9') ||
            (first[i] == '=')) {
            i++;
        } else {
            return 84;
        }
    }
    if (count != 1)
        return 84;
    return 0;
}

static void local_var_only(shell_t *shell)
{
    for (int i = 0; shell->arg_col[i] != NULL; i++)
        add_to_local_env(shell, shell->arg_col[i], 0);
}

void handle_local_var(shell_t *shell)
{
    int count[2] = {0, 0};

    for (int i = 0; shell->arg_col[i] != NULL; i++) {
        if (var_declared(shell, i) == 0)
            count[1]++;
        count[0]++;
    }
    if (count[0] == count[1]) {
        local_var_only(shell);
        return;
    }
    local_and_cmd(shell);
    return;
}

/**
 * @brief Displays the local env using my_printf
 *
 * @param shell Shell structure
 */
void display_local_env(shell_t *shell)
{
    env_t *temp = shell->local_env;

    while (temp != NULL) {
        my_printf("%s=%s\n", temp->var, temp->value);
        temp = temp->next;
    }
}
