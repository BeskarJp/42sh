/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Parse line for explain
*/

#include "shell.h"

void explain_command_line(char *command)
{
    token_tree_t *tree = parse_line(command);

    if (!tree) {
        ia_style_text_writer("\n", 2000000);
        ia_style_text_writer("Sorry, I can't parse this command.\n\n", BASIC);
        return;
    }
    ia_style_text_writer("\nI explain now this command :", BASIC);
    ia_style_text_writer("\n\n", 1500000);
    free_tree(tree);
}
