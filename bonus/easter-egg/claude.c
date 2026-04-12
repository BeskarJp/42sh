/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Main file for EpiClaude
*/

#include "shell.h"

void start_claude(shell_t *shell)
{
    ssize_t read_bytes = 0;
    size_t len = 0;
    char *line = NULL;

    print_header(shell);
    while (1) {
        my_printf("%sEpiClaude >%s ", ORANGE, RESET);
        read_bytes = getline(&line, &len, stdin);
        if (read_bytes == -1 || my_strcmp(line, "quit\n") == 0 ||
            my_strcmp(line, "exit\n") == 0)
            break;
        if (line[read_bytes - 1] == '\n')
            line[read_bytes - 1] = '\0';
        if (line[0] != '\0')
            handle_input(line);
    }
    ia_style_text_writer("Bye Bye ! Returning to 42sh", SLOW);
    ia_style_text_writer(" ...\n", ULTRA_SLOW);
    if (line)
        free(line);
}
