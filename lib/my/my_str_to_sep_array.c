/*
** EPITECH PROJECT, 2026
** my_str_to_sep_array
** File description:
** Most important function
*/

#include "my.h"
#include <stdio.h>

static int is_sep(char c, char const *seps)
{
    if (c == '\0')
        return 1;
    for (int i = 0; seps[i] != '\0'; i++) {
        if (c == seps[i])
            return 1;
    }
    return 0;
}

static int count_words_in_output(char const *str, char const *seps)
{
    int count = 0;
    int flag = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (is_sep(str[i], seps) == 0 && flag == 0) {
            flag = 1;
            count++;
        }
        if (is_sep(str[i], seps) == 1)
            flag = 0;
    }
    return count;
}

static int count_char_in_word(char const *str, int word_index, char const *seps)
{
    int len = 0;
    int i = word_index;

    while (str[i] != '\0' && is_sep(str[i], seps) == 0) {
        len++;
        i++;
    }
    return len;
}

static char *copy_word(const char *src, int i, int len)
{
    char *word = malloc(sizeof(char) * (len + 1));
    int j = 0;

    if (word == NULL)
        return NULL;
    for (; j < len; j++)
        word[j] = src[i + j];
    word[j] = '\0';
    return word;
}

static void free_tab(char **tab, int k)
{
    for (int j = 0; j < k; j++)
        free(tab[j]);
    free(tab);
}

static char **fill_array(char **tab, const char *str, char const *seps)
{
    int k = 0;
    int len;
    int i = 0;

    while (str[i] != '\0') {
        if (is_sep(str[i], seps)) {
            i++;
            continue;
        }
        len = count_char_in_word(str, i, seps);
        tab[k] = copy_word(str, i, len);
        if (tab[k] == NULL) {
            free_tab(tab, k);
            return NULL;
        }
        k++;
        i += len;
    }
    tab[k] = NULL;
    return tab;
}

char **my_str_to_sep_array(const char *str, char const *seps)
{
    int nb_word = 0;
    char **tab = NULL;

    if (str == NULL || seps == NULL)
        return NULL;
    nb_word = count_words_in_output(str, seps);
    tab = malloc(sizeof(char *) * (nb_word + 1));
    if (tab == NULL)
        return NULL;
    return fill_array(tab, str, seps);
}
