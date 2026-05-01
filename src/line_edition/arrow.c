/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** reproduce the behavior of arrow keys
*/

#include "shell.h"

/**
 * @brief Load last command and print it
 *
 * @param shell Shell structure containing line edition data
 */
static void handle_up(shell_t *shell)
{
    history_t *tmp = shell->history;

    if (!tmp)
        return;
    while (tmp->next)
        tmp = tmp->next;
    while (shell->le->i > 0) {
        write(STDOUT_FILENO, "\b \b", 3);
        shell->le->i--;
    }
    free(shell->le->entire_line);
    shell->le->entire_line = strdup(tmp->command);
    write(STDOUT_FILENO, tmp->command, strlen(tmp->command));
    shell->le->i = strlen(tmp->command);
}

/**
 * @brief Load current command and print it
 *
 * @param shell Shell structure containing line edition data
 */
static void handle_down(shell_t *shell)
{
    while (shell->le->i > 0) {
        write(STDOUT_FILENO, "\b \b", 3);
        shell->le->i--;
    }
    free(shell->le->entire_line);
    shell->le->entire_line = strdup("");
}

/**
 * @brief Used to move right without leaving the prompt
 *
 * @param shell Shell structure containing line edition data
 */
void handle_right(shell_t *shell)
{
    if (shell->le->i < my_strlen(shell->le->entire_line)) {
        write(STDOUT_FILENO, "\033[C", 3);
        shell->le->i++;
    }
}

/**
 * @brief Used to move left without leaving the prompt
 *
 * @param shell Shell structure containing line edition data
 */
static void handle_left(shell_t *shell)
{
    if (shell->le->i > 0) {
        write(STDOUT_FILENO, "\033[D", 3);
        shell->le->i--;
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
