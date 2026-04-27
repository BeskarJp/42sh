/*
** EPITECH PROJECT, 2026
** G-PSU-200-LIL-2-1-42sh-1
** File description:
** var_declared
*/

#include "shell.h"

int var_declared(shell_t *shell, int n)
{
    char *first = shell->arg_col[n];
    int count = 0;
    int i = 0;

    while (first[i] != '\0') {
        if (first[i] == '=')
            count++;
        if ((first[i] >= 'a' && first[i] <= 'z') ||
            (first[i] >= 'A' && first[i] <= 'Z') ||
            (first[i] >= '0' && first[i] <= '9') ||
            (first[i] == '=')) {
            i++;
        } else {
            return 84;
        }
    }
    if (count != 1)
        return 84;
    return 0;
}
