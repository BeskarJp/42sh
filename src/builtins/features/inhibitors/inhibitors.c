/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** inhibitors
*/

#include "shell.h"

/**
 * @brief Get the user via env
 *
 * @param env Shell structure to get the env
 */
char *get_user(shell_t *env)
{
    char **user = NULL;

    for (int i = 0; env->copy_env[i] != NULL; i++) {
        user = my_str_to_sep_array(env->copy_env[i], "=");
        if (my_strcmp(user[0], "USER") == 0) {
            env->inhibitors->user = my_strdup(user[1]);
            free_array(user);
            return env->inhibitors->user;
        }
        free_array(user);
    }
    return NULL;
}

/**
 * @brief If the function detect "$USER", it will remplace it with the user
 * found in the env copy
 *
 * @param user_env as the name suggest, the user in the env
 * @param env Shell structure to get the user in the env
 * @param arg Lines argument
 */
int display_user(char *user_env, shell_t *env, char *arg)
{
    if (my_strcmp(arg, "\"$USER\"") == 0) {
        user_env = get_user(env);
        if (user_env == NULL) {
            printf("USER: Undefined variable.\n");
            return 1;
        }
        printf("%s\n", user_env);
        free(env->inhibitors->user);
        return 1;
    }
    return 0;
}

/**
 * @brief Malloc the structure and return 1 if display_user
 * @brief also return 1, bascically a verification
 *
 * @param line Command line to process
 * @param env Shell structure of the env
 */
int check_user(char *line, shell_t *env)
{
    char **arg = my_str_to_sep_array(line, " ");
    char *user_env = NULL;

    env->inhibitors = malloc(sizeof(inhibitors_t));
    if (!env->inhibitors)
        return 84;
    for (int i = 0; arg[i] != NULL; i++) {
        if (display_user(user_env, env, arg[i]) == 1) {
            free_array(arg);
            free(env->inhibitors);
            return 1;
        }
    }
    free_array(arg);
    free(env->inhibitors);
    return 0;
}
