/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Main file for emac builtin
*/

#include "shell.h"

/**
 * @brief Draws the Emacs-like editor interface and positions the cursor
 *
 * @param editor Editor state containing buffer and path information
 */
void base_of_emac_visual(emacs_t *editor)
{
    int x = 0;
    int y = 1;

    clear();
    attron(A_REVERSE);
    mvprintw(0, 0,
        "###   emac: %s 'Ctrl + S' for Save and  'Ctrl + X' for Quit   ###",
        editor->pathline);
    attroff(A_REVERSE);
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

/**
 * @brief Runs the main input loop for the Emacs-like editor
 *
 * @param editor Editor state used during the editing session
 */
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

/**
 * @brief Executes the emac builtin command
 *
 * @param shell Shell structure
 * @return int. 0 on success if fail
 */
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
    editor.cursor_in_file = 0;
    editor.running = 1;
    run_editor_loop(&editor);
    free(editor.file_buffer);
    return 0;
}
