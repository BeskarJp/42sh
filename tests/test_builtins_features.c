/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Tests builtins features
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "shell.h"

Test(builtins_assembly, builtin_exec_continue_alias)
{
    shell_t shell = {0};
    int result = 0;

    shell.arg_col = malloc(sizeof(char *) * 2);
    shell.arg_col[0] = malloc(10);
    my_strcpy(shell.arg_col[0], "alias");
    shell.arg_col[1] = NULL;
    shell.aliases = NULL;
    result = builtin_exec_continue(&shell);
    cr_assert_eq(result, 1);
    free(shell.arg_col[0]);
    free(shell.arg_col);
}

Test(builtins_assembly, builtin_exec_continue_unalias)
{
    shell_t shell = {0};
    int result = 0;

    shell.arg_col = malloc(sizeof(char *) * 2);
    shell.arg_col[0] = malloc(10);
    my_strcpy(shell.arg_col[0], "unalias");
    shell.arg_col[1] = NULL;
    result = builtin_exec_continue(&shell);
    cr_assert_eq(result, 1);
    free(shell.arg_col[0]);
    free(shell.arg_col);
}

Test(aliases, find_add_and_update_alias)
{
    shell_t shell = {0};
    alias_t *alias = NULL;

    add_alias(&shell, "ll", "ls -la");
    alias = find_alias_by_name(shell.aliases, "ll");
    cr_assert_not_null(alias);
    cr_assert_str_eq(alias->command, "ls -la");
    add_alias(&shell, "ll", "ls -lah");
    alias = find_alias_by_name(shell.aliases, "ll");
    cr_assert_not_null(alias);
    cr_assert_str_eq(alias->command, "ls -lah");
    free(alias->name);
    free(alias->command);
    free(alias);
}

Test(aliases, exec_alias_creates_new_alias)
{
    shell_t shell = {0};

    shell.arg_col = malloc(sizeof(char *) * 4);
    shell.arg_col[0] = "alias";
    shell.arg_col[1] = "ll";
    shell.arg_col[2] = "ls";
    shell.arg_col[3] = NULL;
    exec_alias(&shell);
    cr_assert_not_null(shell.aliases);
    cr_assert_str_eq(shell.aliases->name, "ll");
    cr_assert_str_eq(shell.aliases->command, "ls");
    free(shell.aliases->name);
    free(shell.aliases->command);
    free(shell.aliases);
    free(shell.arg_col);
}

Test(aliases, exec_unalias_removes_existing_alias)
{
    shell_t shell = {0};
    alias_t *alias = malloc(sizeof(alias_t));

    alias->name = my_strdup("ls");
    alias->command = my_strdup("ls -la");
    alias->next = NULL;
    shell.aliases = alias;
    shell.arg_col = malloc(sizeof(char *) * 2);
    shell.arg_col[0] = "unalias";
    shell.arg_col[1] = "ls";
    exec_unalias(&shell);
    cr_assert_null(shell.aliases);
    free(shell.arg_col);
}

Test(aliases, get_full_command_concatenates_multiple_arguments)
{
    char *args[] = {"alias", "ll", "ls", "-la", NULL};
    char *command = get_full_command(args);

    cr_assert_not_null(command);
    cr_assert_str_eq(command, "ls -la");
    free(command);
}

Test(aliases, display_aliases_prints_specific_alias)
{
    shell_t shell = {0};
    alias_t *alias = malloc(sizeof(alias_t));

    alias->name = my_strdup("ll");
    alias->command = my_strdup("ls -la");
    alias->next = NULL;
    shell.aliases = alias;
    shell.arg_col = malloc(sizeof(char *) * 3);
    shell.arg_col[0] = "alias";
    shell.arg_col[1] = "ll";
    shell.arg_col[2] = NULL;
    cr_redirect_stdout();
    display_aliases(&shell);
    cr_assert_stdout_eq_str("ls -la\n");
    free(alias->name);
    free(alias->command);
    free(alias);
    free(shell.arg_col);
}

Test(aliases, display_aliases_prints_all_aliases)
{
    shell_t shell = {0};
    alias_t *first = malloc(sizeof(alias_t));
    alias_t *second = malloc(sizeof(alias_t));

    first->name = my_strdup("ll");
    first->command = my_strdup("ls -la");
    first->next = second;
    second->name = my_strdup("gst");
    second->command = my_strdup("git status");
    second->next = NULL;
    shell.aliases = first;
    shell.arg_col = malloc(sizeof(char *) * 2);
    shell.arg_col[0] = "alias";
    shell.arg_col[1] = NULL;
    cr_redirect_stdout();
    display_aliases(&shell);
    cr_assert_stdout_eq_str("ll\tls -la\ngst\tgit status\n");
    free(first->name);
    free(first->command);
    free(second->name);
    free(second->command);
    free(first);
    free(second);
    free(shell.arg_col);
}

