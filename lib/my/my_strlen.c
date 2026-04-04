/*
** EPITECH PROJECT, 2026
** my_strlen
** File description:
** Count the size of string
*/

int my_strlen(char const *str)
{
    int p = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        p = p + 1;
    }
    return p;
}
