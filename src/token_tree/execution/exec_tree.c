/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Execute tree in minishell
*/

#include "shell.h"

/**
 * @brief Executes a simple command
 *
 * @param shell Shell structure
 * @param tree Simple command node
 */
void run_simple_command(shell_t *shell, token_tree_t *tree)
{
    alias_checker(shell, tree);
    var_interpreter(shell, tree);
    tree->args = expand_globbing(tree->args);
    shell->arg_col = tree->args;
    if (!shell->arg_col || !shell->arg_col[0])
        return;
    if (builtin_assembly(shell) == 0) {
        if (var_declared(shell, 0) == 0) {
            handle_local_var(shell);
            return;
        }
        execute_command(shell);
    }
}

/**
 * @brief Traverses the token tree and executes nodes by type.
 *
 * @param shell Shell structure
 * @param tree Redirection tree
 */
void run_tree(shell_t *shell, token_tree_t *tree)
{
    if (!tree)
        return;
    if (tree->type == SEMICOLONS) {
        run_tree(shell, tree->left);
        run_tree(shell, tree->right);
    }
    if (tree->type == AND_OPERATOR || tree->type == OR_OPERATOR)
        exec_operators(shell, tree);
    if (tree->type == PIPE)
        run_pipe(shell, tree);
    if (tree->type == SUBSHELL)
        exec_parentheses(shell, tree);
    if (tree->type >= REDIR_DROITE && tree->type <= REDIR_DB_GAUCHE)
        run_redirection(shell, tree);
    if (tree->type == SIMPLE_COMMAND)
        run_simple_command(shell, tree);
}
