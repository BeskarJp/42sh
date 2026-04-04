/*
** EPITECH PROJECT, 2026
** Minishell 2
** File description:
** Parse line in shell
*/

#include "shell.h"

/**
 * @brief Parses line for redirections (> >> < <<), otherwise a simple command
 *
 * @param line Line to parse
 * @return token_tree_t* Command tree
 */
token_tree_t *parse_redirections(char *line)
{
    token_tree_t *tree = NULL;

    for (int i = my_strlen(line) - 1; i >= 0; i--) {
        if (i > 0 && line[i - 1] == '>' && line[i] == '>')
            return create_redirection_branch(line, i - 1, 2, REDIR_DB_DROITE);
        if (i > 0 && line[i - 1] == '<' && line[i] == '<')
            return create_redirection_branch(line, i - 1, 2, REDIR_DB_GAUCHE);
        if (line[i] == '>')
            return create_redirection_branch(line, i, 1, REDIR_DROITE);
        if (line[i] == '<')
            return create_redirection_branch(line, i, 1, REDIR_GAUCHE);
    }
    tree = create_branch_by_type(SIMPLE_COMMAND);
    tree->args = my_str_to_word_array(line);
    return tree;
}

/**
 * @brief Parses line for find pipe '|' and build the tree
 *
 * @param line Line to parse
 * @return token_tree_t* Command tree
 */
token_tree_t *parse_pipe(char *line)
{
    struct_parse_t data;

    for (int i = my_strlen(line) - 1; i >= 0; i--) {
        if (line[i] == '|') {
            data = (struct_parse_t){PIPE, i, 1, parse_pipe, parse_redirections};
            return cut_branch(line, &data);
        }
    }
    return parse_redirections(line);
}

/**
 * @brief Parses line in the order ';', '|', then redirections/command.
 *
 * @param line Line to parse
 * @return token_tree_t* Final command tree
 */
token_tree_t *parse_line(char *line)
{
    struct_parse_t data;

    if (!line)
        return NULL;
    for (int i = my_strlen(line) - 1; i >= 0; i--) {
        if (line[i] == ';') {
            data = (struct_parse_t){SEMICOLONS, i, 1, parse_line, parse_pipe};
            return cut_branch(line, &data);
        }
    }
    return parse_pipe(line);
}
