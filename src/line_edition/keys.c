/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** handle keys for the line edition
*/

#include <shell.h>

/**
 * @brief Check if ctrl d has been pressed
 *
 * @param le Line edition structure
 */
int handle_ctrl_d(line_edition_t *le)
{
    if (le->key != CTRL_D)
        return 0;
    write(1, "\n", 1);
    tcsetattr(STDIN_FILENO, TCSANOW, &le->config);
    return 1;
}

/**
 * @brief Check if any arrow key has been pressed
 *
 * @param le Line edition structure
 */
int handle_keys(shell_t *keys)
{
    if (keys->le->key != ESC)
        return 0;
    if (read(STDIN_FILENO, &keys->le->arrow_key[0], 1) <= 0)
        return 1;
    if (read(STDIN_FILENO, &keys->le->arrow_key[1], 1) <= 0)
        return 1;
    check_arrows(keys);
    return 1;
}

/**
 * @brief Check if backspace has been pressed
 *
 * @param le Line edition structure
 */
int handle_backspace(line_edition_t *le)
{
    if (le->key != BACKSPACE)
        return 0;
    if (le->i > 0) {
        le->i--;
        le->entire_line[le->i] = '\0';
        write(STDOUT_FILENO, "\b \b", 3);
    }
    return 1;
}
