/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Tests parsing of 42sh
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "shell.h"

Test(parsing, clear_string_basic)
{
    char *str = "   ls -la   ";
    char *res = clear_string(str, 0, strlen(str));

    cr_assert_str_eq(res, "ls -la");
    free(res);
}

Test(parsing, parse_simple_command)
{
    char *cmd = "ls -l";
    token_tree_t *tree = parse_line(cmd);

    cr_assert_not_null(tree);
    cr_assert_eq(tree->type, SIMPLE_COMMAND);
    cr_assert_str_eq(tree->args[0], "ls");
    free_tree(tree);
}

Test(parsing, parse_pipe)
{
    char *cmd = "ls | grep test";
    token_tree_t *tree = parse_line(cmd);

    cr_assert_not_null(tree);
    cr_assert_eq(tree->type, PIPE);
    cr_assert_eq(tree->left->type, SIMPLE_COMMAND);
    cr_assert_eq(tree->right->type, SIMPLE_COMMAND);
    free_tree(tree);
}

Test(parsing, parse_logical_complex)
{
    char *cmd = "ls && cat file || echo fail";
    token_tree_t *tree = parse_line(cmd);

    cr_assert_not_null(tree);
    cr_assert_eq(tree->type, OR_OPERATOR);
    cr_assert_eq(tree->left->type, AND_OPERATOR);
    free_tree(tree);
}
