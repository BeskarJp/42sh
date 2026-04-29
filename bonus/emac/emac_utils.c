/*
** EPITECH PROJECT, 2026
** 42sh
** line description:
** Utils for mini emac editor
*/

#include "shell.h"
#include <ncurses.h>

char *load_file(char *filepath)
{
    char *line = malloc(sizeof(char) * 4096);
    int fd = open(filepath, O_RDONLY);
    int bytes = 0;

    if (!line)
        return NULL;
    line[0] = '\0';
    if (fd != -1) {
        bytes = read(fd, line, 4095);
        if (bytes >= 0)
            line[bytes] = '\0';
        close(fd);
    }
    return line;
}

void save_file(char *filepath, char *line)
{
    int fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, PERM_NORM);

    if (fd == -1) {
        write(2, "emac: Permission denied or directory invalid\n", 45);
        return;
    }
    write(fd, line, my_strlen(line));
    close(fd);
}
