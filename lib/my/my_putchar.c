/*
** EPITECH PROJECT, 2026
** my_putchar
** File description:
** Print one char
*/

#include "my.h"

void my_putchar(char c)
{
    write(1, &c, 1);
}
