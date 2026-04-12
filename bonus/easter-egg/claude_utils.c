/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Utils for Epi Claude
*/

#include "shell.h"

char *user_of_shell(char **env)
{
    char *username = find_word_in_env(env, "USERNAME");

    if (username != NULL)
        return username;
    return "Blud";
}

void ia_style_text_writer(char *text)
{
    for (int i = 0; text[i] != '\0'; i++) {
        my_putchar(text[i]);
        fflush(stdout);
        usleep(40000);
    }
    my_putchar('\n');
}
