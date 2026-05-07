/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Free for valgrind
*/

#include "shell.h"

/**
 * @brief Free a NULL-terminated array of strings
 *
 * @param array Array to free
 */
void free_array(char **array)
{
    if (array == NULL)
        return;
    for (int i = 0; array[i] != NULL; i++)
        free(array[i]);
    free(array);
}

/**
 * @brief Frees the alias linked list
 *
 * @param aliases Alias stucture
 */
void free_aliases(alias_t *aliases)
{
    alias_t *temp;

    while (aliases) {
        temp = aliases;
        aliases = aliases->next;
        free(temp->name);
        free(temp->command);
        free(temp);
    }
}

/**
 * @brief Frees the history linked list
 *
 * @param history History stucture
 */
void free_history(history_t *history)
{
    history_t *temp;

    while (history) {
        temp = history;
        history = history->next;
        free(temp->command);
        free(temp->time);
        free(temp);
    }
}

/**
 * @brief Frees the env tab
 *
 * @param env Env structure
 */
void free_env(env_t *env)
{
    env_t *temp;

    while (env) {
        temp = env;
        env = env->next;
        if (temp->var)
            free(temp->var);
        if (temp->value)
            free(temp->value);
        free(temp);
    }
}

/**
 * @brief Recursive free for token_tree_t tree
 *
 * @param tree Token tree to free
 */
void free_tree(token_tree_t *tree)
{
    if (!tree)
        return;
    free_tree(tree->left);
    free_tree(tree->right);
    if (tree->args)
        free_array(tree->args);
    if (tree->file)
        free(tree->file);
    free(tree);
}
