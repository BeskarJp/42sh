/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Bonus/claude_print : Easter-Egg of Shell
*/

#include "shell.h"

char *user_of_shell(char **env)
{
    char *username = "Blud";

    username = find_word_in_env(env, "USERNAME");
    if (username != NULL || my_strcmp(username, "Blud") != 0)
        return username;
    else
        return username;
}

void print_header(shell_t *shell)
{
    char *username = user_of_shell(shell->copy_env);

    printf("\n%s  [#]  %sClaude Code %sv2.1.74\n", ORANGE, STYLE_BOLD, GREY);
    printf("%sHello %s. How are you ?\n", RESET, username);
}

void ia_style_text_writer(char *text)
{
    for (int i = 0; text[i] != '\0'; i++) {
        printf("%c", text[i]);
        fflush(stdout);
        usleep(30000);
    }
    printf("\n");
}
