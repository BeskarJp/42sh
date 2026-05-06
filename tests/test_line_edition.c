/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Tests line edition
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "shell.h"

static int restore_stdin(int saved_stdin)
{
    if (saved_stdin < 0)
        return -1;
    dup2(saved_stdin, STDIN_FILENO);
    close(saved_stdin);
    return 0;
}

Test(line_edition, handle_ctrl_d_returns_true_and_writes_newline)
{
    line_edition_t le = {0};

    le.key = CTRL_D;
    cr_redirect_stdout();
    cr_assert_eq(handle_ctrl_d(&le), 1);
    cr_assert_stdout_eq_str("\n");
}

Test(line_edition, handle_ctrl_d_returns_false_for_other_key)
{
    line_edition_t le = {0};

    le.key = 'a';
    cr_assert_eq(handle_ctrl_d(&le), 0);
}

Test(line_edition, handle_backspace_deletes_last_character)
{
    line_edition_t le = {0};

    le.key = BACKSPACE;
    le.i = 3;
    le.entire_line = strdup("abc");
    cr_redirect_stdout();
    cr_assert_eq(handle_backspace(&le), 1);
    cr_assert_eq(le.i, 2);
    cr_assert_str_eq(le.entire_line, "ab");
    cr_assert_stdout_eq_str("\b \b");
    free(le.entire_line);
}

Test(line_edition, handle_backspace_does_nothing_when_empty)
{
    line_edition_t le = {0};

    le.key = BACKSPACE;
    le.i = 0;
    le.entire_line = strdup("");
    cr_redirect_stdout();
    cr_assert_eq(handle_backspace(&le), 1);
    cr_assert_stdout_eq_str("");
    free(le.entire_line);
}

Test(line_edition, handle_up_shows_most_recent_history_entry)
{
    shell_t shell = {0};
    line_edition_t le = {0};
    history_t command1 = {1, "first", NULL, NULL};
    history_t command2 = {2, "second", NULL, NULL};
    history_t command3 = {3, "third", NULL, NULL};

    command1.next = &command2;
    command2.next = &command3;
    shell.history = &command1;
    shell.le = &le;
    cr_redirect_stdout();
    handle_up(&shell);
    cr_assert_str_eq(shell.le->entire_line, "third");
    cr_assert_eq(shell.le->i, 5);
    cr_assert_stdout_eq_str("third");
    free(shell.le->entire_line);
}

Test(line_edition, handle_up_moves_to_previous_history_entry)
{
    shell_t shell = {0};
    line_edition_t le = {0};
    history_t command1 = {1, "first", NULL, NULL};
    history_t command2 = {2, "second", NULL, NULL};
    history_t command3 = {3, "third", NULL, NULL};

    command1.next = &command2;
    command2.next = &command3;
    shell.history = &command1;
    shell.le = &le;
    handle_up(&shell);
    cr_redirect_stdout();
    handle_up(&shell);
    cr_assert_str_eq(shell.le->entire_line, "second");
    cr_assert_eq(shell.le->i, 6);
    free(shell.le->entire_line);
}

Test(line_edition, handle_down_moves_to_next_history_entry)
{
    shell_t shell = {0};
    line_edition_t le = {0};
    history_t command1 = {1, "first", NULL, NULL};
    history_t command2 = {2, "second", NULL, NULL};
    history_t command3 = {3, "third", NULL, NULL};

    command1.next = &command2;
    command2.next = &command3;
    shell.history = &command1;
    shell.le = &le;
    shell.le->current = &command2;
    shell.le->entire_line = strdup("second");
    shell.le->i = 6;
    cr_redirect_stdout();
    handle_down(&shell);
    cr_assert_str_eq(shell.le->entire_line, "third");
    cr_assert_eq(shell.le->i, 5);
    cr_assert_stdout_eq_str("\b \b\b \b\b \b\b \b\b \b\b \bthird");
    free(shell.le->entire_line);
}

Test(line_edition, check_arrows_dispatches_to_handle_right)
{
    shell_t shell = {0};
    line_edition_t le = {0};

    le.arrow_key = malloc(3);
    le.arrow_key[1] = 'C';
    le.entire_line = strdup("abc");
    le.i = 0;
    shell.le = &le;
    cr_redirect_stdout();
    check_arrows(&shell);
    cr_assert_eq(le.i, 1);
    cr_assert_stdout_eq_str("\033[C");
    free(le.entire_line);
    free(le.arrow_key);
}

Test(line_edition, handle_keys_reads_escape_sequence_and_invokes_arrow)
{
    shell_t shell = {0};
    line_edition_t le = {0};
    history_t command = {1, "history", NULL, NULL};
    int saved_stdin = dup(STDIN_FILENO);
    int pipe_fds[2];

    shell.history = &command;
    shell.le = &le;
    le.arrow_key = malloc(3);
    le.key = ESC;
    pipe(pipe_fds);
    write(pipe_fds[1], "[A", 2);
    close(pipe_fds[1]);
    dup2(pipe_fds[0], STDIN_FILENO);
    close(pipe_fds[0]);
    cr_redirect_stdout();
    cr_assert_eq(handle_keys(&shell), 1);
    cr_assert_str_eq(shell.le->entire_line, "history");
    cr_assert_stdout_eq_str("history");
    free(shell.le->entire_line);
    free(shell.le->arrow_key);
    restore_stdin(saved_stdin);
}
