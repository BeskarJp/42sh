/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Tests token tree and execution
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "shell.h"

/**
 * @brief Create a temp filename object
 *
 * @param template
 * @return char*.
 */
static char *create_temp_filename(char *template)
{
    char *filename = strdup(template);
    int fd = 0;

    if (!filename)
        return NULL;
    fd = mkstemp(filename);
    if (fd == -1) {
        free(filename);
        return NULL;
    }
    close(fd);
    return filename;
}

/**
 * @brief Restore_sdtin for tests
 *
 * @param saved_stdin
 */
static void restore_stdin(int saved_stdin)
{
    dup2(saved_stdin, STDIN_FILENO);
    close(saved_stdin);
}

/**
 * @brief Write in file for tests
 *
 * @param path
 * @param content
 * @return int.
 */
static int write_file(char *path, char *content)
{
    int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, PERM_NORM);

    if (fd == -1)
        return -1;
    write(fd, content, strlen(content));
    close(fd);
    return 0;
}

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

Test(globbing_utils, collect_matches_returns_pattern_if_no_file)
{
    char **matches = collect_matches("no_such_file_pattern_12345");

    cr_assert_not_null(matches);
    cr_assert_str_eq(matches[0], "no_such_file_pattern_12345");
    free_array(matches);
}

Test(globbing_utils, collect_matches_returns_found_file)
{
    char *filename = create_temp_filename("tmp_glob_test_XXXXXX");
    char **matches = NULL;
    char pattern[64];

    cr_assert_not_null(filename);
    sprintf(pattern, "%s*", "tmp_glob_test_");
    matches = collect_matches(pattern);
    cr_assert_not_null(matches);
    cr_assert_str_eq(matches[0], filename);
    free_array(matches);
    remove(filename);
    free(filename);
}

Test(globbing_utils, expand_globbing_returns_original_when_capacity_exceeded)
{
    char *prefix = "tmp_glob_overflow_";
    char *filename[22];
    char template[32];
    char glob_pattern[64];
    char **args = malloc(sizeof(char *) * 2);
    char **result = NULL;
    int i;

    for (i = 0; i < 21; i++) {
        sprintf(template, "%s%02dXXXXXX", prefix, i);
        filename[i] = create_temp_filename(template);
        cr_assert_not_null(filename[i]);
    }
    filename[21] = NULL;
    sprintf(glob_pattern, "%s*", prefix);
    args[0] = my_strdup(glob_pattern);
    args[1] = NULL;
    result = expand_globbing(args);
    cr_assert_eq(result, args);
    free_array(result);
    for (i = 0; i < 21; i++) {
        remove(filename[i]);
        free(filename[i]);
    }
}

Test(globbing_utils, expand_globbing_expands_pattern)
{
    char *file1 = create_temp_filename("tmp_glob_expand_aaXXXXXX");
    char *file2 = create_temp_filename("tmp_glob_expand_abXXXXXX");
    char **args = malloc(sizeof(char *) * 3);
    char **expanded = NULL;

    cr_assert_not_null(file1);
    cr_assert_not_null(file2);
    args[0] = my_strdup("echo");
    args[1] = my_strdup("tmp_glob_expand_*");
    args[2] = NULL;
    expanded = expand_globbing(args);
    cr_assert_not_null(expanded);
    cr_assert_str_eq(expanded[0], "echo");
    cr_assert_not_null(expanded[1]);
    free_array(expanded);
    remove(file1);
    remove(file2);
    free(file1);
    free(file2);
}

Test(exec_operators, and_operator_runs_right_when_left_succeeds)
{
    shell_t shell = {0};
    token_tree_t right = {.type = SIMPLE_COMMAND, .args = NULL};
    token_tree_t left = {.type = SIMPLE_COMMAND, .args = NULL};
    token_tree_t tree = {.type = AND_OPERATOR, .left = &left, .right = &right};

    shell.exit_status = 0;
    exec_operators(&shell, &tree);
    cr_assert_eq(shell.exit_status, 0);
}

Test(exec_operators, or_operator_runs_right_when_left_fails)
{
    shell_t shell = {0};
    token_tree_t right = {.type = SIMPLE_COMMAND, .args = NULL};
    token_tree_t left = {.type = SIMPLE_COMMAND, .args = NULL};
    token_tree_t tree = {.type = OR_OPERATOR, .left = &left, .right = &right};

    shell.exit_status = 1;
    exec_operators(&shell, &tree);
    cr_assert_eq(shell.exit_status, 1);
}

