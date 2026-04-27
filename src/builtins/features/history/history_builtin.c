/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** History in shell
*/

#include "shell.h"

/**
 * @brief Get current time in XX : XX
 *
 * @return char*. allocated string with current time
 */
char *get_current_time(void)
{
    time_t rawtime;
    struct tm *timeinfo;
    char *line = malloc(sizeof(char) * 6);

    if (!line)
        return NULL;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(line, 6, "%H:%M", timeinfo);
    return line;
}

/**
 * @brief Adds a command line to the history list
 *
 * @param shell Shell structure
 * @param line Command line to save
 */
void add_to_history_linked_list(shell_t *shell, char *line)
{
    history_t *new_node = malloc(sizeof(history_t));
    history_t *temp = shell->history;

    if (!line || line[0] == '\n' || !new_node)
        return;
    new_node->command = my_strdup(line);
    if (new_node->command[my_strlen(new_node->command) - 1] == '\n')
        new_node->command[my_strlen(new_node->command) - 1] = '\0';
    new_node->time = get_current_time();
    new_node->next = NULL;
    if (!shell->history) {
        new_node->index = 1;
        shell->history = new_node;
    } else {
        while (temp->next)
            temp = temp->next;
        new_node->index = temp->index + 1;
        temp->next = new_node;
    }
}

/**
 * @brief Displays the command history using my_printf
 *
 * @param shell Shell structure
 */
void display_history(shell_t *shell)
{
    history_t *temp = shell->history;

    while (temp) {
        my_printf("\t%d  %s   %s\n", temp->index, temp->time, temp->command);
        temp = temp->next;
    }
    shell->exit_status = 0;
}
