/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** history_expansion
*/

#include "shell.h"

/**
 * @brief Find a specific node in the history list by his index
 *
 * @param history The history structure
 * @param target The index to search
 * @return char*. The command string found or NULL
 */
char *find_command_by_index(history_t *history, int target)
{
    history_t *temp = history;

    while (temp != NULL) {
        if (temp->index == target)
            return temp->command;
        temp = temp->next;
    }
    return NULL;
}

/**
 * @brief Search for a command in history by his index (!n)
 *
 * @param shell Shell structure
 * @param index The index to find
 * @return char*. The command found or NULL
 */
char *get_history_by_index(shell_t *shell, int index)
{
    history_t *temp = shell->history;
    int target = index;

    if (index < 0) {
        while (temp && temp->next)
            temp = temp->next;
        if (temp != NULL)
            target = temp->index + index + 1;
        else
            target = 0;
    }
    return find_command_by_index(shell->history, target);
}

/**
 * @brief Search for the last command starting with a specific string (!string)
 *
 * @param shell Shell structure
 * @param str The str to find
 * @return char*. The command found or NULL
 */
char *get_history_by_str(shell_t *shell, char *str)
{
    history_t *temp = shell->history;
    int len = my_strlen(str);
    char *str_found = NULL;

    while (temp) {
        if (my_strncmp(temp->command, str, len) == 0)
            str_found = temp->command;
        temp = temp->next;
    }
    return str_found;
}

/**
 * @brief Identify which expansion type to perform (!!, !n, !str)
 *
 * @param shell Shell structure
 * @param line String after the first '!'
 * @return char*. The command found or NULL
 */
char *find_expansion(shell_t *shell, char *line)
{
    if (line[0] == '!')
        return get_history_by_index(shell, -1);
    if ((line[0] >= '0' && line[0] <= '9') || line[0] == '-')
        return get_history_by_index(shell, my_getnbr(line));
    return get_history_by_str(shell, line);
}

/**
 * @brief Main function for history substitution (!)
 *
 * @param shell Shell structure
 * @param line Line which will be excecute
 * @return char*. New allocated line or NULL for error
 */
char *check_history_feature(shell_t *shell, char *line)
{
    char *str_found = NULL;

    if (!line || line[0] != '!' || my_strlen(line) < 2)
        return line;
    str_found = find_expansion(shell, &line[1]);
    if (str_found == NULL) {
        write(2, &line[1], my_strlen(&line[1]));
        write(2, ": Event not found.\n", 19);
        free(line);
        return NULL;
    }
    my_printf("%s\n", str_found);
    free(line);
    return my_strdup(str_found);
}
