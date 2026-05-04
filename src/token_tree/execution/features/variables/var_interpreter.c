/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Interpret variables before executing command
*/

#include "shell.h"

static char *to_interpret(char *str)
{
    char *buff = NULL;
    int len = 0;

    if (!str || str[0] != '$')
        return NULL;
    len = strlen(str);
    buff = malloc(sizeof(char) * len);
    if (!buff)
        return NULL;
    for (int i = 1; i < len; i++)
        buff[i - 1] = str[i];
    buff[len - 1] = '\0';
    return buff;
}

static env_t *find_corr_local(shell_t *shell, token_tree_t *tree, int *ind)
{
    env_t *correlation = NULL;
    char *temp = to_interpret(tree->args[*ind]);

    if (temp == NULL)
        return NULL;
    correlation = find_var_by_name(shell->local_env, temp);
    free(temp);
    return correlation;
}

static char *find_corr_env(shell_t *shell, token_tree_t *tree, int *ind)
{
    char *in_env = NULL;
    char *temp = to_interpret(tree->args[*ind]);

    if (temp == NULL)
        return NULL;
    in_env = find_word_in_env(shell->copy_env, temp);
    free(temp);
    return in_env;
}

static int arr_len(char **array)
{
    int len = 0;

    while (array[len])
        len++;
    return len;
}

/**
 * @brief Recursively checks and applies var to command arguments
 *
 * @param shell Shell structure
 * @param tree Token tree structure
 * @param rec_count Pointer the counter (recursive)
 */
void recursive_var_interpreter(shell_t *shell, token_tree_t *tree,
    int *rec_count)
{
    env_t *correlation = NULL;
    char *in_env = NULL;

    if (tree == NULL || tree->args == NULL ||
        *rec_count >= arr_len(tree->args))
        return;
    correlation = find_corr_local(shell, tree, rec_count);
    if (correlation != NULL)
        tree->args[*rec_count] = my_strdup(correlation->value);
    if (correlation == NULL) {
        in_env = find_corr_env(shell, tree, rec_count);
        if (in_env != NULL)
            tree->args[*rec_count] = my_strdup(in_env);
    }
    (*rec_count)++;
    recursive_var_interpreter(shell, tree, rec_count);
}

/**
 * @brief Checks and applies variables to a command in the token tree
 *
 * @param shell Shell structure with variables
 * @param tree Token tree with the command to check
 */
void var_interpreter(shell_t *shell, token_tree_t *tree)
{
    int rec_count = 0;

    if (shell == NULL || tree == NULL)
        return;
    recursive_var_interpreter(shell, tree, &rec_count);
}
