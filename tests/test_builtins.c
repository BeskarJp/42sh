/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Tests builtins
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "shell.h"

Test(builtin_assembly, bonus_builtin_exec_echo)
{
    shell_t shell = {0};
    int result = 0;

    shell.arg_col = malloc(sizeof(char *) * 2);
    shell.arg_col[0] = malloc(10);
    my_strcpy(shell.arg_col[0], "echo");
    shell.arg_col[1] = NULL;
    result = bonus_builtin_exec(&shell);
    cr_assert_eq(result, 1);
    free(shell.arg_col[0]);
    free(shell.arg_col);
}

Test(builtin_assembly, builtin_assembly_exit)
{
    shell_t shell = {0};
    int result = 0;

    shell.continue_shell = 1;
    shell.arg_col = malloc(sizeof(char *) * 2);
    shell.arg_col[0] = malloc(10);
    my_strcpy(shell.arg_col[0], "exit");
    shell.arg_col[1] = NULL;
    result = builtin_assembly(&shell);
    cr_assert_eq(result, 1);
    cr_assert_eq(shell.continue_shell, 0);
    free(shell.arg_col[0]);
    free(shell.arg_col);
}

Test(builtin_assembly, builtin_assembly_env)
{
    shell_t shell = {0};
    int result = 0;

    shell.arg_col = malloc(sizeof(char *) * 2);
    shell.arg_col[0] = malloc(10);
    my_strcpy(shell.arg_col[0], "env");
    shell.arg_col[1] = NULL;
    shell.copy_env = malloc(sizeof(char *) * 2);
    shell.copy_env[0] = "VAR=value";
    shell.copy_env[1] = NULL;
    result = builtin_assembly(&shell);
    cr_assert_eq(result, 1);
    cr_assert_eq(shell.exit_status, 0);
    free(shell.arg_col[0]);
    free(shell.arg_col);
    free(shell.copy_env);
}

Test(builtin_assembly, builtin_assembly_unknown_command)
{
    shell_t shell = {0};
    int result = 0;

    shell.arg_col = malloc(sizeof(char *) * 2);
    shell.arg_col[0] = malloc(15);
    my_strcpy(shell.arg_col[0], "unknown_cmd");
    shell.arg_col[1] = NULL;
    result = builtin_assembly(&shell);
    cr_assert_eq(result, 0);
    free(shell.arg_col[0]);
    free(shell.arg_col);
}

Test(cd_builtin, check_cd_flag_home_expansion)
{
    shell_t shell = {0};
    char *path = NULL;

    shell.arg_col = malloc(sizeof(char *) * 2);
    shell.arg_col[0] = "cd";
    shell.arg_col[1] = "~";
    shell.copy_env = malloc(sizeof(char *) * 2);
    shell.copy_env[0] = malloc(50);
    my_strcpy(shell.copy_env[0], "HOME=/home/testuser");
    shell.copy_env[1] = NULL;
    path = check_cd_flag(&shell);
    cr_assert_not_null(path);
    cr_assert_str_eq(path, "/home/testuser");
    free(shell.arg_col);
    free(shell.copy_env[0]);
    free(shell.copy_env);
}

Test(cd_builtin, check_cd_flag_null_path)
{
    shell_t shell = {0};
    char *path = NULL;

    shell.arg_col = malloc(sizeof(char *) * 2);
    shell.arg_col[0] = "cd";
    shell.arg_col[1] = NULL;
    shell.copy_env = malloc(sizeof(char *) * 2);
    shell.copy_env[0] = malloc(50);
    my_strcpy(shell.copy_env[0], "HOME=/home/testuser");
    shell.copy_env[1] = NULL;
    path = check_cd_flag(&shell);
    cr_assert_not_null(path);
    free(shell.arg_col);
    free(shell.copy_env[0]);
    free(shell.copy_env);
}

