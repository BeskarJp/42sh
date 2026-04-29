/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Utils for backsticks
*/

#include "shell.h"

/**
 * @brief Replace all newline characters in a buffer with spaces
 *
 * @param buffer The string to process
 * @param bytes Number of bytes to check
 */
void replace_newlines(char *buffer, int bytes)
{
    for (int i = 0; i < bytes; i++) {
        if (buffer[i] == '\n')
            buffer[i] = ' ';
    }
}

/**
 * @brief Concatenate two strings and free the old one
 *
 * @param old The original string to be freed
 * @param buffer The new string to append
 * @return char*. The new concatenated string or NULL if not
 */
char *join_and_free(char *old, char *buffer)
{
    size_t len = my_strlen(old) + my_strlen(buffer) + 1;
    char *new = malloc(sizeof(char) * len);

    if (!new)
        return NULL;
    my_strcpy(new, old);
    my_strcat(new, buffer);
    free(old);
    return new;
}

/**
 * @brief Read the content of a pipe and return it as a string
 *
 * @param fd File descriptor of the pipe to read from
 * @return char*. The content read from the pipe or NULL if not
 */
char *read_pipe(int fd)
{
    char buffer[1024];
    char *old = my_strdup("");
    int bytes = 0;

    if (!old)
        return NULL;
    bytes = read(fd, buffer, 1023);
    while (bytes > 0) {
        buffer[bytes] = '\0';
        replace_newlines(buffer, bytes);
        old = join_and_free(old, buffer);
        if (!old)
            return NULL;
        bytes = read(fd, buffer, 1023);
    }
    return old;
}

/**
 * @brief Reconstruct the command line by replacing the backticks with
 * the command output
 *
 * @param line The original command line
 * @param start Index of the first backtick
 * @param end Index of the second backtick
 * @param out The output string to inject
 * @return char*. The new command line
 */
char *rebuild_line(char *line, int start, int end, char *out)
{
    int len = my_strlen(line) + my_strlen(out) + 1;
    char *new = malloc(sizeof(char) * len);
    int i = 0;
    int j = 0;

    if (!new)
        return NULL;
    for (i = 0; i < start; i++)
        new[i] = line[i];
    new[i] = '\0';
    my_strcat(new, out);
    i = my_strlen(new);
    for (j = end + 1; line[j] != '\0'; j++) {
        new[i] = line[j];
        i++;
    }
    new[i] = '\0';
    return new;
}
