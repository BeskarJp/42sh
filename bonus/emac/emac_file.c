/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Function linked to file
*/

#include "shell.h"

/**
 * @brief Loads a file into the Emac editor buffer
 *
 * @param pathline Path of the file to load
 * @return char*. Allocated buffer containing file contents or NULL if not
 */
char *load_emac_file(char *pathline)
{
    char *file_buffer = malloc(sizeof(char) * 4096);
    int fd = open(pathline, O_RDONLY);
    int size = 0;

    if (!file_buffer)
        return NULL;
    memset(file_buffer, 0, 4096);
    if (fd != -1) {
        size = read(fd, file_buffer, 4095);
        if (size < 0)
            size = 0;
        file_buffer[size] = '\0';
        close(fd);
    }
    return file_buffer;
}

/**
 * @brief Saves the current editor buffer to disk
 *
 * @param editor Editor state containing file path and buffer
 */
void save_emac_file(emacs_t *editor)
{
    int fd = open(editor->pathline, O_WRONLY | O_CREAT | O_TRUNC, PERM_NORM);

    if (fd == -1) {
        mvprintw(0, 0, "Error: Cannot save file!");
        return;
    }
    write(fd, editor->file_buffer, editor->text_len);
    close(fd);
}
