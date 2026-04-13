/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Parse line for explain
*/

#include "shell.h"

void display_text(char *line)
{
    ia_style_text_writer("      -> More of this command : ", FAST);
    ia_style_text_writer(line + 2, FAST);
    ia_style_text_writer("\n", FAST);
}

void print_more_of_command(char *command)
{
    FILE *fd = fopen("./bonus/epiclaude/rdr_files/commands.rdr", "r");
    char *line = NULL;
    size_t len = 0;
    int flag_found = 0;

    if (!fd)
        return;
    while (getline(&line, &len, fd) != -1) {
        if (line[my_strlen(line) - 1] == '\n')
            line[my_strlen(line) - 1] = '\0';
        if (flag_found == 1 && my_strncmp(line, "C ", 2) == 0) {
            display_text(line);
            break;
        }
        if (my_strncmp(line, "U ", 2) == 0)
            flag_found = (my_strcmp(line + 2, command) == 0) ? 1 : 0;
    }
    if (line)
        free(line);
    fclose(fd);
}
