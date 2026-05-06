/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Tests exec of commands
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "shell.h"

Test(backticks, handle_backticks_no_backticks)
{
    shell_t shell = {0};
    char *line = my_strdup("echo hello");
    char *result = handle_backticks(&shell, line);

    cr_assert_str_eq(result, "echo hello");
    free(result);
}

Test(backticks, handle_backticks_with_backticks)
{
    shell_t shell = {0};
    char *line = my_strdup("echo `echo world` test");
    char *result = handle_backticks(&shell, line);

    cr_assert_not_null(result);
    free(result);
}

Test(shell_scripting, try_execute_bash_script_no_script)
{
    shell_t shell = {0};
    char *line = "echo hello";
    bool result = try_execute_bash_script(&shell, line);

    cr_assert_eq(result, false);
}

Test(shell_scripting, try_execute_bash_script_with_script)
{
    shell_t shell = {0};
    char *line = "[[ 1 -eq 1 ]] && echo test";
    bool result = try_execute_bash_script(&shell, line);

    cr_assert_eq(result, true);
}

Test(shell_request, line_executor_background)
{
    shell_t shell = {0};
    char *line = my_strdup("echo hello &");

    line_executor(&shell, line);
    free(line);
}

Test(shell_request, line_executor_empty)
{
    shell_t shell = {0};
    char *line = my_strdup("");

    line_executor(&shell, line);
    free(line);
}

Test(shell_request, line_executor_invalid)
{
    shell_t shell = {0};
    char *line = my_strdup("invalid_command");

    line_executor(&shell, line);
    free(line);
}
