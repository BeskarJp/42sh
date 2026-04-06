/*
** EPITECH PROJECT, 2026
** my_get_nbr
** File description:
** Find number in a string
*/

int my_getnbr(char *str)
{
    int result = 0;
    int sign = 1;
    int i = 0;

    if (str[i] == '-') {
        sign = -1;
        i++;
    }
    for (; str[i] != '\0'; i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            result = result * 10 + (str[i] - '0');
        } else
            return 0;
    }
    return (sign * result);
}
