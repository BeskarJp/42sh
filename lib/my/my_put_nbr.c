/*
** EPITECH PROJECT, 2026
** my_put_nbr.c
** File description:
** my_put_nbr
*/

#include "my.h"

int my_put_nbr(int nb)
{
    if (-2147483648 >= nb || 2147483647 <= nb)
        return 0;
    if (nb < 0) {
        my_putchar('-');
        nb = -nb;
    }
    if (nb >= 10)
        my_put_nbr(nb / 10);
    my_putchar('0' + (nb % 10));
    return 0;
}
