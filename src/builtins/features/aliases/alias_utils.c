/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Alias' utils for shell
*/

#include "shell.h"

/**
 * @brief Finds an alias by its name in the linked list
 *
 * @param aliases The aliases structure
 * @param name Name of the alias to find
 * @return alias_t. The alias struct if found or NULL
 */
alias_t *find_alias_by_name(alias_t *aliases, char *name)
{
    alias_t *temp = aliases;

    while (temp) {
        if (my_strcmp(temp->name, name) == 0)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

/**
 * @brief Adds or updates an alias in the shell
 *
 * @param shell Shell structure
 * @param name Name of the alias
 * @param command Command string for the alias
 */
void add_alias(shell_t *shell, char *name, char *command)
{
    alias_t *correlation = find_alias_by_name(shell->aliases, name);
    alias_t *new_node;

    if (correlation) {
        free(correlation->command);
        correlation->command = my_strdup(command);
        return;
    }
    new_node = malloc(sizeof(alias_t));
    if (!new_node)
        return;
    new_node->name = my_strdup(name);
    new_node->command = my_strdup(command);
    new_node->next = shell->aliases;
    shell->aliases = new_node;
}
