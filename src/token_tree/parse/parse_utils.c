/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Utils for parse line
*/

#include "shell.h"

/**
 * @brief Creates a command tree node with the given type
 *
 * @param type Node type (PIPE, REDIR, ...)
 * @return token_tree_t* Allocated node or NULL
 */
token_tree_t *create_branch_by_type(node_type_t type)
{
    token_tree_t *tree = malloc(sizeof(token_tree_t));

    if (!tree)
        return NULL;
    tree->type = type;
    tree->args = NULL;
    tree->file = NULL;
    tree->left = NULL;
    tree->right = NULL;
    return tree;
}

/**
 * @brief Creates a redirection node from a line and position.
 *
 * @param line Full command line.
 * @param i Index of the redirection symbol
 * @param len Length of the symbol (1 or 2)
 * @param type Redirection type
 * @return token_tree_t* Redirection node or NULL.
 */
token_tree_t *create_redirection_branch(char *line,
    int i, int len, node_type_t type)
{
    token_tree_t *tree = create_branch_by_type(type);

    if (!tree)
        return NULL;
    tree->left = parse_redirections(clear_string(line, 0, i));
    tree->file = clear_string(line, i + len, my_strlen(line));
    return tree;
}

/**
 * @brief Split line into two branches using a given operator.
 *
 * @param line Command line
 * @param data Split parameters and parser functions
 * @return token_tree_t* Node representing the operator
 */
token_tree_t *cut_branch(char *line, struct_parse_t *data)
{
    token_tree_t *tree = create_branch_by_type(data->type);
    int len = my_strlen(line);

    tree->left = data->left_function(
        clear_string(line, 0, data->count_stopped));
    tree->right = data->right_function(
        clear_string(line, data->count_stopped + data->end_line, len));
    return tree;
}
