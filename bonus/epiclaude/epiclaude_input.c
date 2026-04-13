/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Handle input for EpiClaude
*/

#include "shell.h"

int bonus_commands(char *line)
{
    if (my_strcmp(line, "whereami") == 0) {
        ia_style_text_writer("\nI don't know where we are ...\n\n", SLOW);
        ia_style_text_writer("But it doesn't matter where we are,", SLOW);
        ia_style_text_writer(" it's a huge party here !!!\n\n", SLOW);
        return 1;
    }
    if (my_strcmp(line, "antoiix") == 0) {
        ia_style_text_writer("\nLet's me ask to Antoine Orange ...\n\n", SLOW);
        ia_style_text_writer("He said skill issue ...\n\n", SLOW);
        return 1;
    }
    if (my_strcmp(line, "eliott") == 0) {
        ia_style_text_writer("\nLet's me ask to Eliott the AER ...\n\n", SLOW);
        ia_style_text_writer("42 sh ? Pourquoi pas Wolf3D ???\n\n", SLOW);
        return 1;
    }
    return 0;
}

int handle_basic_commands(char *line)
{
    if (my_strcmp(line, "help") == 0) {
        ia_style_text_writer("\nYou only can write 'notions'", BASIC);
        ia_style_text_writer(" or 'explain line <command>'.\n\n", BASIC);
        return 1;
    }
    if (my_strcmp(line, "notions") == 0) {
        print_explication_shell();
        return 1;
    }
    if (my_strncmp(line, "explain line ", 13) == 0) {
        explain_command_line(line + 13);
        return 1;
    }
    if (bonus_commands(line) == 1)
        return 1;
    return 0;
}

void handle_input(char *line)
{
    if (handle_basic_commands(line) == 1)
        return;
    ia_style_text_writer("\nI don't understand. Try 'notions'", BASIC);
    ia_style_text_writer(" or 'explain line <command>'.\n\n", BASIC);
}
