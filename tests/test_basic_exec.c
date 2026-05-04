/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Tests exec of commands
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "shell.h"

Test(exec, find_env_var)
{
    char *env[] = {"PATH=/usr/bin", "HOME=/home/user", NULL};
    char *res = find_word_in_env(env, "HOME");
    cr_assert_str_eq(res, "/home/user");

    res = find_word_in_env(env, "UNKNOWN");
    cr_assert_null(res);
}

Test(exec, create_path_way_test)
{
    char *res = create_path_way("/bin", "ls");
    cr_assert_str_eq(res, "/bin/ls");
    free(res);
}

Test(exec, find_command_path_test)
{
    char *env[] = {"PATH=/bin:/usr/bin", NULL};
    char *path = find_command_path("ls", env);

    cr_assert_not_null(path);
    cr_assert(access(path, X_OK) == 0);
    free(path);
}

Test(exec, add_line_in_env_test)
{
    char *res = add_line_in_env("TEST", "VALUE");

    cr_assert_str_eq(res, "TEST=VALUE");
    free(res);
}
