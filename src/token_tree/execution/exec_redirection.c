/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Execute redirection in minishell
*/

#include "shell.h"

/**
 * @brief Open a file based on the redirection type
 *
 * @param tree Redirection tree
 * @param fd Initial file
 * @return int. Opened file descriptor or an error of fd
 */
int manipulate_file_with_type(token_tree_t *tree, int fd)
{
    if (tree->type == REDIR_DROITE)
        fd = open(tree->file, O_WRONLY | O_CREAT | O_TRUNC, PERM_NORM);
    if (tree->type == REDIR_DB_DROITE)
        fd = open(tree->file, O_WRONLY | O_CREAT | O_APPEND, PERM_NORM);
    if (tree->type == REDIR_GAUCHE)
        fd = open(tree->file, O_RDONLY);
    if (tree->type == REDIR_DB_GAUCHE)
        left_double_redirection(tree->file);
    return fd;
}

/**
 * @brief Handles redirection, execute a command in a child
 *
 * @param shell Shell structure
 * @param tree Redirection tree
 */
void run_redirection(shell_t *shell, token_tree_t *tree)
{
    int fd = FD_ERROR;
    pid_t pid = fork();

    if (pid != 0) {
        waitpid(pid, NULL, 0);
        return;
    }
    fd = manipulate_file_with_type(tree, fd);
    if (fd == FD_ERROR && tree->type != REDIR_DB_GAUCHE) {
        perror(tree->file);
        exit(1);
    }
    if (fd != FD_ERROR) {
        dup2(fd, (tree->type == REDIR_GAUCHE) ? 0 : 1);
        close(fd);
    }
    run_tree(shell, tree->left);
    exit(0);
}
