/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Alias checkeer before execute command
*/

#include "shell.h"

/**
 * @brief Merges aliases commands with tree commands
 *
 * @param aliases_buffer Array of aliases commands
 * @param argv_tree Array of tree arguments
 * @return char **. Containing merged arguments or NULL
 */
char **change_tree_command_to_alias(char **aliases_buffer, char **argv_tree)
{
    char **command_to_launch;
    int alias_len = 0;
    int tree_len = 0;
    int i = 0;

    while (aliases_buffer[alias_len])
        alias_len++;
    while (argv_tree[tree_len])
        tree_len++;
    command_to_launch = malloc(sizeof(char *) * (alias_len + tree_len));
    if (command_to_launch == NULL)
        return NULL;
    for (i = 0; i < alias_len; i++)
        command_to_launch[i] = my_strdup(aliases_buffer[i]);
    for (int j = 1; argv_tree[j]; j++) {
        command_to_launch[i] = my_strdup(argv_tree[j]);
        i++;
    }
    command_to_launch[i] = NULL;
    return command_to_launch;
}

/**
 * @brief Substitutes the first argument of the tree with its alias value
 *
 * @param tree Token tree structure
 * @param recursive_count Pointer the counter for handle infinite loops
 * @return int. 1 if substitution succeeded or 0 is error
 */
int apply_alias_substitution(token_tree_t *tree, alias_t *correlation)
{
    char **aliases_buffer = my_str_to_word_array(correlation->command);
    char **command_launch;

    if (!aliases_buffer)
        return 0;
    command_launch = change_tree_command_to_alias(aliases_buffer, tree->args);
    free_array(aliases_buffer);
    if (command_launch == NULL)
        return 0;
    free_array(tree->args);
    tree->args = command_launch;
    return 1;
}

/**
 * @brief Recursively checks and applies aliases to command arguments
 *
 * @param shell Shell structure
 * @param tree Token tree structure
 * @param recursive_count Pointer the counter for handle infinite loops
 */
void recursive_alias_checker(shell_t *shell, token_tree_t *tree,
    int *recursive_count)
{
    alias_t *correlation;
    char **command_to_lunch;
    char **aliases_buffer;

    if (*recursive_count > 20) {
        write(2, "Alias loop.\n", 12);
        free_array(tree->args);
        tree->args = NULL;
        return;
    }
    if (!tree || !tree->args || !tree->args[0])
        return;
    correlation = find_alias_by_name(shell->aliases, tree->args[0]);
    if (correlation == NULL)
        return;
    aliases_buffer = my_str_to_word_array(correlation->command);
    command_to_lunch = change_tree_command_to_alias(aliases_buffer, tree->args);
    if (command_to_lunch == NULL)
        return;
    free_array(tree->args);
    free_array(aliases_buffer);
    tree->args = command_to_lunch;
    (*recursive_count)++;
    recursive_alias_checker(shell, tree, recursive_count);
}

/**
 * @brief Checks and applies aliases to a command in the token tree
 *
 * @param shell Shell structure with aliases
 * @param tree Token tree with the command to check
 */
void alias_checker(shell_t *shell, token_tree_t *tree)
{
    int recursive_count = 0;

    if (shell == NULL || tree == NULL)
        return;
    recursive_alias_checker(shell, tree, &recursive_count);
}
