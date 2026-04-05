/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Clean string for save in struct
*/

#include "shell.h"

/**
 * @brief Extract and clean a substring without spaces before and after
 *
 * @param str String
 * @param start Start index
 * @param end End index
 * @return char* Allocated substring, or NULL.
 */
char *clear_string(char *str, int start, int end)
{
    char *str_cleaned = NULL;
    int len = 0;

    if (str == NULL)
        return NULL;
    while (start < end && (str[start] == ' ' || str[start] == '\t'))
        start++;
    while (end > start && (str[end - 1] == ' ' || str[end - 1] == '\t'))
        end--;
    len = end - start;
    str_cleaned = malloc(len + 1);
    if (!str_cleaned)
        return NULL;
    for (int i = 0; i < len; i++)
        str_cleaned[i] = str[start + i];
    str_cleaned[len] = '\0';
    return str_cleaned;
}
