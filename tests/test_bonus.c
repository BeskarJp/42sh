/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Tests bonus
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "shell.h"

Test(exec_echo, no_arguments)
{
    shell_t shell = {0};

    shell.arg_col = malloc(sizeof(char *) * 2);
    shell.arg_col[0] = my_strdup("echo");
    shell.arg_col[1] = NULL;
    shell.exit_status = 42;
    cr_redirect_stdout();
    exec_echo(&shell);
    cr_assert_stdout_eq_str("\n");
    cr_assert_eq(shell.exit_status, 0);
    free(shell.arg_col[0]);
    free(shell.arg_col);
}

Test(exec_echo, one_argument)
{
    shell_t shell = {0};

    shell.arg_col = malloc(sizeof(char *) * 3);
    shell.arg_col[0] = my_strdup("echo");
    shell.arg_col[1] = my_strdup("hello");
    shell.arg_col[2] = NULL;
    shell.exit_status = 42;
    cr_redirect_stdout();
    exec_echo(&shell);
    cr_assert_stdout_eq_str("hello\n");
    cr_assert_eq(shell.exit_status, 0);
    free(shell.arg_col[0]);
    free(shell.arg_col[1]);
    free(shell.arg_col);
}

Test(exec_echo, multiple_arguments)
{
    shell_t shell = {0};

    shell.arg_col = malloc(sizeof(char *) * 4);
    shell.arg_col[0] = my_strdup("echo");
    shell.arg_col[1] = my_strdup("hello");
    shell.arg_col[2] = my_strdup("world");
    shell.arg_col[3] = NULL;
    shell.exit_status = 42;
    cr_redirect_stdout();
    exec_echo(&shell);
    cr_assert_stdout_eq_str("hello world\n");
    cr_assert_eq(shell.exit_status, 0);
    free(shell.arg_col[0]);
    free(shell.arg_col[1]);
    free(shell.arg_col[2]);
    free(shell.arg_col);
}

Test(exec_echo, exit_status_variable)
{
    shell_t shell = {0};

    shell.arg_col = malloc(sizeof(char *) * 3);
    shell.arg_col[0] = my_strdup("echo");
    shell.arg_col[1] = my_strdup("$?");
    shell.arg_col[2] = NULL;
    shell.exit_status = 42;
    cr_redirect_stdout();
    exec_echo(&shell);
    cr_assert_stdout_eq_str("42\n");
    cr_assert_eq(shell.exit_status, 0);
    free(shell.arg_col[0]);
    free(shell.arg_col[1]);
    free(shell.arg_col);
}

Test(exec_echo, mixed_arguments)
{
    shell_t shell = {0};

    shell.arg_col = malloc(sizeof(char *) * 5);
    shell.arg_col[0] = my_strdup("echo");
    shell.arg_col[1] = my_strdup("hello");
    shell.arg_col[2] = my_strdup("$?");
    shell.arg_col[3] = my_strdup("world");
    shell.arg_col[4] = NULL;
    shell.exit_status = 42;
    cr_redirect_stdout();
    exec_echo(&shell);
    cr_assert_stdout_eq_str("hello 42 world\n");
    cr_assert_eq(shell.exit_status, 0);
    free(shell.arg_col[0]);
    free(shell.arg_col[1]);
    free(shell.arg_col[2]);
    free(shell.arg_col[3]);
    free(shell.arg_col);
}

Test(handle_emac_input, insert_char)
{
    emacs_t editor = {0};

    editor.file_buffer = malloc(4096);
    my_strcpy(editor.file_buffer, "hello");
    editor.text_len = 5;
    editor.cursor_in_file = 5;
    editor.running = 1;
    handle_emac_input('a', &editor);
    cr_assert_str_eq(editor.file_buffer, "helloa");
    cr_assert_eq(editor.cursor_in_file, 6);
    cr_assert_eq(editor.text_len, 6);
    free(editor.file_buffer);
}

Test(handle_emac_input, delete_char)
{
    emacs_t editor = {0};

    editor.file_buffer = malloc(4096);
    my_strcpy(editor.file_buffer, "hello!");
    editor.text_len = 6;
    editor.cursor_in_file = 6;
    editor.running = 1;
    handle_emac_input(127, &editor);
    cr_assert_str_eq(editor.file_buffer, "hello");
    cr_assert_eq(editor.cursor_in_file, 5);
    cr_assert_eq(editor.text_len, 5);
    free(editor.file_buffer);
}

