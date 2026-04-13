/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Parse line for explain
*/

#include "shell.h"

void explain_simple_command(token_tree_t *tree, int *step)
{
    if (!tree->args || !tree->args[0])
        return;
    my_printf("%s Step %d :%s ", ORANGE, *step, RESET);
    ia_style_text_writer("Execute the command '", FAST);
    ia_style_text_writer(tree->args[0], FAST);
    ia_style_text_writer("'", FAST);
    if (tree->args[1] != NULL) {
        ia_style_text_writer(" with his arguments : ", FAST);
        for (int i = 1; tree->args[i]; i++) {
            ia_style_text_writer("[", FAST);
            ia_style_text_writer(tree->args[i], FAST);
            ia_style_text_writer("] ", FAST);
        }
    }
    ia_style_text_writer("\n", FAST);
    print_more_of_command(tree->args[0]);
    (*step)++;
}

void explain_pipe_and_semicolons(token_tree_t *tree, int *step)
{
    if (tree->type == SEMICOLONS) {
        explain_tree(tree->left, step);
        my_printf("%s Step %d :%s ", ORANGE, *step, RESET);
        ia_style_text_writer("We continue with the next command\n", FAST);
        (*step)++;
        explain_tree(tree->right, step);
    }
    if (tree->type == PIPE) {
        explain_tree(tree->left, step);
        my_printf("%s Step %d :%s ", ORANGE, *step, RESET);
        ia_style_text_writer("Handle output (Pipe) ", FAST);
        ia_style_text_writer("to the next command \n", FAST);
        (*step)++;
        explain_tree(tree->right, step);
    }
}

void explain_redirections(token_tree_t *tree, int *step)
{
    explain_tree(tree->left, step);
    my_printf("%s Step %d :%s ", ORANGE, *step, RESET);
    if (tree->type == REDIR_DROITE)
        ia_style_text_writer("Redirect stdout to the file (>)\n", FAST);
    if (tree->type == REDIR_DB_DROITE)
        ia_style_text_writer("Redirect stdout to end of the file (>>)\n", FAST);
    if (tree->type == REDIR_GAUCHE)
        ia_style_text_writer("Redirect stdin from the file (<)\n", FAST);
    if (tree->type == REDIR_DB_GAUCHE)
        ia_style_text_writer("Redirect stdin from old command (<<)\n", FAST);
    (*step)++;
}

void explain_tree(token_tree_t *tree, int *step)
{
    if (!tree)
        return;
    if (tree->type == SEMICOLONS || tree->type == PIPE) {
        explain_pipe_and_semicolons(tree, step);
        return;
    }
    if (tree->type >= REDIR_DROITE && tree->type <= REDIR_DB_GAUCHE) {
        explain_redirections(tree, step);
        return;
    }
    explain_simple_command(tree, step);
}

void explain_command_line(char *command)
{
    token_tree_t *tree = parse_line(command);
    int step = 1;

    if (!tree || (tree->type == SIMPLE_COMMAND && !tree->args[0])) {
        ia_style_text_writer("\n", 2000000);
        ia_style_text_writer("Sorry, I can't parse this command.\n\n", BASIC);
        return;
    }
    ia_style_text_writer("\nI explain now this command :", BASIC);
    ia_style_text_writer("\n\n", 1500000);
    explain_tree(tree, &step);
    ia_style_text_writer("\nThat's it ! If you need any explain,", SLOW);
    ia_style_text_writer(" don't hesitate !\n\n", SLOW);
    free_tree(tree);
}
