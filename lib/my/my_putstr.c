/*
** EPITECH PROJECT, 2026
** my_putstr
** File description:
** Paste a string
*/

#include "my.h"

int my_putstr(char const *str)
{
    int i;

    for (i = 0; str[i] != '\0'; i++) {
        my_putchar(str[i]);
    }
    return 0;
}
