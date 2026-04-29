/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Main file for emac builtin
*/

#include "shell.h"

void loop_editor(char *line)
{
    int pid_count = 0;
    int len = my_strlen(line);

    while (pid_count != 24) {
        clear();
        printw("--- 42sh Emac (%s) ---\n", "(Ctrl + X: Save & Quit)");
        printw("%s", line);
        refresh();
        pid_count = getch();
        handle_emac_input(pid_count, line, &len);
    }
}

int check_emac_permissions(char *path)
{
    if (access(path, F_OK) == 0 && access(path, R_OK | W_OK) == -1) {
        write(2, "emac: No permissions for edit file\n", 35);
        return 1;
    }
    return 0;
}

int exec_emac(shell_t *shell)
{
    char *line = NULL;
    char *path = shell->arg_col[1];

    if (!path) {
        write(2, "emac: Missing filename\n", 24);
        return shell->exit_status = 1;
    }
    if (check_emac_permissions(path) == 1)
        return shell->exit_status = 1;
    line = load_file(path);
    initscr();
    raw();
    noecho();
    keypad(stdscr, TRUE);
    loop_editor(line);
    endwin();
    save_file(path, line);
    free(line);
    return shell->exit_status = 0;
}
