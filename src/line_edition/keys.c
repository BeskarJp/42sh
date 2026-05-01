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
    if (le->key != 4)
        return 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &le->config);
    return 1;
}

/**
 * @brief Check if any arrow key has been pressed
 *
 * @param le Line edition structure
 */
int handle_keys(line_edition_t *le)
{
    if (le->key != 27)
        return 0;
    if (read(STDIN_FILENO, &le->arrow_key[0], 1) != 1)
        return 1;
    if (read(STDIN_FILENO, &le->arrow_key[1], 1) != 1)
        return 1;
    return 1;
}

/**
 * @brief Check if backspace has been pressed
 *
 * @param le Line edition structure
 */
int handle_backspace(line_edition_t *le)
{
    if (le->key != 127)
        return 0;
    if (le->i > 0) {
        le->i--;
        le->entire_line[le->i] = '\0';
        write(STDOUT_FILENO, "\b \b", 3);
    }
    return 1;
}
