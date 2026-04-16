/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Execute tree in minishell
*/

#include "shell.h"

/**
 * @brief Exec operators commands && + ||
 *
 * @param shell Shell structure
 * @param tree Command tree with operators operator
 */
void exec_operators(shell_t *shell, token_tree_t *tree)
{
    if (tree->type == AND_OPERATOR) {
        run_tree(shell, tree->left);
        if (shell->exit_status == 0)
            run_tree(shell, tree->right);
    }
    if (tree->type == OR_OPERATOR) {
        run_tree(shell, tree->left);
        if (shell->exit_status != 0)
            run_tree(shell, tree->right);
    }
}
