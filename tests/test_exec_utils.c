/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Tests exec utils before command
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "shell.h"

Test(exec_utils, path_concatenation)
{
    char *path = create_path_way("/usr/bin", "grep");

    cr_assert_str_eq(path, "/usr/bin/grep");
    free(path);
}

Test(exec_utils, resolve_binary_path)
{
    char *env[] = {"PATH=/bin:/usr/bin", NULL};
    char *full_path = find_command_path("ls", env);

    cr_assert_not_null(full_path);
    cr_assert(access(full_path, X_OK) == 0);
    free(full_path);
}
