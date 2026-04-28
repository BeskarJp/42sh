/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Handle backticks command substitution
*/

#include "shell.h"

char *exec_backtick(shell_t *shell, char *command)
{
    char *out = NULL;
    int pfd[2];
    pid_t pid;

    if (pipe(pfd) == -1)
        return my_strdup("");
    pid = fork();
    if (pid == 0) {
        dup2(pfd[1], STDOUT_FILENO);
        close(pfd[0]);
        close(pfd[1]);
        line_executor(shell, command);
        exit(0);
    }
    close(pfd[1]);
    out = read_pipe(pfd[0]);
    close(pfd[0]);
    waitpid(pid, NULL, 0);
    return out;
}

void find_backticks(char *line, int *indices)
{
    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == '`' && indices[0] == -1) {
            indices[0] = i;
            continue;
        }
        if (line[i] == '`' && indices[0] != -1) {
            indices[1] = i;
            break;
        }
    }
}

char *handle_backticks(shell_t *shell, char *line)
{
    int indices[2] = {-1, -1};
    char *command = NULL;
    char *out = NULL;
    char *new_line = NULL;

    find_backticks(line, indices);
    if (indices[0] == -1 || indices[1] == -1)
        return line;
    command = clear_string(line, indices[0] + 1, indices[1]);
    out = exec_backtick(shell, command);
    new_line = rebuild_line(line, indices[0], indices[1], out);
    free(command);
    free(out);
    free(line);
    return handle_backticks(shell, new_line);
}
