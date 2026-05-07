/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Tests utilities
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "shell.h"

static token_tree_t *stub_parse_node(char *line)
{
    token_tree_t *node = create_branch_by_type(SIMPLE_COMMAND);

    if (!node)
        return NULL;
    node->file = my_strdup(line);
    return node;
}

Test(utils, clear_string_trims_spaces)
{
    char *result = clear_string("  hello world  ", 0, 15);

    cr_assert_not_null(result);
    cr_assert_str_eq(result, "hello world");
    free(result);
}

Test(utils, clear_string_null_returns_null)
{
    cr_assert_null(clear_string(NULL, 0, 0));
}

Test(utils, create_branch_by_type_initializes_node)
{
    token_tree_t *node = create_branch_by_type(PIPE);

    cr_assert_not_null(node);
    cr_assert_eq(node->type, PIPE);
    cr_assert_null(node->args);
    cr_assert_null(node->file);
    cr_assert_null(node->left);
    cr_assert_null(node->right);
    free(node);
}

Test(utils, cut_branch_splits_input_and_builds_subtrees)
{
    struct_parse_t data = {0};
    token_tree_t *tree = NULL;

    data.type = AND_OPERATOR;
    data.count_stopped = 2;
    data.end_line = 2;
    data.left_function = stub_parse_node;
    data.right_function = stub_parse_node;
    tree = cut_branch("a && b", &data);
    cr_assert_not_null(tree);
    cr_assert_eq(tree->type, AND_OPERATOR);
    cr_assert_not_null(tree->left);
    cr_assert_not_null(tree->right);
    cr_assert_str_eq(tree->left->file, "a");
    cr_assert_str_eq(tree->right->file, "b");
    free_tree(tree);
}

Test(free, free_array_handles_null)
{
    free_array(NULL);
    cr_assert(true);
}

Test(free, free_array_frees_strings)
{
    char **array = malloc(sizeof(char *) * 2);

    array[0] = my_strdup("hello");
    array[1] = NULL;
    free_array(array);
    cr_assert(true);
}

Test(free, free_aliases_releases_list)
{
    alias_t *first = malloc(sizeof(alias_t));
    alias_t *second = malloc(sizeof(alias_t));

    first->name = my_strdup("ls");
    first->command = my_strdup("ls -la");
    first->next = second;
    second->name = my_strdup("ps");
    second->command = my_strdup("ps aux");
    second->next = NULL;
    free_aliases(first);
    cr_assert(true);
}

Test(free, free_history_releases_list)
{
    history_t *first = malloc(sizeof(history_t));
    history_t *second = malloc(sizeof(history_t));

    first->command = my_strdup("echo hello");
    first->time = my_strdup("12:00");
    first->next = second;
    second->command = my_strdup("pwd");
    second->time = my_strdup("12:01");
    second->next = NULL;
    free_history(first);
    cr_assert(true);
}

Test(free, free_tree_releases_recursive_tree)
{
    token_tree_t *root = create_branch_by_type(PIPE);

    root->args = malloc(sizeof(char *) * 2);
    root->args[0] = my_strdup("arg1");
    root->args[1] = NULL;
    root->file = my_strdup("out.txt");
    root->left = stub_parse_node("left");
    root->right = stub_parse_node("right");
    free_tree(root);
    cr_assert(true);
}

Test(error, handle_sigint_prints_prompt)
{
    cr_redirect_stdout();
    handle_sigint(0);
    cr_assert_stdout_eq_str(
        "\n\033[1;95mCtrl + C prompt (push entry for shell prompt)"
        "\033[0m $> ");
}

Test(error, check_execve_output_error_permission_denied)
{
    cr_redirect_stdout();
    errno = EACCES;
    check_execve_output_error("/tmp/test");
    cr_assert_stdout_eq_str("/tmp/test: Permission denied.\n");
}

Test(error, check_execve_output_error_exec_format)
{
    cr_redirect_stdout();
    errno = ENOEXEC;
    check_execve_output_error("/tmp/test");
    cr_assert_stdout_eq_str(
        "/tmp/test: Exec format error. Binary file not executable.\n");
}

Test(error, check_strsignal_prints_signal_description)
{
    cr_redirect_stderr();
    check_strsignal(SIGFPE);
    cr_assert_stderr_eq_str("Floating exception\n");
}
