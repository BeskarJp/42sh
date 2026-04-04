/*
** EPITECH PROJECT, 2026
** Minishell 2
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
 * @brief Free allocated resources for the oldpwd variable
 *
 * @param shell Shell structure
 */
void free_cd(shell_t *shell)
{
    if (shell->oldpwd)
        free(shell->oldpwd);
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
