/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** File that will detect and execute arrows
*/

#include "shell.h"

/**
 * @brief Return NULL while writting a error message and freeing the structure
 *
 * @param str The error message
 * @param le Line edition structure
 * @param flag Decide what the function do
 */
static char *char_return(const char *str, line_edition_t *le, const char *flag)
{
    if (strcmp(flag, "silent") == 0) {
        if (le)
            free(le);
        return NULL;
    }
    if (strcmp(flag, "no free") == 0) {
        printf("Error: %s!\n", str);
        return NULL;
    }
    if (strcmp(flag, "silent, no free") == 0)
        return NULL;
    printf("Error: %s!\n", str);
    if (le)
        free(le);
    return NULL;
}

/**
 * @brief set the le structure
 *
 * @param le Line edition structure
*/
static line_edition_t *set_line_edition(line_edition_t *le)
{
    le->entire_line = NULL;
    le->arrow_key = malloc(2);
    if (!le->arrow_key)
        return NULL;
    le->arrow_key[0] = 0;
    le->arrow_key[1] = 0;
    le->key = '\0';
    le->i = 0;
    le->current = NULL;
    return le;
}

/**
 * @brief Get the configuration of the current terminal and store
 * it inside the structure line_edition_t
 *
 * @param le Line edition structure
*/
line_edition_t *check_config(line_edition_t *le)
{
    if (tcgetattr(STDIN_FILENO, &le->config) == -1) {
        printf("Error: invalid configuarion!\n");
        return NULL;
    }
    le->config_copy = le->config;
    le->config_copy.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSANOW, &le->config_copy) == -1) {
        printf("Error: invalid configuration\n");
        tcsetattr(STDIN_FILENO, TCSANOW, &le->config);
        return NULL;
    }
    return set_line_edition(le);
}

/**
 * @brief Append the current key to the line buffer.
 *
 * @param shell Shell structure
 */
static void set_line(line_edition_t *le)
{
    char *new_line = realloc(le->entire_line, le->i + 2);

    if (!new_line)
        return;
    le->entire_line = new_line;
    le->entire_line[le->i] = le->key;
    le->i++;
    le->entire_line[le->i] = '\0';
}

/**
 * @brief while loop that constantly check if any of those
 * keys have been pressed
 *
 * @param shell Shell structure
 */
char *key_loop(shell_t *shell)
{
    line_edition_t *le = shell->le;

    while (read(STDIN_FILENO, &le->key, 1) > 0) {
        if (handle_ctrl_d(le))
            return NULL;
        if (handle_backspace(le) || handle_keys(shell) || le->key == '\t')
            continue;
        write(STDOUT_FILENO, &le->key, 1);
        set_line(le);
        if (le->key == '\n')
            break;
    }
    return le->entire_line;
}

/**
 * @brief Read the line and if the function detect its an arrow key,
 * it will [something]
 *
 * @param shell Shell structure
 */
char *detect_keys(shell_t *shell)
{
    char *result = NULL;

    shell->le = malloc(sizeof(line_edition_t));
    if (!shell->le)
        return char_return("invalid malloc", shell->le, "silent");
    shell->le = check_config(shell->le);
    if (shell->le == NULL)
        return char_return("check_config fail", shell->le, "silent");
    result = key_loop(shell);
    tcsetattr(STDIN_FILENO, TCSANOW, &shell->le->config);
    return result;
}
