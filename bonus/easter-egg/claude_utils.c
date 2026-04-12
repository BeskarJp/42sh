/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Utils for Epi Claude
*/

#include "shell.h"

char *user_of_shell(char **env)
{
    char *username = "Blud";

    username = find_word_in_env(env, "USERNAME");
    if (username != NULL || my_strcmp(username, "Blud") == 0)
        return username;
    else
        return username;
}

void ia_style_text_writer(char *text)
{
    for (int i = 0; text[i] != '\0'; i++) {
        printf("%c", text[i]);
        fflush(stdout);
        usleep(40000);
    }
    printf("\n");
}
