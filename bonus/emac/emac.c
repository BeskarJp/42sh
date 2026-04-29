/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Main file for emac builtin
*/

#include "shell.h"

void base_of_emac_visual(emacs_t *editor)
{
    int x = 0;
    int y = 1;

    clear();
    mvprintw(0, 0,
        "### emac: %s ('Ctrl + S' for Save and  'Ctrl + X' for Quit) ###",
        editor->pathline);
    mvprintw(1, 0, "%s", editor->file_buffer);
    for (int i = 0; i < editor->cursor_in_file; i++) {
        if (editor->file_buffer[i] == '\n') {
            y++;
            x = 0;
        } else
            x++;
    }
    move(y, x);
    refresh();
}

void run_editor_loop(emacs_t *editor)
{
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    while (editor->running) {
        base_of_emac_visual(editor);
        handle_emac_input(getch(), editor);
    }
    endwin();
}

int exec_emac(shell_t *shell)
{
    emacs_t editor;

    if (!shell->arg_col[1]) {
        write(2, "emac: Need file\n", 16);
        return 1;
    }
    editor.pathline = shell->arg_col[1];
    editor.file_buffer = load_emac_file(editor.pathline);
    if (!editor.file_buffer)
        return 1;
    editor.text_len = my_strlen(editor.file_buffer);
    editor.cursor_in_file = editor.text_len;
    editor.running = 1;
    run_editor_loop(&editor);
    free(editor.file_buffer);
    return 0;
}
