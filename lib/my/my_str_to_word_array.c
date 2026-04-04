/*
** EPITECH PROJECT, 2026
** my_str_to_word_array
** File description:
** my_str_to_word_array
*/

#include "my.h"

static int is_separator(char c)
{
    if (c == ' ' || c == '\t' || c == '\n' || c == '\0')
        return 1;
    return 0;
}

int count_words_in_output(char const *str)
{
    int count = 0;
    int flag = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (is_separator(str[i]) == 0 && flag == 0) {
            flag = 1;
            count++;
        }
        if (is_separator(str[i]) == 1) {
            flag = 0;
        }
    }
    return count;
}

int count_char_in_word(char const *str, int word_index)
{
    int len = 0;

    for (int i = word_index; str[i] != '\0' && is_separator(str[i]) == 0; i++) {
        len++;
    }
    return len;
}

char *copy_word(const char *src, int i, int len)
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

char **clean_on_failure(char **tab, int k)
{
    for (int j = 0; j < k; j++) {
        free(tab[j]);
    }
    free(tab);
    return NULL;
}

char **my_str_to_word_array(const char *str)
{
    int nb_word = count_words_in_output(str);
    char **tab = malloc(sizeof(char *) * (nb_word + 1));
    int len_word;
    int k = 0;

    if (str == NULL || tab == NULL)
        return NULL;
    for (int i = 0; str[i] != '\0'; i++) {
        if (is_separator(str[i]))
            continue;
        len_word = count_char_in_word(str, i);
        tab[k] = copy_word(str, i, len_word);
        if (tab[k] == NULL)
            return clean_on_failure(tab, k);
        k++;
        i += len_word - 1;
    }
    tab[k] = NULL;
    return tab;
}
