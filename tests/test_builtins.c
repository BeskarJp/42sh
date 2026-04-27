/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Tests env functions
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "shell.h"

Test(builtins, history_storage)
{
    shell_t shell = {0};

    add_to_history_linked_list(&shell, "ls -la");
    cr_assert_not_null(shell.history);
    cr_assert_str_eq(shell.history->command, "ls -la");
    free_history(shell.history);
}