Test(aliases, find_alias_by_name_returns_null_when_missing)
{
    shell_t shell = {0};
    alias_t *alias = malloc(sizeof(alias_t));

    alias->name = my_strdup("ll");
    alias->command = my_strdup("ls -la");
    alias->next = NULL;
    shell.aliases = alias;
    cr_assert_null(find_alias_by_name(shell.aliases, "gst"));
    free(alias->name);
    free(alias->command);
    free(alias);
}

Test(aliases, add_alias_adds_new_node_when_no_alias_exists)
{
    shell_t shell = {0};

    add_alias(&shell, "ll", "ls -la");
    cr_assert_not_null(shell.aliases);
    cr_assert_str_eq(shell.aliases->name, "ll");
    cr_assert_str_eq(shell.aliases->command, "ls -la");
    free(shell.aliases->name);
    free(shell.aliases->command);
    free(shell.aliases);
}

Test(aliases, delete_alias_node_removes_middle_alias)
{
    shell_t shell = {0};
    alias_t *first = malloc(sizeof(alias_t));
    alias_t *second = malloc(sizeof(alias_t));

    first->name = my_strdup("a");
    first->command = my_strdup("cmd_a");
    first->next = second;
    second->name = my_strdup("b");
    second->command = my_strdup("cmd_b");
    second->next = NULL;
    shell.aliases = first;
    delete_alias_node(&shell, second, first);
    cr_assert_null(first->next);
    cr_assert_str_eq(shell.aliases->name, "a");
    free(first->name);
    free(first->command);
    free(first);
}

Test(history, history_storage)
{
    shell_t shell = {0};

    add_to_history_linked_list(&shell, "ls -la");
    cr_assert_not_null(shell.history);
    cr_assert_str_eq(shell.history->command, "ls -la");
    free_history(shell.history);
}

Test(history, get_history_by_index_and_string)
{
    shell_t shell = {0};
    history_t first = {1, "ls", "00:00", NULL};
    history_t second = {2, "git status", "00:01", NULL};

    first.next = &second;
    shell.history = &first;
    cr_assert_str_eq(find_command_by_index(shell.history, 1), "ls");
    cr_assert_str_eq(get_history_by_index(&shell, -1), "git status");
    cr_assert_str_eq(get_history_by_str(&shell, "git"), "git status");
    cr_assert_str_eq(find_expansion(&shell, "1"), "ls");
    cr_assert_str_eq(find_expansion(&shell, "git"), "git status");
}

Test(history, get_current_time_returns_formatted_string)
{
    char *time_str = get_current_time();

    cr_assert_not_null(time_str);
    cr_assert_eq(my_strlen(time_str), 5);
    free(time_str);
}

Test(history, check_history_feature_expands_history)
{
    shell_t shell = {0};
    history_t first = {1, "ls", "00:00", NULL};
    history_t second = {2, "git status", "00:01", NULL};
    char *line = my_strdup("!git");
    char *result = NULL;

    first.next = &second;
    shell.history = &first;
    cr_redirect_stdout();
    result = check_history_feature(&shell, line);
    cr_assert_not_null(result);
    cr_assert_str_eq(result, "git status");
    free(result);
}

Test(history, check_history_feature_not_found)
{
    shell_t shell = {0};
    char *line = my_strdup("!unknown");

    cr_redirect_stderr();
    cr_assert_null(check_history_feature(&shell, line));
    cr_assert_stderr_eq_str("unknown: Event not found.\n");
}

Test(special_var, cwd_builtin_prints_pwd)
{
    shell_t shell = {0};

    shell.copy_env = malloc(sizeof(char *) * 2);
    shell.copy_env[0] = "PWD=/tmp";
    shell.copy_env[1] = NULL;
    cr_redirect_stdout();
    cwd_builtin(&shell);
    cr_assert_stdout_eq_str("/tmp\n");
    free(shell.copy_env);
}

