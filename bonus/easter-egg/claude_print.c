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

    my_printf("\033[H\033[J");
    my_printf("\n%s [#] %s EpiClaude Code %s version 42.sh\n\n",
        ORANGE, STYLE_BOLD, GREY);
    sprintf(welcome, "Hello %s ! How are you ?\n", username);
    my_printf("%s ", RESET);
    ia_style_text_writer(welcome, SLOW);
    my_putchar('\n');
}

void print_explication_shell(void)
{
    ia_style_text_writer("\nHere is what this 42sh version can do :\n", BASIC);
    ia_style_text_writer("  - Execute standard shell commands with their ", FAST);
    ia_style_text_writer("flags (for example 'ls', 'ls -l', etc)\n", FAST);
}
