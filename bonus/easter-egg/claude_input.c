/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Handle input for EpiClaude
*/

#include "shell.h"

void handle_input(char *line)
{
    if (my_strcmp(line, "notions") == 0) {
        print_explication_shell();
        return;
    }
    ia_style_text_writer("I don't understand. Try 'notions'.", BASIC);
}