Test(special_var, cwd_builtin_ignores_missing_pwd)
{
    shell_t shell = {0};

    shell.copy_env = malloc(sizeof(char *) * 2);
    shell.copy_env[0] = "HOME=/tmp";
    shell.copy_env[1] = NULL;
    cr_redirect_stdout();
    cwd_builtin(&shell);
    cr_assert_stdout_eq_str("");
    free(shell.copy_env);
}

Test(export, find_var_by_name_and_export)
{
    shell_t shell = {0};
    env_t *first = malloc(sizeof(env_t));

    first->var = my_strdup("VAR1");
    first->value = my_strdup("value1");
    first->temp = 0;
    first->next = NULL;
    shell.local_env = first;
    shell.arg_col = malloc(sizeof(char *) * 2);
    shell.arg_col[0] = "export";
    shell.arg_col[1] = "VAR1";
    shell.copy_env = NULL;
    export_builtin(&shell);
    cr_assert_not_null(shell.copy_env);
    cr_assert_str_eq(shell.copy_env[0], "VAR1=value1");
    cr_assert_null(shell.copy_env[1]);
    free(shell.copy_env);
    free(shell.arg_col);
}

Test(export, export_helper_updates_existing_line)
{
    shell_t shell = {0};
    env_t local = {"VAR1", "new", 0, NULL};

    shell.copy_env = malloc(sizeof(char *) * 2);
    shell.copy_env[0] = my_strdup("VAR1=old");
    shell.copy_env[1] = NULL;
    export_helper(&shell, &local);
    cr_assert_str_eq(shell.copy_env[0], "VAR1=new");
    free(shell.copy_env[0]);
    free(shell.copy_env);
}

Test(export, no_arg_export_prints_declare_entries)
{
    shell_t shell = {0};

    shell.copy_env = malloc(sizeof(char *) * 2);
    shell.copy_env[0] = my_strdup("VAR1=value1");
    shell.copy_env[1] = NULL;
    shell.arg_col = malloc(sizeof(char *) * 2);
    shell.arg_col[0] = "export";
    shell.arg_col[1] = NULL;
    cr_redirect_stdout();
    export_builtin(&shell);
    cr_assert_stdout_eq_str("declare -x VAR1=value1\n");
    free(shell.copy_env[0]);
    free(shell.copy_env);
    free(shell.arg_col);
}

Test(export, export_builtin_creates_new_env_variable)
{
    shell_t shell = {0};

    shell.arg_col = malloc(sizeof(char *) * 3);
    shell.arg_col[0] = "export";
    shell.arg_col[1] = "A=1";
    shell.arg_col[2] = NULL;
    shell.copy_env = NULL;
    shell.local_env = NULL;
    export_builtin(&shell);
    cr_assert_not_null(shell.copy_env);
    cr_assert_str_eq(shell.copy_env[0], "A=1");
    cr_assert_null(shell.copy_env[1]);
    free(shell.copy_env[0]);
    free(shell.copy_env);
    free(shell.arg_col);
}

Test(local_env, add_and_remove_variable)
{
    shell_t shell = {0};

    add_to_local_env(&shell, "A=1", 0);
    cr_assert_not_null(shell.local_env);
    cr_assert_str_eq(shell.local_env->var, "A");
    cr_assert_str_eq(shell.local_env->value, "1");
    rm_local_env_var(&shell, "A");
    cr_assert_null(shell.local_env);
}

Test(local_env, rm_local_env_var_removes_middle_entry)
{
    shell_t shell = {0};
    env_t *first = malloc(sizeof(env_t));
    env_t *second = malloc(sizeof(env_t));

    first->var = my_strdup("A");
    first->value = my_strdup("1");
    first->temp = 0;
    first->next = second;
    second->var = my_strdup("B");
    second->value = my_strdup("2");
    second->temp = 0;
    second->next = NULL;
    shell.local_env = first;

    rm_local_env_var(&shell, "B");
    cr_assert_not_null(shell.local_env);
    cr_assert_null(shell.local_env->next);
    cr_assert_str_eq(shell.local_env->var, "A");

    free(first->var);
    free(first->value);
    free(first);
}

Test(local_env, display_local_env_prints_each_variable)
{
    shell_t shell = {0};
    env_t *first = malloc(sizeof(env_t));
    env_t *second = malloc(sizeof(env_t));

    first->var = my_strdup("A");
    first->value = my_strdup("1");
    first->temp = 0;
    first->next = second;
    second->var = my_strdup("B");
    second->value = my_strdup("2");
    second->temp = 0;
    second->next = NULL;
    shell.local_env = first;
    cr_redirect_stdout();
    display_local_env(&shell);
    cr_assert_stdout_eq_str("A=1\nB=2\n");
    free(first->var);
    free(first->value);
    free(second->var);
    free(second->value);
    free(first);
    free(second);
}

