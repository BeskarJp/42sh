/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Which in shell
*/

#include "shell.h"

int check_if_builtin(char *command)
{
    if (my_strcmp(command, "cd") == 0 || my_strcmp(command, "setenv") == 0 ||
        my_strcmp(command, "exit") == 0 || my_strcmp(command, "history") == 0 ||
        my_strcmp(command, "alias") == 0 || my_strcmp(command, "which") == 0 ||
        my_strcmp(command, "where") == 0 || my_strcmp(command, "help") == 0 ||
        my_strcmp(command, "unsetenv") == 0 ||
        my_strcmp(command, "./claude") == 0)
        return 1;
    return 0;
}

void print_when_where_match(char *copy_pathway, char *command)
{
    char *directory = strtok(copy_pathway, ":");
    char *pathway = NULL;

    while (directory != NULL) {
        pathway = create_path_way(directory, command);
        if (pathway != NULL && access(pathway, X_OK) == 0)
            my_printf("%s\n", pathway);
        if (pathway != NULL)
            free(pathway);
        directory = strtok(NULL, ":");
    }
}
