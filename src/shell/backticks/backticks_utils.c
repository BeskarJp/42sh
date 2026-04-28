/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Utils for backsticks
*/

#include "shell.h"

void replace_newlines(char *buffer, int bytes)
{
    for (int i = 0; i < bytes; i++) {
        if (buffer[i] == '\n')
            buffer[i] = ' ';
    }
}

char *join_and_free(char *old, char *buffer)
{
    size_t len = strlen(old) + strlen(buffer) + 1;
    char *new = malloc(sizeof(char) * len);

    if (!new)
        return NULL;
    strcpy(new, old);
    strcat(new, buffer);
    free(old);
    return new;
}

char *read_pipe(int fd)
{
    char buffer[1024];
    char *old = strdup("");
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
