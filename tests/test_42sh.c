/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Main test file for 42sh
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "shell.h"

void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(parsing, create_tree_node)
{
    token_tree_t *node = create_branch_by_type(PIPE);

    cr_assert_not_null(node);
    cr_assert_eq(node->type, PIPE);
    cr_assert_null(node->left);
    cr_assert_null(node->right);
    free(node);
}

Test(env, get_existing_word)
{
    char *env[] = {"PATH=/usr/bin", "HOME=/home/user", NULL};
    char *path = find_word_in_env(env, "PATH");

    cr_assert_str_eq(path, "/usr/bin");
}

Test(env, get_non_existing_word)
{
    char *env[] = {"PATH=/usr/bin", NULL};
    char *res = find_word_in_env(env, "PWD");

    cr_assert_null(res, "Should return NULL if variable doesn't exist");
}

Test(env, format_env_line)
{
    char *line = add_line_in_env("USER", "bocal");

    cr_assert_str_eq(line, "USER=bocal");
    free(line);
}