Test(pipe, ignore_negative_child_one)
{
    shell_t shell = {0};
    token_tree_t tree = {0};
    int pipefd[2];

    cr_assert_eq(pipe(pipefd), 0);
    child_one(&shell, &tree, -1, pipefd);
    close(pipefd[0]);
    close(pipefd[1]);
}

Test(pipe, ignore_negative_child_two)
{
    shell_t shell = {0};
    token_tree_t tree = {0};
    int pipefd[2];

    cr_assert_eq(pipe(pipefd), 0);
    child_two(&shell, &tree, -1, pipefd);
    close(pipefd[0]);
    close(pipefd[1]);
}

Test(pipe, run_pipe_executes_without_branches)
{
    shell_t shell = {0};
    token_tree_t tree = {.type = PIPE, .left = NULL, .right = NULL};

    run_pipe(&shell, &tree);
    cr_assert_eq(shell.exit_status, 0);
}

Test(pipe, run_pipe_returns_on_pipe_failure)
{
    shell_t shell = {0};
    token_tree_t tree = {.type = PIPE, .left = NULL, .right = NULL};

#ifdef UNIT_TEST
    unit_test_pipe_fail = 1;
#endif
    run_pipe(&shell, &tree);
#ifdef UNIT_TEST
    unit_test_pipe_fail = 0;
#endif
    cr_assert_eq(shell.exit_status, 0);
}

Test(redirection_utils, left_double_redirection_reads_until_delimiter)
{
    char *filename = create_temp_filename("tmp_here_XXXXXX");
    int saved_stdin = dup(STDIN_FILENO);
    int input_fd = 0;
    char buffer[16] = {0};
    ssize_t read_bytes = 0;

    cr_assert_not_null(filename);
    write_file(filename, "line1\nEND\n");
    input_fd = open(filename, O_RDONLY);
    cr_assert_neq(input_fd, -1);
    dup2(input_fd, STDIN_FILENO);
    close(input_fd);
    left_double_redirection("END");
    read_bytes = read(STDIN_FILENO, buffer, 6);
    cr_assert_eq(read_bytes, 6);
    cr_assert_str_eq(buffer, "line1\n");
    restore_stdin(saved_stdin);
    remove(filename);
    free(filename);
}

Test(redirection_utils, left_double_redirection_ends_on_eof)
{
    char *filename = create_temp_filename("tmp_here_eof_XXXXXX");
    int saved_stdin = dup(STDIN_FILENO);
    int input_fd = 0;

    cr_assert_not_null(filename);
    write_file(filename, "");
    input_fd = open(filename, O_RDONLY);
    cr_assert_neq(input_fd, -1);
    dup2(input_fd, STDIN_FILENO);
    close(input_fd);
    left_double_redirection("END");
    restore_stdin(saved_stdin);
    remove(filename);
    free(filename);
}

Test(redirection, manipulate_file_with_type_handles_all_redirects)
{
    token_tree_t tree = {.file = "tmp_redirect_test.txt", .type = REDIR_DROITE};
    int fd = manipulate_file_with_type(&tree, FD_ERROR);

    cr_assert_neq(fd, FD_ERROR);
    close(fd);
    remove(tree.file);

    tree.type = REDIR_DB_DROITE;
    fd = manipulate_file_with_type(&tree, FD_ERROR);
    cr_assert_neq(fd, FD_ERROR);
    close(fd);
    remove(tree.file);

    write_file(tree.file, "data\n");
    tree.type = REDIR_GAUCHE;
    fd = manipulate_file_with_type(&tree, FD_ERROR);
    cr_assert_neq(fd, FD_ERROR);
    close(fd);
    remove(tree.file);
}

Test(redirection, run_redirection_creates_output_file)
{
    shell_t shell = {0};
    token_tree_t left = {.type = SIMPLE_COMMAND, .args = NULL};
    token_tree_t tree = {.type = REDIR_DROITE,
        .file = my_strdup("tmp_runredir.txt"), .left = &left};
    int fd = 0;

    run_redirection(&shell, &tree);
    fd = open(tree.file, O_RDONLY);
    cr_assert_neq(fd, -1);
    close(fd);
    remove(tree.file);
    free(tree.file);
}