Test(handle_emac_input, quit)
{
    emacs_t editor = {0};

    editor.running = 1;
    handle_emac_input(24, &editor);
    cr_assert_eq(editor.running, 0);
}

Test(move_vertical, move_up)
{
    emacs_t editor = {0};

    editor.file_buffer = my_strdup("hello\nworld");
    editor.text_len = 11;
    editor.cursor_in_file = 8;
    move_vertical(&editor, KEY_UP);
    cr_assert_eq(editor.cursor_in_file, 2);
    free(editor.file_buffer);
}

Test(bonus_builtin_ascii_art_cactus, display_cactus)
{
    cr_redirect_stdout();
    bonus_builtin_ascii_art_cactus();
}

Test(user_of_shell, username_present)
{
    char *env[] = {"USERNAME=testuser", "HOME=/home/user", NULL};

    cr_assert_str_eq(user_of_shell(env), "testuser");
}

Test(user_of_shell, username_not_present)
{
    char *env[] = {"HOME=/home/user", NULL};

    cr_assert_str_eq(user_of_shell(env), "Blud");
}

Test(user_of_shell, null_env)
{
    cr_assert_str_eq(user_of_shell(NULL), "Blud");
}

Test(display_line_in_file, null_buffer)
{
    cr_redirect_stdout();
    display_line_in_file(NULL, 0);
}

Test(display_line_in_file, empty_buffer)
{
    cr_redirect_stdout();
    display_line_in_file("", 0);
}

Test(print_header, display_header)
{
    shell_t shell = {0};
    char *env[] = {"USERNAME=testuser", NULL};

    shell.copy_env = env;
    cr_redirect_stdout();
    print_header(&shell);
}

Test(print_explication_shell, display_notions)
{
    cr_redirect_stdout();
    print_explication_shell();
}

Test(print_more_of_command, known_command)
{
    cr_redirect_stdout();
    print_more_of_command("ls");
}

Test(print_more_of_command, unknown_command)
{
    cr_redirect_stdout();
    print_more_of_command("unknown");
}

Test(explain_command_line, simple_command)
{
    cr_redirect_stdout();
    explain_command_line("ls");
}

Test(explain_command_line, invalid_command)
{
    cr_redirect_stdout();
    explain_command_line("");
}

Test(handle_input, valid_command)
{
    cr_redirect_stdout();
    handle_input("help");
}

Test(handle_input, invalid_command)
{
    cr_redirect_stdout();
    handle_input("invalid");
}

Test(exec_emac, no_file_argument)
{
    shell_t shell = {0};

    shell.arg_col = malloc(sizeof(char *) * 2);
    shell.arg_col[0] = my_strdup("emac");
    shell.arg_col[1] = NULL;
    cr_redirect_stderr();
    cr_assert_eq(exec_emac(&shell), 1);
    cr_assert_stderr_eq_str("emac: Need file\n");
    free(shell.arg_col[0]);
    free(shell.arg_col);
}

Test(load_emac_file, non_existent_file)
{
    char *buffer = load_emac_file("/non/existent/file");

    cr_assert_not_null(buffer);
    cr_assert_str_eq(buffer, "");
    free(buffer);
}

Test(save_emac_file, save_to_file)
{
    emacs_t editor = {0};
    FILE *f;
    char buf[20];

    editor.pathline = "/tmp/test_emac_file";
    editor.file_buffer = my_strdup("test content");
    editor.text_len = 12;
    save_emac_file(&editor);
    f = fopen("/tmp/test_emac_file", "r");
    cr_assert_not_null(f);
    fread(buf, 1, 20, f);
    buf[12] = '\0';
    cr_assert_str_eq(buf, "test content");
    fclose(f);
    remove("/tmp/test_emac_file");
    free(editor.file_buffer);
}

Test(start_claude, start_and_exit)
{
    shell_t shell = {0};
    int pipefd[2];
    char *env[] = {"USERNAME=testuser", NULL};

    shell.copy_env = env;
    pipe(pipefd);
    write(pipefd[1], "exit\n", 5);
    close(pipefd[1]);
    dup2(pipefd[0], STDIN_FILENO);
    close(pipefd[0]);
    cr_redirect_stdout();
    start_claude(&shell);
}