Test(cd_builtin, check_cd_flag_oldpwd_not_set)
{
    shell_t shell = {0};
    char *path = NULL;

    shell.arg_col = malloc(sizeof(char *) * 2);
    shell.arg_col[0] = "cd";
    shell.arg_col[1] = "-";
    shell.oldpwd = NULL;
    shell.copy_env = NULL;
    path = check_cd_flag(&shell);
    cr_assert_null(path);
    free(shell.arg_col);
}

Test(cd_builtin, check_cd_flag_oldpwd_set)
{
    shell_t shell = {0};
    char *path = NULL;

    shell.arg_col = malloc(sizeof(char *) * 2);
    shell.arg_col[0] = "cd";
    shell.arg_col[1] = "-";
    shell.oldpwd = malloc(50);
    my_strcpy(shell.oldpwd, "/tmp");
    path = check_cd_flag(&shell);
    cr_assert_str_eq(path, "/tmp");
    free(shell.arg_col);
    free(shell.oldpwd);
}

Test(cd_builtin, exec_cd_invalid_directory)
{
    shell_t shell = {0};

    shell.arg_col = malloc(sizeof(char *) * 2);
    shell.arg_col[0] = "cd";
    shell.arg_col[1] = "/nonexistent/path/12345";
    shell.oldpwd = NULL;
    exec_cd(&shell);
    cr_assert_eq(shell.exit_status, 1);
    free(shell.arg_col);
}

Test(cd_builtin, exec_cd_home_directory)
{
    shell_t shell = {0};

    shell.arg_col = malloc(sizeof(char *) * 2);
    shell.arg_col[0] = "cd";
    shell.arg_col[1] = NULL;
    shell.oldpwd = NULL;
    shell.copy_env = malloc(sizeof(char *) * 2);
    shell.copy_env[0] = malloc(50);
    my_strcpy(shell.copy_env[0], "HOME=/tmp");
    shell.copy_env[1] = NULL;
    exec_cd(&shell);
    cr_assert_eq(shell.exit_status, 0);
    cr_assert_not_null(shell.oldpwd);
    free(shell.arg_col);
    free(shell.copy_env[0]);
    free(shell.copy_env);
    if (shell.oldpwd)
        free(shell.oldpwd);
}

Test(env_builtin, display_env_null_env)
{
    shell_t shell = {0};

    shell.copy_env = NULL;
    display_env(&shell);
    cr_assert_null(shell.copy_env);
}

Test(env_builtin, display_env_single_var)
{
    shell_t shell = {0};

    shell.copy_env = malloc(sizeof(char *) * 2);
    shell.copy_env[0] = "VAR1=value1";
    shell.copy_env[1] = NULL;
    display_env(&shell);
    free(shell.copy_env);
}

Test(env_builtin, display_env_multiple_vars)
{
    shell_t shell = {0};

    shell.copy_env = malloc(sizeof(char *) * 3);
    shell.copy_env[0] = "VAR1=value1";
    shell.copy_env[1] = "VAR2=value2";
    shell.copy_env[2] = NULL;
    display_env(&shell);
    free(shell.copy_env);
}


Test(setenv, init_env_with_valid_line)
{
    shell_t shell = {0};
    char *new_line = "TEST_VAR=test_value";

    init_env(&shell, new_line);
    cr_assert_not_null(shell.copy_env);
    cr_assert_str_eq(shell.copy_env[0], new_line);
    cr_assert_null(shell.copy_env[1]);
    free(shell.copy_env);
}

Test(setenv, init_env_handles_null_shell)
{
    shell_t shell = {0};

    init_env(&shell, NULL);
    cr_assert_not_null(shell.copy_env);
    cr_assert_null(shell.copy_env[0]);
}

Test(setenv, make_env_bigger_from_empty)
{
    shell_t shell = {0};
    char *new_line = "VAR1=value1";

    shell.copy_env = NULL;
    make_env_bigger(&shell, new_line);
    cr_assert_not_null(shell.copy_env);
    cr_assert_str_eq(shell.copy_env[0], new_line);
    cr_assert_null(shell.copy_env[1]);
    free(shell.copy_env);
}

