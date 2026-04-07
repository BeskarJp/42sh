/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Print prompt line in shell
*/

#include "shell.h"

/**
 * @brief Finds and prints the current username from the environment
 *
 * @param env Array of the environment
 */
void print_username(char **env)
{
    char *username = find_word_in_env(env, "USERNAME");

    if (username != NULL)
        my_putstr(username);
    else
        my_putstr("unknown");
}

/**
 * @brief Finds the HOME in env and compare to getcwd line for replace with ~
 *
 * @param way Exactly position of user
 * @param env Array of the environment
 */
void print_shorter_path(char *way, char **env)
{
    char *home = find_word_in_env(env, "HOME");
    int home_len = 0;

    if (home != NULL) {
        home_len = my_strlen(home);
        if (my_strncmp(way, home, home_len) == 0) {
            write(1, "~", 1);
            my_putstr(way + home_len);
            return;
        }
    }
    my_putstr(way);
}

/**
 * @brief Displays the shell prompt with user info and current directory
 *
 * @param env Array of the environment
 */
void print_shell_line(char **env)
{
    char way[200];

    if (getcwd(way, sizeof(way)) == NULL)
        way[0] = '\0';
    if (isatty(0)) {
        write(1, BLUE, my_strlen(BLUE));
        print_username(env);
        write(1, RESET, my_strlen(RESET));
        write(1, ":", 1);
        write(1, PURPLE, my_strlen(PURPLE));
        print_shorter_path(way, env);
        write(1, RESET, my_strlen(RESET));
        write(1, " $> ", 4);
    }
}
