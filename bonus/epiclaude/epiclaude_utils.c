/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Utils for EpiClaude
*/

#include "shell.h"

/**
 * @brief Returns the shell username from the environment
 *
 * @param env Array which represente environment variables
 * @return char *. Username string or default value if not
 */
char *user_of_shell(char **env)
{
    char *username = find_word_in_env(env, "USERNAME");

    if (username != NULL)
        return username;
    return "Blud";
}

/**
 * @brief Displays the content of a notions file buffer
 *
 * @param line_in_file Buffer with the file contents
 * @param size Size of the buffer
 */
void display_line_in_file(char *line_in_file, int size)
{
    if (line_in_file == NULL || size == 0) {
        ia_style_text_writer("\nThere are nothing in 'notions.rdr' file", SLOW);
        ia_style_text_writer(" ...\n\n", ULTRA_SLOW);
        return;
    }
    line_in_file[size] = '\0';
    ia_style_text_writer("\n", SLOW);
    ia_style_text_writer(line_in_file, FAST);
    ia_style_text_writer("\n", ULTRA_SLOW);
}

/**
 * @brief Writes text with a simulated typing animation
 *
 * @param text Text to display
 * @param speed Delay between characters in microseconds
 */
void ia_style_text_writer(char *text, int speed)
{
    for (int i = 0; text[i] != '\0'; i++) {
        my_putchar(text[i]);
        fflush(stdout);
        usleep(speed);
    }
}
