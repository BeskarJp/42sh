/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** reproduce the behavior of arrow keys
*/

#include "shell.h"

/**
 * @brief Return the last command in history
 * starting from the most recent to the oldest
 *
 * @param tmp Head of the history linked list
 */
static history_t *get_last(history_t *tmp)
{
    while (tmp->next)
        tmp = tmp->next;
    return tmp;
}

/**
 * @brief Return the command just before current in history
 * starting from the oldest to the most recent
 *
 * @param tmp Head of the history linked list
 * @param shell Shell structure containing line edition data
 */
static history_t *get_prev(history_t *tmp, shell_t *shell)
{
    while (tmp->next && tmp->next != shell->le->current)
        tmp = tmp->next;
    return tmp;
}

/**
 * @brief Reproduce the up arrow from tcsh shell, naviguate throught
 * the history list and print it starting from the most recent to the oldest
 *
 * @param shell Shell structure containing line edition data
 */
void handle_up(shell_t *shell)
{
    history_t *tmp = shell->history;

    if (!shell->history)
        return;
    if (shell->le->current == NULL)
        shell->le->current = get_last(tmp);
    if (shell->le->current != NULL)
        shell->le->current = get_prev(tmp, shell);
    while (shell->le->i > 0) {
        write(STDOUT_FILENO, "\b \b", 3);
        shell->le->i--;
    }
    free(shell->le->entire_line);
    shell->le->entire_line = strdup(shell->le->current->command);
    write(STDOUT_FILENO, shell->le->current->command,
        strlen(shell->le->current->command));
    shell->le->i = strlen(shell->le->current->command);
    shell->le->cursor_pos = shell->le->i;
}

/**
 * @brief Reproduce the down arrow from tcsh shell, naviguate throught
 * the history list and print it starting from the oldest to the most recent
 *
 * @param shell Shell structure containing line edition data
 */
void handle_down(shell_t *shell)
{
    if (shell->le->current == NULL)
        return;
    while (shell->le->i > 0) {
        write(STDOUT_FILENO, "\b \b", 3);
        shell->le->i--;
        shell->le->cursor_pos--;
    }
    free(shell->le->entire_line);
    if (shell->le->current->next != NULL) {
        shell->le->current = shell->le->current->next;
        shell->le->entire_line = strdup(shell->le->current->command);
        write(STDOUT_FILENO, shell->le->entire_line,
            strlen(shell->le->entire_line));
        shell->le->i = strlen(shell->le->entire_line);
        shell->le->cursor_pos = strlen(shell->le->entire_line);
    } else {
        shell->le->current = NULL;
        shell->le->entire_line = strdup("");
        shell->le->i = 0;
    }
}

/**
 * @brief Reproduce the right arrow from tcsh shell
 * Used to move right without leaving the prompt
 *
 * @param shell Shell structure containing line edition data
 */
void handle_right(shell_t *shell)
{
    if (shell->le->entire_line == NULL)
        return;
    if (shell->le->cursor_pos < (int)my_strlen(shell->le->entire_line)) {
        write(STDOUT_FILENO, "\033[C", 3);
        shell->le->cursor_pos++;
    }
}

/**
 * @brief Reproduce the left arrow from tcsh shell
 * Used to move left without leaving the prompt
 *
 * @param shell Shell structure containing line edition data
 */
void handle_left(shell_t *shell)
{
    if (shell->le->entire_line == NULL)
        return;
    if (shell->le->cursor_pos > 0) {
        write(STDOUT_FILENO, "\033[D", 3);
        shell->le->cursor_pos--;
    }
}

/**
 * @brief Handle arrow keys based on escape sequence.
 *
 * @note A = up
 *       B = down
 *       C = right
 *       D = left
 *
 * @param shell Shell structure containing line edition data
 */
void check_arrows(shell_t *shell)
{
    char c = shell->le->arrow_key[1];

    switch (c) {
        case 'A':
            handle_up(shell);
            break;
        case 'B':
            handle_down(shell);
            break;
        case 'C':
            handle_right(shell);
            break;
        case 'D':
            handle_left(shell);
            break;
    }
}
