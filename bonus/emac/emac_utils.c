/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Utils for emac
*/

#include "shell.h"

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

void handle_emac_input(int pid_count, char *line, int *len)
{
    if ((pid_count == KEY_BACKSPACE || pid_count == 127 ||
            pid_count == '\b') && *len > 0) {
        (*len)--;
        line[*len] = '\0';
    } else if (pid_count != 24 && *len < 4095 && pid_count >= 32 &&
        pid_count <= 126) {
        line[*len] = (char)pid_count;
        (*len)++;
        line[*len] = '\0';
    }
    if (pid_count == '\n' && *len < 4095) {
        line[*len] = '\n';
        (*len)++;
        line[*len] = '\0';
    }
}
