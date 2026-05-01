/*
** EPITECH PROJECT, 2026
** parse_parentheses
** File description:
** Parse parentheses groups into SUBSHELL nodes
*/
#include "shell.h"

/**
 * @brief Finds the matching closing parenthesis for a given '(' index.
 *
 * @param line  Line to scan
 * @param start Index of the '(' character
 */
static int find_closing_paren(char *line, int start)
{
    int depth = 0;

    for (int i = start; line[i]; i++) {
        if (line[i] == '(')
            depth++;
        if (line[i] == ')')
            depth--;
        if (depth == 0)
            return i;
    }
    return -1;
}

/**
 * @brief Extracts the substring strictly between open and close indices.
 *
 * @param line  Source string
 * @param open  Index of '('
 * @param close Index of ')'
 */
static char *extract_inner(char *line, int open, int close)
{
    int len = close - open - 1;
    char *inner = NULL;

    if (len <= 0)
        return NULL;
    inner = malloc(sizeof(char) * (len + 1));
    if (!inner)
        return NULL;
    strncpy(inner, line + open + 1, len);
    inner[len] = '\0';
    return inner;
}

/**
 * @brief Trims leading spaces from a string (returns pointer into it).
 */
static char *trim_left(char *s)
{
    while (*s == ' ' || *s == '\t')
        s++;
    return s;
}

/**
 * @brief Builds a SUBSHELL node.
 *
 * @param line  Full command line
 * @param open  Index of '('
 * @param close Index of matching ')'
 */
static token_tree_t *build_subshell_node(char *line, int open, int close)
{
    token_tree_t *node = create_branch_by_type(SUBSHELL);
    char *inner = NULL;
    char *after = NULL;

    if (!node)
        return NULL;
    inner = extract_inner(line, open, close);
    if (!inner) {
        free(node);
        return NULL;
    }
    node->left = parse_line(inner);
    free(inner);
    after = trim_left(line + close + 1);
    if (after && after[0] != '\0')
        node->right = parse_redirections(after);
    return node;
}

/**
 * @brief Scans the line left-to-right
 *
 * @param line Line to parse
 */
token_tree_t *parse_parentheses(char *line)
{
    int open = -1;
    int close = -1;
    char *trimmed = trim_left(line);

    for (int i = 0; trimmed[i]; i++) {
        if (trimmed[i] == '(') {
            open = i;
            close = find_closing_paren(trimmed, i);
            break;
        }
    }
    if (open == -1 || close == -1)
        return parse_redirections(line);
    return build_subshell_node(trimmed, open, close);
}
