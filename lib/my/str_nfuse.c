/*
** EPITECH PROJECT, 2026
** str_nfuse
** File description:
** take a char** and fuse from ind 'start to ind 'end' in a char*
*/

#include "my.h"

static int add_separator(char *str, int pos, char sep)
{
    str[pos] = sep;
    return (pos + 1);
}

char *str_nfuse(char **buff, int start, int end, char sep)
{
    char *str = NULL;
    int size = 0;
    int pos = 0;

    if (!buff || start > end)
        return NULL;
    for (int k = start; k <= end; k++)
        size += my_strlen(buff[k]);
    str = malloc(sizeof(char) * (size + (end - start) + 1));
    if (!str)
        return NULL;
    for (int i = start; i <= end && buff[i] != NULL; i++) {
        for (int j = 0; buff[i][j] != '\0'; j++) {
            str[pos] = buff[i][j];
            pos++;
        }
        pos = add_separator(str, pos, sep);
    }
    str[pos] = '\0';
    return str;
}
