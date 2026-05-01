/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** reproduce the behavior of arrow keys
*/

#include "shell.h"

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
        case 'C':
            if (shell->le->i < my_strlen(shell->le->entire_line)) {
                write(STDOUT_FILENO, "\033[C", 3);
                shell->le->i++;
            }
            break;
        case 'D':
            handle_left(shell);
            break;
    }
}
