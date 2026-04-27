/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Main test file for 42sh
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "shell.h"

Test(lib_my, test_strlen)
{
    cr_assert_eq(my_strlen("EpiClaude"), 9);
    cr_assert_eq(my_strlen(""), 0);
}

Test(env_logic, test_find_env)
{
    char *fake_env[] = {"PATH=/bin", "USER=claude", NULL};
    char *res = find_word_in_env(fake_env, "USER");

    cr_assert_str_eq(res, "claude");
}

Test(path_logic, test_path_with_slash)
{
    char *fake_env[] = {"PATH=/", NULL};
    char *res = find_command_path("bin/ls", fake_env);

    cr_assert_null(res);
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

Test(pipe, create_pathway)
{
    char *path = create_path_way("/usr/bin", "ls");

    cr_assert_str_eq(path, "/usr/bin/ls");
    free(path);
}

Test(pipe, find_command_path)
{
    char *env[] = {"PATH=/usr/bin:/bin", NULL};
    char *cmd_path = find_command_path("ls", env);

    cr_assert_str_eq(cmd_path, "/usr/bin/ls");
    free(cmd_path);
}
