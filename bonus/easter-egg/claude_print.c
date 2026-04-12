/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Print Epi Claude
*/

#include "shell.h"

void print_header(shell_t *shell)
{
    char *username = user_of_shell(shell->copy_env);
    char welcome[128];

    printf("\033[H\033[J");
    printf("\n %s [#] %s Epi Claude Code %s version 42.sh\n\n",
        ORANGE, STYLE_BOLD, GREY);
    sprintf(welcome, "Hello %s. How are you ?", username);
    printf("%s ", RESET);
    ia_style_text_writer(welcome);
    my_putchar('\n');
}
