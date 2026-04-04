/*
** EPITECH PROJECT, 2026
** my_printf
** File description:
** my_printf
*/

#include "my.h"

void follow_percent(char argv, va_list list)
{
    switch (argv) {
        case '%':
            my_putchar('%');
            break;
        case 'c':
            my_putchar(va_arg(list, int));
            break;
        case 's':
            my_putstr(va_arg(list, char*));
            break;
        case 'i':
        case 'd':
            my_put_nbr(va_arg(list, int));
            break;
        default:
            my_putchar('%');
            my_putchar(argv);
            break;
    }
}

int my_printf(const char *format, ...)
{
    va_list list;

    va_start(list, format);
    for (int i = 0; format[i] != '\0'; i++)
        if (format[i] == '%' && format[i + 1] != '\0') {
            follow_percent(format[i + 1], list);
            i++;
        } else
            my_putchar(format[i]);
    va_end(list);
    return 0;
}
