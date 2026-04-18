/*
** EPITECH PROJECT, 2026
** echo_output
** File description:
** echo_output for 42sh
*/

#include "shell.h"

/**
 * @brief Executes the echo builtin command
 *
 * @param shell Shell structure
 */
int exec_echo(shell_t *shell)
{
    int i = 1;

    while (shell->arg_col[i] != NULL) {
        if (my_strcmp(shell->arg_col[i], "$?") == 0) {
            my_printf("%d", shell->exit_status);
        } else {
            my_printf("%s", shell->arg_col[i]);
        }
        if (shell->arg_col[i + 1] != NULL) {
            my_printf(" ");
        }
        i++;
    }
    my_printf("\n");
    shell->exit_status = 0;
    return 0;
}