Test(setenv, make_env_bigger_extends_existing)
{
    shell_t shell = {0};
    char *line1 = "VAR1=value1";
    char *line2 = "VAR2=value2";

    shell.copy_env = malloc(sizeof(char *) * 2);
    shell.copy_env[0] = line1;
    shell.copy_env[1] = NULL;
    make_env_bigger(&shell, line2);
    cr_assert_not_null(shell.copy_env);
    cr_assert_str_eq(shell.copy_env[0], line1);
    cr_assert_str_eq(shell.copy_env[1], line2);
    cr_assert_null(shell.copy_env[2]);
    free(shell.copy_env);
}

Test(setenv, check_setenv_no_args)
{
    shell_t shell = {0};
    int result = 0;

    shell.arg_col = malloc(sizeof(char *) * 2);
    shell.arg_col[0] = "setenv";
    shell.arg_col[1] = NULL;
    shell.copy_env = NULL;
    result = check_setenv(&shell);
    cr_assert_eq(result, 84);
    free(shell.arg_col);
}

Test(setenv, check_setenv_with_invalid_chars)
{
    shell_t shell = {0};
    int result = 0;

    shell.arg_col = malloc(sizeof(char *) * 3);
    shell.arg_col[0] = "setenv";
    shell.arg_col[1] = "VAR-NAME";
    shell.arg_col[2] = "value";
    shell.copy_env = NULL;
    result = check_setenv(&shell);
    cr_assert_eq(result, 84);
    free(shell.arg_col);
}

Test(setenv, check_setenv_with_valid_name)
{
    shell_t shell = {0};
    int result = 0;

    shell.arg_col = malloc(sizeof(char *) * 3);
    shell.arg_col[0] = "setenv";
    shell.arg_col[1] = "VALIDVAr123";
    shell.arg_col[2] = "value";
    shell.copy_env = NULL;
    result = check_setenv(&shell);
    cr_assert_eq(result, 0);
    free(shell.arg_col);
}

Test(setenv, exec_setenv_new_variable)
{
    shell_t shell = {0};

    shell.arg_col = malloc(sizeof(char *) * 4);
    shell.arg_col[0] = "setenv";
    shell.arg_col[1] = "NEWVAR";
    shell.arg_col[2] = "new_value";
    shell.arg_col[3] = NULL;
    shell.copy_env = NULL;
    exec_setenv(&shell);
    cr_assert_eq(shell.exit_status, 0);
    cr_assert_not_null(shell.copy_env);
    free(shell.arg_col);
    if (shell.copy_env != NULL) {
        free(shell.copy_env[0]);
        free(shell.copy_env);
    }
}

Test(setenv, exec_setenv_update_existing_variable)
{
    shell_t shell = {0};

    shell.arg_col = malloc(sizeof(char *) * 3);
    shell.arg_col[0] = "setenv";
    shell.arg_col[1] = "VAR";
    shell.arg_col[2] = "new_value";
    shell.copy_env = malloc(sizeof(char *) * 3);
    shell.copy_env[0] = malloc(20);
    my_strcpy(shell.copy_env[0], "VAR=old_value");
    shell.copy_env[1] = malloc(20);
    my_strcpy(shell.copy_env[1], "OTHER=value");
    shell.copy_env[2] = NULL;
    exec_setenv(&shell);
    cr_assert_eq(shell.exit_status, 0);
    cr_assert_str_eq(shell.copy_env[1], "OTHER=value");
    free(shell.arg_col);
    free(shell.copy_env[0]);
    free(shell.copy_env[1]);
    free(shell.copy_env);
}

Test(setenv, exec_setenv_invalid_name)
{
    shell_t shell = {0};

    shell.arg_col = malloc(sizeof(char *) * 3);
    shell.arg_col[0] = "setenv";
    shell.arg_col[1] = "INVALID-VAR";
    shell.arg_col[2] = "value";
    shell.copy_env = NULL;
    exec_setenv(&shell);
    cr_assert_eq(shell.exit_status, 1);
    free(shell.arg_col);
}

