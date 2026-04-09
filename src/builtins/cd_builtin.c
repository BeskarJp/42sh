/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Builtin of cd
*/

#include "shell.h"

/**
 * @brief Displays an error message for cd based by the type of problem
 *
 * @param path Target path for the cd command
 */
void cd_error_output(char *path)
{
    write(2, path, my_strlen(path));
    if (access(path, F_OK) == -1)
        write(2, ": No such file or directory.\n", 29);
    else
        write(2, ": Not a directory.\n", 19);
}

/**
 * @brief Determines the path to use for cd based on options
 *
 * @param shell Shell structure
 * @return char*. Calculated path or NULL
 */
char *check_cd_flag(shell_t *shell)
{
    char *path = shell->arg_col[1];

    if (path == NULL || my_strcmp(path, "~") == 0)
        path = find_word_in_env(shell->copy_env, "HOME");
    if (path == NULL)
        return NULL;
    if (my_strcmp(path, "-") == 0) {
        if (shell->oldpwd == NULL) {
            write(2, "cd: OLDPWD not set\n", 20);
            return NULL;
        }
        return shell->oldpwd;
    }
    return path;
}

/**
 * @brief Executes the cd command and updates OLDPWD
 *
 * @param shell Shell structure
 */
void exec_cd(shell_t *shell)
{
    char *path = check_cd_flag(shell);
    char *curr_dir = getcwd(NULL, 0);

    if (path == NULL) {
        if (curr_dir)
            free(curr_dir);
        return;
    }
    if (chdir(path) == -1) {
        cd_error_output(path);
        if (curr_dir)
            free(curr_dir);
    } else {
        if (shell->oldpwd)
            free(shell->oldpwd);
        shell->oldpwd = curr_dir;
    }
}
