/*
** EPITECH PROJECT, 2026
** exec_globbings
** File description:
** Globbing pattern expansion for 42sh
*/

#include "shell.h"

/**
 * @brief Checks if a string contains globbing pattern characters
 *
 * @param str String to check
 */
int is_globbing_pattern(char *str)
{
    int i;

    for (i = 0; str && str[i]; i++) {
        if (str[i] == '*' || str[i] == '?' || str[i] == '[')
            return 1;
    }
    return 0;
}

/**
 * @brief Counts the number of arguments in an array
 *
 * @param args Array of strings terminated by NULL
 */
int count_args(char **args)
{
    int i;

    for (i = 0; args[i]; i++);
    return i;
}

/**
 * @brief Appends a string to the expanded arguments array
 *
 * @param exp Pointer to expanded array
 * @param count Pointer to current count
 * @param cap Pointer to capacity
 * @param str String to append
 */
int append_match(char ***exp, int *count, int *cap, char *str)
{
    if (*count >= *cap)
        return -1;
    (*exp)[*count] = str;
    (*count)++;
    return 0;
}

/**
 * @brief Expands glob patterns in command arguments
 *
 * @param args Original command arguments
 */
char **expand_globbing(char **args)
{
    char **expanded;
    int count = 0;
    int capacity;
    int orig_size;

    if (!args)
        return NULL;
    orig_size = count_args(args);
    capacity = orig_size * 10 + 10;
    expanded = malloc(sizeof(char *) * capacity);
    if (!expanded)
        return args;
    if (expand_all_args(args, expanded, &count, &capacity) == -1) {
        free(expanded);
        return args;
    }
    expanded[count] = NULL;
    free_array(args);
    return expanded;
}
