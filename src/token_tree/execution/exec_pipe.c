/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Execute pipe in minishell
*/

#include "shell.h"

/**
 * @brief Child process #1 to execute the left side of the pipe
 *
 * @param shell Shell structure
 * @param tree Command tree
 * @param child1 PID returned by fork for child 1
 * @param pipefd Pipe descriptor
 */
void child_one(shell_t *shell, token_tree_t *tree, pid_t child1, int pipefd[2])
{
    if (child1 == -1)
        return;
    if (child1 == 0) {
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);
        run_tree(shell, tree->left);
        exit(0);
    }
}

/**
 * @brief Child process #2 to execute the right side of the pipe
 *
 * @param shell Shell structure
 * @param tree Command tree
 * @param child2 PID returned by fork for child 2
 * @param pipefd Pipe descriptor
 */
void child_two(shell_t *shell, token_tree_t *tree, pid_t child2, int pipefd[2])
{
    if (child2 == -1)
        return;
    if (child2 == 0) {
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);
        run_tree(shell, tree->right);
        exit(0);
    }
}

/**
 * @brief Executes the pipe represented by the tree and waits the 2 childrens
 *
 * @param shell Shell structure
 * @param tree Command tree with pipe operator
 */
void run_pipe(shell_t *shell, token_tree_t *tree)
{
    int pipefd[2];
    pid_t child1;
    pid_t child2;

    if (pipe(pipefd) < 0)
        return;
    child1 = fork();
    child_one(shell, tree, child1, pipefd);
    child2 = fork();
    child_two(shell, tree, child2, pipefd);
    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(child1, NULL, 0);
    waitpid(child2, NULL, 0);
}
