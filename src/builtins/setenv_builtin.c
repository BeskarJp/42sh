/*
** EPITECH PROJECT, 2026
** Minishell 2
** File description:
** Execute setenv
*/

#include "shell.h"

/**
 * @brief Enlarges the environment array and adds a new line
 *
 * @param shell Shell structure
 * @param new_line String in the form "name=value" to add
 */
void make_env_bigger(shell_t *shell, char *new_line)
{
    char **new_env = NULL;
    int line_count = 0;

    while (shell->copy_env[line_count] != NULL)
        line_count++;
    new_env = malloc(sizeof(char *) * (line_count + 2));
    if (new_env == NULL)
        return;
    for (int i = 0; i < line_count; i++)
        new_env[i] = shell->copy_env[i];
    new_env[line_count] = new_line;
    new_env[line_count + 1] = NULL;
    free(shell->copy_env);
    shell->copy_env = new_env;
}

/**
 * @brief Checks that setenv arguments are valid
 *
 * @param shell Shell structure
 * @return int. 0 if valid or 84 if error
 */
int check_setenv(shell_t *shell)
{
    char alphabet = '\0';

    if (shell->arg_col[1] == NULL) {
        display_env(shell);
        return 84;
    }
    for (int i = 0; shell->arg_col[1][i] != '\0'; i++) {
        alphabet = shell->arg_col[1][i];
        if (!((alphabet >= 'a' && alphabet <= 'z') ||
                (alphabet >= 'A' && alphabet <= 'Z') ||
                (alphabet >= '0' && alphabet <= '9'))) {
            write(2, "setenv: Variable name must be alphanumeric.\n", 44);
            return 84;
        }
    }
    return 0;
}

/**
 * @brief Executes the setenv command (adds or modifies a variable).
 *
 * @param shell Shell structure.
 */
void exec_setenv(shell_t *shell)
{
    char *added_line = NULL;
    int len_name = 0;

    if (check_setenv(shell) == 84)
        return;
    len_name = my_strlen(shell->arg_col[1]);
    added_line = add_line_in_env(shell->arg_col[1], shell->arg_col[2]);
    for (int i = 0; shell->copy_env[i] != NULL; i++) {
        if (my_strncmp(shell->copy_env[i], shell->arg_col[1], len_name) == 0
            && shell->copy_env[i][len_name] == '=') {
            free(shell->copy_env[i]);
            shell->copy_env[i] = added_line;
            return;
        }
    }
    make_env_bigger(shell, added_line);
}
