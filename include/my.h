/*
** EPITECH PROJECT, 2026
** my.h
** File description:
** Include of Lib
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

#ifndef MY
    #define MY

int my_printf(const char *format, ...);
int my_put_nbr(int nb);
void my_putchar(char c);
int my_putstr(char const *str);
char **my_str_to_word_array(const char *str);
char *my_strcat(char *dest, char const *src);
int my_strcmp(char const *s1, char const *s2);
char *my_strcpy(char *dest, char const *src);
char *my_strdup(char const *src);
int my_strlen(char const *str);
int my_strncmp(char const *s1, char const *s2, int n);

#endif /* MY */