Test(local_env, local_var_only_adds_all_vars)
{
    shell_t shell = {0};

    shell.arg_col = malloc(sizeof(char *) * 3);
    shell.arg_col[0] = "set";
    shell.arg_col[1] = "A=1";
    shell.arg_col[2] = NULL;
    local_var_only(&shell);
    cr_assert_not_null(shell.local_env);
    cr_assert_str_eq(shell.local_env->var, "A");
    cr_assert_str_eq(shell.local_env->value, "1");
    rm_local_env_var(&shell, "A");
    free(shell.arg_col);
}

Test(variables, set_builtin_not_enough_arguments)
{
    shell_t shell = {0};

    shell.arg_col = malloc(sizeof(char *) * 2);
    shell.arg_col[0] = "set";
    shell.arg_col[1] = NULL;
    cr_redirect_stderr();
    cr_assert_eq(set_builtin(&shell), 0);
    cr_assert_stderr_eq_str("set: Not enough arguments.\n");
    free(shell.arg_col);
}

Test(variables, set_builtin_adds_variable)
{
    shell_t shell = {0};

    shell.arg_col = malloc(sizeof(char *) * 3);
    shell.arg_col[0] = "set";
    shell.arg_col[1] = "A=1";
    shell.arg_col[2] = NULL;
    set_builtin(&shell);
    cr_assert_not_null(shell.local_env);
    cr_assert_str_eq(shell.local_env->var, "A");
    cr_assert_str_eq(shell.local_env->value, "1");
    rm_local_env_var(&shell, "A");
}

Test(variables, unset_builtin_removes_variable)
{
    shell_t shell = {0};
    env_t *local = malloc(sizeof(env_t));

    local->var = my_strdup("A");
    local->value = my_strdup("1");
    local->temp = 0;
    local->next = NULL;
    shell.arg_col = malloc(sizeof(char *) * 3);
    shell.arg_col[0] = "unset";
    shell.arg_col[1] = "A";
    shell.arg_col[2] = NULL;
    shell.local_env = local;
    unset_builtin(&shell);
    cr_assert_null(shell.local_env);
    free(shell.arg_col);
}

Test(variables, var_declared_valid_and_invalid)
{
    shell_t shell = {0};

    shell.arg_col = malloc(sizeof(char *) * 3);
    shell.arg_col[0] = "A=1";
    shell.arg_col[1] = "BAD*VAR";
    shell.arg_col[2] = NULL;
    cr_assert_eq(var_declared(&shell, 0), 0);
    cr_assert_eq(var_declared(&shell, 1), 84);
    free(shell.arg_col);
}

Test(variables, var_declared_rejects_missing_equals)
{
    shell_t shell = {0};

    shell.arg_col = malloc(sizeof(char *) * 2);
    shell.arg_col[0] = "A1";
    shell.arg_col[1] = NULL;
    cr_assert_eq(var_declared(&shell, 0), 84);
    free(shell.arg_col);
}

Test(variables, unset_builtin_too_few_arguments)
{
    shell_t shell = {0};

    shell.arg_col = malloc(sizeof(char *) * 2);
    shell.arg_col[0] = "unset";
    shell.arg_col[1] = NULL;
    cr_redirect_stderr();
    cr_assert_eq(unset_builtin(&shell), 0);
    cr_assert_stderr_eq_str("unset: Not enough arguments.\n");
    free(shell.arg_col);
}

Test(temp_var, apply_temp_variables_and_restore_env)
{
    shell_t shell = {0};
    char *saved_values[2] = {NULL, NULL};
    char *var_names[2] = {NULL, NULL};

    shell.arg_col = malloc(sizeof(char *) * 2);
    shell.arg_col[0] = "A=2";
    shell.arg_col[1] = NULL;
    shell.copy_env = malloc(sizeof(char *) * 2);
    shell.copy_env[0] = my_strdup("A=1");
    shell.copy_env[1] = NULL;
    apply_temp_variables(&shell, saved_values, var_names, 1);
    cr_assert_str_eq(shell.copy_env[0], "A=2");
    restore_env(&shell, saved_values, var_names, 1);
    cr_assert_str_eq(shell.copy_env[0], "A=1");
    free(shell.copy_env[0]);
    free(shell.copy_env);
    free(shell.arg_col);
}

