/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Handle input for EpiClaude
*/

#include "shell.h"

void handle_input(char *line)
{
    if (my_strcmp(line, "help") == 0) {
        ia_style_text_writer("\nYou only can write 'notions'", BASIC);
        ia_style_text_writer(" for the moment.\n\n", BASIC);
        return;
    }
    if (my_strcmp(line, "notions") == 0) {
        print_explication_shell();
        return;
    }
    ia_style_text_writer("I don't understand. Try 'notions'.\n", BASIC);
}
