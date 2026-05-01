/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Tests token tree and execution
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "shell.h"

Test(parsing, clear_string_basic)
{
    char *str = "   ls -la   ";
    char *result = clear_string(str, 0, strlen(str));

    cr_assert_str_eq(result, "ls -la");
    free(result);
}

Test(parsing, parse_simple_command)
{
    char *command = "ls -l";
    token_tree_t *tree = parse_line(command);

    cr_assert_not_null(tree);
    cr_assert_eq(tree->type, SIMPLE_COMMAND);
    cr_assert_str_eq(tree->args[0], "ls");
    free_tree(tree);
}

Test(parsing, parse_pipe)
{
    char *command = "ls | grep test";
    token_tree_t *tree = parse_line(command);

    cr_assert_not_null(tree);
    cr_assert_eq(tree->type, PIPE);
    cr_assert_eq(tree->left->type, SIMPLE_COMMAND);
    cr_assert_eq(tree->right->type, SIMPLE_COMMAND);
    free_tree(tree);
}

Test(parsing, parse_logical_complex)
{
    char *command = "ls && cat file || echo fail";
    token_tree_t *tree = parse_line(command);

    cr_assert_not_null(tree);
    cr_assert_eq(tree->type, OR_OPERATOR);
    cr_assert_eq(tree->left->type, AND_OPERATOR);
    free_tree(tree);
}

Test(parsing, parse_operators_priority)
{
    token_tree_t *tree = parse_line("ls && cat file || echo error");

    cr_assert_eq(tree->type, OR_OPERATOR);
    cr_assert_eq(tree->left->type, AND_OPERATOR);
    free_tree(tree);
}


Test(globbing, pattern_detection)
{
    cr_assert_eq(is_globbing_pattern("plain"), 0);
    cr_assert_eq(is_globbing_pattern("file*"), 1);
    cr_assert_eq(is_globbing_pattern("what?"), 1);
    cr_assert_eq(is_globbing_pattern("x[yz]"), 1);
}

Test(globbing, count_args_and_append_match)
{
    char *args[] = {"one", "two", NULL};
    char *exp_buf[1];
    char **exp = exp_buf;
    int count = 0;
    int cap = 1;

    cr_assert_eq(count_args(args), 2);
    cr_assert_eq(append_match(&exp, &count, &cap, "one"), 0);
    cr_assert_eq(count, 1);
    cr_assert_eq(append_match(&exp, &count, &cap, "two"), -1);
}

Test(globbing, expand_globbing_without_patterns)
{
    char **args = malloc(sizeof(char *) * 3);
    char **expanded;

    args[0] = my_strdup("echo");
    args[1] = my_strdup("test");
    args[2] = NULL;
    expanded = expand_globbing(args);

    cr_assert_not_null(expanded);
    cr_assert_str_eq(expanded[0], "echo");
    free_array(expanded);
}

Test(pipe, child_one_and_two_nonchild)
{
    shell_t shell = {0};
    token_tree_t tree = {0};
    int pipefd[2];

    cr_assert_eq(pipe(pipefd), 0);
    child_one(&shell, &tree, 5, pipefd);
    child_two(&shell, &tree, 5, pipefd);
    close(pipefd[0]);
    close(pipefd[1]);
}

Test(pipe, run_pipe_noop)
{
    shell_t shell = {0};
    token_tree_t tree = {.type = PIPE, .left = NULL, .right = NULL};

    run_pipe(&shell, &tree);
    cr_assert_eq(shell.exit_status, 0);
}

Test(redirection, manipulate_file_with_type_create_truncate)
{
    token_tree_t tree = {.type = REDIR_DROITE, .file = "tmp_redirect.txt"};
    int fd = manipulate_file_with_type(&tree, FD_ERROR);

    cr_assert_neq(fd, FD_ERROR);
    close(fd);
    remove("tmp_redirect.txt");
}

Test(tree, run_simple_command_null_args)
{
    shell_t shell = {0};
    token_tree_t tree = {.type = SIMPLE_COMMAND, .args = NULL};

    run_simple_command(&shell, &tree);
}

Test(alias, change_tree_command_to_alias)
{
    char *aliases_buffer[] = {"ls", "-la", NULL};
    char *argv_tree[] = {"echo", "foo", NULL};
    char **result = change_tree_command_to_alias(aliases_buffer, argv_tree);

    cr_assert_str_eq(result[0], "ls");
    cr_assert_str_eq(result[1], "-la");
    cr_assert_str_eq(result[2], "foo");
    free_array(result);
}

Test(alias, apply_alias_substitution_success)
{
    alias_t correlation = {.command = "ls -la"};
    token_tree_t tree = {.args = NULL};

    tree.args = my_str_to_word_array("echo foo");
    cr_assert_eq(apply_alias_substitution(&tree, &correlation), 1);
    cr_assert_str_eq(tree.args[0], "ls");
    cr_assert_str_eq(tree.args[1], "-la");
    cr_assert_str_eq(tree.args[2], "foo");
    free_array(tree.args);
}

Test(parser, parse_redirections_and_structure)
{
    token_tree_t *tree = parse_line("ls > output.txt");

    cr_assert_not_null(tree);
    cr_assert_eq(tree->type, REDIR_DROITE);
    cr_assert_str_eq(tree->file, "output.txt");
    free_tree(tree);
    tree = parse_line("ls >> output.txt");
    cr_assert_eq(tree->type, REDIR_DB_DROITE);
    free_tree(tree);
    tree = parse_line("cat < input.txt");
    cr_assert_eq(tree->type, REDIR_GAUCHE);
    free_tree(tree);
    tree = parse_line("cat << LIMIT");
    cr_assert_eq(tree->type, REDIR_DB_GAUCHE);
    free_tree(tree);
}

Test(parser, parse_pipe_and_logical)
{
    token_tree_t *tree = parse_line("ls | grep foo");

    cr_assert_eq(tree->type, PIPE);
    free_tree(tree);
    tree = parse_line("true && false || echo ok");
    cr_assert_eq(tree->type, OR_OPERATOR);
    cr_assert_eq(tree->left->type, AND_OPERATOR);
    free_tree(tree);
    tree = parse_line("echo a ; echo b");
    cr_assert_eq(tree->type, SEMICOLONS);
    free_tree(tree);
}
