/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Handle input for EpiClaude
*/

#include "shell.h"

/**
 * @brief Handles extended bonus commands for EpiClaude
 *
 * @param line Input line from the user
 * @return int. 1 if the command was recognized or 0 if otherwise
 */
int continue_bonus_commands(char *line)
{
    if (my_strcmp(line, "leandre") == 0) {
        ia_style_text_writer("\nLet me ask Léandre the AER ...\n\n", SLOW);
        ia_style_text_writer("Is it graphic ? Go ask Eliott ... \n\n", SLOW);
        return 1;
    }
    if (my_strcmp(line, "hugo") == 0) {
        ia_style_text_writer("\nHugo ?\n\n", SLOW);
        ia_style_text_writer("Don't you mean Hugoat ?\n\n", SLOW);
        return 1;
    }
    return 0;
}

/**
 * @brief Handles EpiClaude bonus commands not in the main command list
 *
 * @param line Input line from the user
 * @return int. 1 if the bonus command was processed or 0 if otherwise
 */
int bonus_commands(char *line)
{
    if (my_strcmp(line, "whereami") == 0) {
        ia_style_text_writer("\nI don't know where we are ...\n\n", SLOW);
        ia_style_text_writer("But it doesn't matter where we are,", SLOW);
        ia_style_text_writer(" it's a huge party here !!!\n\n", SLOW);
        return 1;
    }
    if (my_strcmp(line, "antoiix") == 0) {
        ia_style_text_writer("\nLet me ask Antoine Orange ...\n\n", SLOW);
        ia_style_text_writer("He said skill issue ...\n\n", SLOW);
        return 1;
    }
    if (my_strcmp(line, "eliott") == 0) {
        ia_style_text_writer("\nLet me ask Eliott the AER ...\n\n", SLOW);
        ia_style_text_writer("42 sh ? Pourquoi pas Wolf3D ???\n\n", SLOW);
        return 1;
    }
    if (continue_bonus_commands(line) == 1)
        return 1;
    return 0;
}

/**
 * @brief Handles the main EpiClaude commands
 *
 * @param line Input line from the user
 * @return int. 1 if the command was processed or 0 if otherwise
 */
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

/**
 * @brief Handles an unrecognized input line for EpiClaude
 *
 * @param line Input line from the user
 */
void handle_input(char *line)
{
    if (handle_basic_commands(line) == 1)
        return;
    ia_style_text_writer("\nI don't understand. Try 'notions'", BASIC);
    ia_style_text_writer(" or 'explain line <command>'.\n\n", BASIC);
}
