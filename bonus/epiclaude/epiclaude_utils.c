/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Utils for EpiClaude
*/

#include "shell.h"

char *user_of_shell(char **env)
{
    char *username = find_word_in_env(env, "USERNAME");

    if (username != NULL)
        return username;
    return "Blud";
}

void ia_style_text_writer(char *text, int speed)
{
    for (int i = 0; text[i] != '\0'; i++) {
        my_putchar(text[i]);
        fflush(stdout);
        usleep(speed);
    }
}
