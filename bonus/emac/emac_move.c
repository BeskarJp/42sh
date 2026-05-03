/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Function linked to scroll
*/

#include "shell.h"

/**
 * @brief Returns the current cursor column in the active line
 *
 * @param editor Editor state containing cursor and buffer
 * @return int Column index from the start of the current line
 */
int get_current_column(emacs_t *editor)
{
    int i = editor->cursor_in_file;
    int column = 0;

    while (i > 0 && editor->file_buffer[i - 1] != '\n') {
        i--;
        column++;
    }
    return column;
}

/**
 * @brief Moves the cursor one line up while preserving the column position
 *
 * @param editor Editor state containing cursor and buffer
 * @param column Desired column position in the previous line
 */
void move_up(emacs_t *editor, int column)
{
    int i = editor->cursor_in_file;

    while (i > 0 && editor->file_buffer[i - 1] != '\n')
        i--;
    if (i == 0)
        return;
    i--;
    while (i > 0 && editor->file_buffer[i - 1] != '\n')
        i--;
    for (int c = 0; c < column && editor->file_buffer[i] != '\n'; c++)
        i++;
    editor->cursor_in_file = i;
}

/**
 * @brief Moves the cursor one line down while preserving the column position
 *
 * @param editor Editor state containing cursor and buffer
 * @param column Desired column position in the next line
 */
void move_down(emacs_t *editor, int column)
{
    int i = editor->cursor_in_file;

    while (i < editor->text_len && editor->file_buffer[i] != '\n')
        i++;
    if (i >= editor->text_len)
        return;
    i++;
    for (int c = 0; c < column && i < editor->text_len
        && editor->file_buffer[i] != '\n'; c++)
        i++;
    editor->cursor_in_file = i;
}

/**
 * @brief Moves the cursor vertically based on the input direction
 *
 * @param editor Editor state containing cursor and buffer
 * @param direction Input key code for vertical movement
 */
void move_vertical(emacs_t *editor, int direction)
{
    int column = get_current_column(editor);

    if (direction == KEY_UP)
        move_up(editor, column);
    if (direction == KEY_DOWN)
        move_down(editor, column);
}