Test(unsetenv, fill_the_void_removes_entry)
{
    char *env[] = {"VAR1=v1", "VAR2=v2", "VAR3=v3", NULL};

    fill_the_void(env, 1);
    cr_assert_str_eq(env[1], "VAR3=v3");
    cr_assert_null(env[2]);
}

Test(unsetenv, delete_var_existing_variable)
{
    shell_t shell = {0};

    shell.copy_env = malloc(sizeof(char *) * 3);
    shell.copy_env[0] = malloc(20);
    my_strcpy(shell.copy_env[0], "VAR1=value1");
    shell.copy_env[1] = malloc(20);
    my_strcpy(shell.copy_env[1], "VAR2=value2");
    shell.copy_env[2] = NULL;
    delete_var(&shell, "VAR1");
    cr_assert_str_eq(shell.copy_env[0], "VAR2=value2");
    cr_assert_null(shell.copy_env[1]);
    free(shell.copy_env[0]);
    free(shell.copy_env[1]);
    free(shell.copy_env);
}

Test(unsetenv, delete_var_nonexistent_variable)
{
    shell_t shell = {0};

    shell.copy_env = malloc(sizeof(char *) * 2);
    shell.copy_env[0] = malloc(20);
    my_strcpy(shell.copy_env[0], "VAR1=value1");
    shell.copy_env[1] = NULL;
    delete_var(&shell, "NONEXISTENT");
    cr_assert_str_eq(shell.copy_env[0], "VAR1=value1");
    free(shell.copy_env[0]);
    free(shell.copy_env);
}

Test(unsetenv, delete_var_null_env)
{
    shell_t shell = {0};

    shell.copy_env = NULL;
    delete_var(&shell, "VAR1");
    cr_assert_null(shell.copy_env);
}

Test(unsetenv, exec_unsetenv_no_args)
{
    shell_t shell = {0};

    shell.arg_col = malloc(sizeof(char *) * 2);
    shell.arg_col[0] = "unsetenv";
    shell.arg_col[1] = NULL;
    shell.copy_env = NULL;
    exec_unsetenv(&shell);
    cr_assert_eq(shell.exit_status, 1);
    free(shell.arg_col);
}

Test(unsetenv, exec_unsetenv_single_var)
{
    shell_t shell = {0};

    shell.arg_col = malloc(sizeof(char *) * 3);
    shell.arg_col[0] = "unsetenv";
    shell.arg_col[1] = "VAR1";
    shell.arg_col[2] = NULL;
    shell.copy_env = malloc(sizeof(char *) * 2);
    shell.copy_env[0] = malloc(20);
    my_strcpy(shell.copy_env[0], "VAR1=value1");
    shell.copy_env[1] = NULL;
    exec_unsetenv(&shell);
    cr_assert_eq(shell.exit_status, 0);
    free(shell.arg_col);
    free(shell.copy_env[0]);
    free(shell.copy_env);
}

Test(unsetenv, exec_unsetenv_multiple_vars)
{
    shell_t shell = {0};

    shell.arg_col = malloc(sizeof(char *) * 4);
    shell.arg_col[0] = "unsetenv";
    shell.arg_col[1] = "VAR1";
    shell.arg_col[2] = "VAR2";
    shell.arg_col[3] = NULL;
    shell.copy_env = malloc(sizeof(char *) * 3);
    shell.copy_env[0] = malloc(20);
    my_strcpy(shell.copy_env[0], "VAR1=value1");
    shell.copy_env[1] = malloc(20);
    my_strcpy(shell.copy_env[1], "VAR2=value2");
    shell.copy_env[2] = NULL;
    exec_unsetenv(&shell);
    cr_assert_eq(shell.exit_status, 0);
    free(shell.arg_col);
    free(shell.copy_env[0]);
    free(shell.copy_env[1]);
    free(shell.copy_env);
}
