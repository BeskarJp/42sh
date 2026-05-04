/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Tests env functions
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "shell.h"

Test(env, copy_env_integrity)
{
    char *env[] = {"PATH=/bin", "USER=hugoat", NULL};
    char **copy = copy_environment(env);

    cr_assert_str_eq(copy[0], "PATH=/bin");
    cr_assert_str_eq(copy[1], "USER=hugoat");
    cr_assert_null(copy[2]);
    free_array(copy);
}

Test(env, find_var_value)
{
    char *env[] = {"HOME=/home/user", "SHELL=42sh", NULL};

    cr_assert_str_eq(find_word_in_env(env, "HOME"), "/home/user");
    cr_assert_null(find_word_in_env(env, "UNKNOWN"));
}

Test(env, create_env_line)
{
    char *line = add_line_in_env("MY_VAR", "42");

    cr_assert_str_eq(line, "MY_VAR=42");
    free(line);
}

Test(env, path_concatenation)
{
    char *path = create_path_way("/usr/bin", "grep");

    cr_assert_str_eq(path, "/usr/bin/grep");
    free(path);
}

Test(env, resolve_binary_path)
{
    char *env[] = {"PATH=/bin:/usr/bin", NULL};
    char *full_path = find_command_path("ls", env);

    cr_assert_not_null(full_path);
    cr_assert(access(full_path, X_OK) == 0);
    free(full_path);
}