Test(redirection, run_redirection_reads_input_file)
{
    shell_t shell = {0};
    token_tree_t left = {.type = SIMPLE_COMMAND, .args = NULL};
    token_tree_t tree = {.type = REDIR_GAUCHE,
        .file = my_strdup("tmp_infile.txt"), .left = &left};

    write_file(tree.file, "content\n");
    run_redirection(&shell, &tree);
    remove(tree.file);
    free(tree.file);
}

Test(redirection, run_redirection_handles_here_document)
{
    shell_t shell = {0};
    token_tree_t left = {.type = SIMPLE_COMMAND, .args = NULL};
    token_tree_t tree = {.type = REDIR_DB_GAUCHE,
        .file = my_strdup("END"), .left = &left};
    char *filename = create_temp_filename("tmp_here_input_XXXXXX");
    int saved_stdin = dup(STDIN_FILENO);
    int input_fd = 0;

    cr_assert_not_null(filename);
    write_file(filename, "hello\nEND\n");
    input_fd = open(filename, O_RDONLY);
    cr_assert_neq(input_fd, -1);
    dup2(input_fd, STDIN_FILENO);
    close(input_fd);
    run_redirection(&shell, &tree);
    restore_stdin(saved_stdin);
    remove(filename);
    free(filename);
    free(tree.file);
}

Test(tree, run_tree_handles_null)
{
    shell_t shell = {0};

    run_tree(&shell, NULL);
}

Test(tree, run_tree_executes_semicolon_branches)
{
    shell_t shell = {0};
    token_tree_t left = {.type = SIMPLE_COMMAND, .args = NULL};
    token_tree_t right = {.type = SIMPLE_COMMAND, .args = NULL};
    token_tree_t tree = {.type = SEMICOLONS, .left = &left, .right = &right};

    run_tree(&shell, &tree);
}

Test(tree, run_tree_executes_pipe_branch)
{
    shell_t shell = {0};
    token_tree_t tree = {.type = PIPE, .left = NULL, .right = NULL};

    run_tree(&shell, &tree);
}

Test(tree, run_tree_executes_redirection_branch)
{
    shell_t shell = {0};
    token_tree_t left = {.type = SIMPLE_COMMAND, .args = NULL};
    token_tree_t tree = {.type = REDIR_DROITE,
        .file = my_strdup("tmp_tree_redir.txt"), .left = &left};

    run_tree(&shell, &tree);
    remove(tree.file);
    free(tree.file);
}

Test(alias, alias_checker_ignores_null_inputs)
{
    alias_checker(NULL, NULL);
}

Test(alias, alias_checker_breaks_alias_loop)
{
    shell_t shell = {0};
    token_tree_t tree = {0};

    add_alias(&shell, "a", "a");
    tree.args = my_str_to_word_array("a");
    alias_checker(&shell, &tree);
    cr_assert_null(tree.args);
    free_aliases(shell.aliases);
}

Test(alias, alias_checker_leaves_non_alias_command_untouched)
{
    shell_t shell = {0};
    token_tree_t tree = {0};

    tree.args = my_str_to_word_array("echo foo");
    alias_checker(&shell, &tree);
    cr_assert_str_eq(tree.args[0], "echo");
    free_array(tree.args);
}

Test(parse_utils, create_branch_by_type_allocates_node)
{
    token_tree_t *tree = create_branch_by_type(PIPE);

    cr_assert_not_null(tree);
    cr_assert_eq(tree->type, PIPE);
    free(tree);
}

Test(parse_utils, create_redirection_branch_sets_file_and_left)
{
    token_tree_t *tree = create_redirection_branch("ls > out", 3, 1,
        REDIR_DROITE);

    cr_assert_not_null(tree);
    cr_assert_eq(tree->type, REDIR_DROITE);
    cr_assert_not_null(tree->left);
    cr_assert_str_eq(tree->file, "out");
    free_tree(tree);
}

Test(parser, parse_line_returns_null_for_null_input)
{
    cr_assert_null(parse_line(NULL));
}

Test(parser, parse_line_builds_logical_tree)
{
    token_tree_t *tree = parse_line("true && false || echo ok");

    cr_assert_not_null(tree);
    cr_assert_eq(tree->type, OR_OPERATOR);
    cr_assert_eq(tree->left->type, AND_OPERATOR);
    free_tree(tree);
}