Test(temp_var, exec_with_new_args_returns_when_no_extra_arguments)
{
    shell_t shell = {0};

    shell.arg_col = malloc(sizeof(char *) * 2);
    shell.arg_col[0] = "A=1";
    shell.arg_col[1] = NULL;
    exec_with_new_args(&shell, 1);
    free(shell.arg_col);
}

Test(temp_var, restore_env_removes_value_when_saved_missing)
{
    shell_t shell = {0};
    char *saved_values[2] = {NULL, NULL};
    char *var_names[2] = {NULL, NULL};

    shell.copy_env = malloc(sizeof(char *) * 2);
    shell.copy_env[0] = my_strdup("A=1");
    shell.copy_env[1] = NULL;
    var_names[0] = my_strdup("A");
    restore_env(&shell, saved_values, var_names, 1);
    cr_assert_null(shell.copy_env[0]);
    free(shell.copy_env);
}

Test(temp_var, local_and_cmd_restores_environment_after_failed_command)
{
    shell_t shell = {0};

    shell.arg_col = malloc(sizeof(char *) * 3);
    shell.arg_col[0] = "A=1";
    shell.arg_col[1] = "/notfound";
    shell.arg_col[2] = NULL;
    shell.copy_env = NULL;
    shell.local_env = NULL;
    cr_redirect_stderr();
    handle_local_var(&shell);
    cr_assert_stderr_eq_str("/notfound: Command not found.\n");
    free(shell.arg_col);
}

Test(wh_utils, check_if_builtin_and_where_prints_path)
{
    shell_t shell = {0};

    cr_assert_eq(check_if_builtin("cd"), 1);
    cr_assert_eq(check_if_builtin("nonbuiltin"), 0);
    shell.arg_col = malloc(sizeof(char *) * 2);
    shell.copy_env = malloc(sizeof(char *) * 2);
    shell.copy_env[0] = "PATH=/bin";
    shell.copy_env[1] = NULL;
    shell.aliases = NULL;
    cr_redirect_stdout();
    process_where_command(&shell, "ls");
    cr_assert_stdout_eq_str("/bin/ls\n");
    free(shell.copy_env);
    free(shell.arg_col);
}

Test(wh_utils, exec_where_too_few_arguments)
{
    shell_t shell = {0};

    shell.arg_col = malloc(sizeof(char *) * 2);
    shell.arg_col[0] = "where";
    shell.arg_col[1] = NULL;
    cr_redirect_stderr();
    exec_where(&shell);
    cr_assert_stderr_eq_str("where: Too few arguments.\n");
    free(shell.arg_col);
}

Test(wh_utils, process_which_command_prints_alias_when_defined)
{
    shell_t shell = {0};
    alias_t *alias = malloc(sizeof(alias_t));

    alias->name = my_strdup("ls");
    alias->command = my_strdup("ls -la");
    alias->next = NULL;
    shell.aliases = alias;
    shell.copy_env = NULL;
    cr_redirect_stdout();
    process_which_command(&shell, "ls");
    cr_assert_stdout_eq_str("ls: aliased to ls -la\n");
    free(alias->name);
    free(alias->command);
    free(alias);
}

Test(wh_utils, process_which_command_prints_builtin_when_defined)
{
    shell_t shell = {0};

    shell.copy_env = NULL;
    cr_redirect_stdout();
    process_which_command(&shell, "cd");
    cr_assert_stdout_eq_str("cd: shell built-in command.\n");
}

Test(wh_utils, process_which_command_prints_not_found)
{
    shell_t shell = {0};

    shell.copy_env = malloc(sizeof(char *) * 2);
    shell.copy_env[0] = my_strdup("PATH=/bin");
    shell.copy_env[1] = NULL;
    cr_redirect_stdout();
    process_which_command(&shell, "command_that_does_not_exist");
    cr_assert_stdout_eq_str(
        "command_that_does_not_exist: Command not found.\n");
    free(shell.copy_env[0]);
    free(shell.copy_env);
}

Test(wh_utils, exec_which_too_few_arguments)
{
    shell_t shell = {0};

    shell.arg_col = malloc(sizeof(char *) * 2);
    shell.arg_col[0] = "which";
    shell.arg_col[1] = NULL;
    cr_redirect_stderr();
    exec_which(&shell);
    cr_assert_stderr_eq_str("which: Too few arguments.\n");
    free(shell.arg_col);
}
