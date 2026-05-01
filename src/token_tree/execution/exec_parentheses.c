/*
** EPITECH PROJECT, 2026
** exec_parentheses
** File description:
** Execute a SUBSHELL node  (command group between parentheses)
*/
#include "shell.h"

/**
 * @brief Child process: runs the subtree inside the parenthese
 *
 * @param shell Shell structure
 * @param tree  SUBSHELL node whose left child is the inner command tree
 */
static void run_subshell_child(shell_t *shell, token_tree_t *tree)
{
    run_tree(shell, tree->left);
    exit(shell->exit_status);
}

/**
 * @brief Parent process: waits for the child and records its exit status.
 *
 * @param shell  Shell structure
 * @param tree   SUBSHELL node
 * @param pid    PID of the child process
 */
static void run_subshell_parent(shell_t *shell, token_tree_t *tree, pid_t pid)
{
    int status = 0;

    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
        shell->exit_status = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
        shell->exit_status = 128 + WTERMSIG(status);
    if (tree->right)
        run_tree(shell, tree->right);
}

/**
 * @brief Executes a SUBSHELL node.
 *
 * @param shell Shell structure
 * @param tree  SUBSHELL node
 */
void exec_parentheses(shell_t *shell, token_tree_t *tree)
{
    pid_t pid;

    if (!tree || !tree->left)
        return;
    pid = fork();
    if (pid == -1) {
        perror("fork");
        shell->exit_status = 1;
        return;
    }
    if (pid == 0)
        run_subshell_child(shell, tree);
    else
        run_subshell_parent(shell, tree, pid);
}
