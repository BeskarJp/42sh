/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Functions linked to file edit
*/

#include "shell.h"

/**
 * @brief Inserts a character into the editor buffer at the cursor position
 *
 * @param editor Editor state containing file buffer and cursor
 * @param pid_count Character code to insert
 */
void insert_character(emacs_t *editor, int pid_count)
{
    if (editor->text_len >= 4094)
        return;
    for (int i = editor->text_len; i > editor->cursor_in_file; i--)
        editor->file_buffer[i] = editor->file_buffer[i - 1];
    editor->file_buffer[editor->cursor_in_file] = (char)pid_count;
    editor->cursor_in_file++;
    editor->text_len++;
    editor->file_buffer[editor->text_len] = '\0';
}

/**
 * @brief Deletes the character immediately before the cursor
 *
 * @param editor Editor state containing file buffer and cursor
 */
void delete_character(emacs_t *editor)
{
    if (editor->cursor_in_file <= 0)
        return;
    for (int i = editor->cursor_in_file - 1; i < editor->text_len; i++)
        editor->file_buffer[i] = editor->file_buffer[i + 1];
    editor->cursor_in_file--;
    editor->text_len--;
    editor->file_buffer[editor->text_len] = '\0';
}

/**
 * @brief Handles keyboard input for the Emacs-like editor
 *
 * @param pid_count Input key code or character
 * @param editor Editor state to update
 */
void handle_emac_input(int pid_count, emacs_t *editor)
{
    if (pid_count == 24)
        editor->running = 0;
    if (pid_count == 19)
        save_emac_file(editor);
    if (pid_count == KEY_LEFT && editor->cursor_in_file > 0)
        editor->cursor_in_file--;
    if (pid_count == KEY_RIGHT && editor->cursor_in_file < editor->text_len)
        editor->cursor_in_file++;
    if (pid_count == KEY_UP || pid_count == KEY_DOWN)
        move_vertical(editor, pid_count);
    if (pid_count == KEY_BACKSPACE || pid_count == 127)
        delete_character(editor);
    if ((pid_count >= 32 && pid_count <= 126) || pid_count == '\n')
        insert_character(editor, pid_count);
}
