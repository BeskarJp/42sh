/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Tests for lib/my functions
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "my.h"

Test(my_printf, print_char)
{
    cr_redirect_stdout();
    my_printf("%c", 'A');
    cr_assert_stdout_eq_str("A");
}

Test(my_printf, print_str)
{
    cr_redirect_stdout();
    my_printf("%s", "Hello");
    cr_assert_stdout_eq_str("Hello");
}

Test(my_printf, print_number)
{
    cr_redirect_stdout();
    my_printf("%d", 42);
    cr_assert_stdout_eq_str("42");
}

Test(my_printf, percent_percent)
{
    cr_redirect_stdout();
    my_printf("%%");
    cr_assert_stdout_eq_str("%");
}

Test(my_printf, default_case)
{
    cr_redirect_stdout();
    my_printf("%x");
    cr_assert_stdout_eq_str("%x");
}

Test(my_getnbr, positive_number)
{
    int result = my_getnbr("123");

    cr_assert_eq(result, 123);
}

Test(my_getnbr, negative_number)
{
    int result = my_getnbr("-456");

    cr_assert_eq(result, -456);
}

Test(my_getnbr, with_non_digit)
{
    int result = my_getnbr("789abc");

    cr_assert_eq(result, 0);
}

Test(my_put_nbr, positive_number)
{
    cr_redirect_stdout();
    my_put_nbr(123);
    cr_assert_stdout_eq_str("123");
}

Test(my_put_nbr, negative_number)
{
    cr_redirect_stdout();
    my_put_nbr(-456);
    cr_assert_stdout_eq_str("-456");
}

Test(my_put_nbr, zero)
{
    cr_redirect_stdout();
    my_put_nbr(0);
    cr_assert_stdout_eq_str("0");
}

Test(my_put_nbr, int_min)
{
    int result = my_put_nbr(-2147483648);

    cr_assert_eq(result, 0);
}

Test(my_putchar, basic)
{
    cr_redirect_stdout();
    my_putchar('Z');
    cr_assert_stdout_eq_str("Z");
}

Test(str_nfuse, basic_fusion)
{
    char *buff[] = {"usr", "bin", "ls", NULL};
    char *res = str_nfuse(buff, 0, 2, '/');

    cr_assert_str_eq(res, "usr/bin/ls/");
    free(res);
}

Test(str_nfuse, error_cases)
{
    char *buff[] = {"a", "b", NULL};

    cr_assert_null(str_nfuse(NULL, 0, 1, ' '));
    cr_assert_null(str_nfuse(buff, 2, 0, ' '));
}

Test(str_nfuse, single_word)
{
    char *buff[] = {"hello", NULL};
    char *res = str_nfuse(buff, 0, 0, ':');

    cr_assert_str_eq(res, "hello:");
    free(res);
}
