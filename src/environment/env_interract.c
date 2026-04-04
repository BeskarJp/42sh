/*
** EPITECH PROJECT, 2026
** Minishell 2
** File description:
** Utils with environment
*/

#include "shell.h"

/**
 * @brief Duplicates the environment array
 *
 * @param env Original environment string array
 * @return char**. New copy of the array or NULL
 */
char **copy_environment(char **env)
{
    int i = 0;
    char **copy_env;

    while (env[i])
        i++;
    copy_env = malloc(sizeof(char *) * (i + 1));
    if (copy_env == NULL)
        return NULL;
    for (int j = 0; j < i; j++) {
        copy_env[j] = my_strdup(env[j]);
    }
    copy_env[i] = NULL;
    return copy_env;
}

/**
 * @brief Finds the value of a variable in the environment
 *
 * @param env Environment array
 * @param word Variable name without "="
 * @return char*. Pointer to the value or NULL if not found.
 */
char *find_word_in_env(char **env, char *word)
{
    int len = my_strlen(word);

    for (int i = 0; env[i] != NULL; i++) {
        if (my_strncmp(env[i], word, len) == 0 && env[i][len] == '=')
            return &env[i][len + 1];
    }
    return NULL;
}

/**
 * @brief Creates a string of the form "name=value"
 *
 * @param name Variable name
 * @param value Variable value
 * @return char*. Allocated string or NULL
 */
char *add_line_in_env(char *name, char *value)
{
    int val_len = (value != NULL) ? my_strlen(value) : 0;
    int size = my_strlen(name) + val_len + 2;
    char *line = malloc(sizeof(char) * size);

    if (line == NULL)
        return NULL;
    my_strcpy(line, name);
    my_strcat(line, "=");
    if (value != NULL)
        my_strcat(line, value);
    return line;
}
