/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Find the path_way of the command
*/

#include "shell.h"

/**
 * @brief Concatenates a directory and a command name to form a path
 *
 * @param dir path directory
 * @param command Command name
 * @return char*. Allocated string with full path or NULL
 */
char *create_path_way(char *dir, char *command)
{
    int path_len = my_strlen(dir) + my_strlen(command) + 2;
    char *path_way = malloc(sizeof(char) * path_len);
    int i = 0;
    int j = 0;

    if (path_way == NULL)
        return NULL;
    while (dir[i] != '\0') {
        path_way[i] = dir[i];
        i++;
    }
    path_way[i] = '/';
    i++;
    while (command[j] != '\0') {
        path_way[i + j] = command[j];
        j++;
    }
    path_way[i + j] = '\0';
    return path_way;
}

/**
 * @brief Searches for the executable command in each path directory
 *
 * @param path_copy Modifiable copy of the path variable
 * @param command Command name
 * @return char*. Path if it exists or NULL
 */
char *check_all_paths(char *path_copy, char *command)
{
    char *dir = strtok(path_copy, ":");
    char *path_way = NULL;

    while (dir != NULL) {
        path_way = create_path_way(dir, command);
        if (path_way != NULL && access(path_way, X_OK) == 0)
            return path_way;
        free(path_way);
        dir = strtok(NULL, ":");
    }
    return NULL;
}

/**
 * @brief Resolves the full path of a command from PATH or a relative path
 *
 * @param command Command name
 * @param env Environment variables
 * @return char*. Executable path or NULL
 */
char *find_command_path(char *command, char **env)
{
    char *path_line_in_env = find_word_in_env(env, "PATH");
    char *path_copy = NULL;
    char *path_way = NULL;

    if (env == NULL || command == NULL)
        return NULL;
    if (strchr(command, '/') != NULL) {
        if (access(command, F_OK) == 0)
            return my_strdup(command);
        return NULL;
    }
    if (path_line_in_env == NULL)
        return NULL;
    path_copy = my_strdup(path_line_in_env);
    if (path_copy == NULL)
        return NULL;
    path_way = check_all_paths(path_copy, command);
    free(path_copy);
    return path_way;
}
