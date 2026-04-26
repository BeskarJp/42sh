/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Handle bash script execution fallback
*/

#include "shell.h"

static bool is_ident_char(char c)
{
    if (c >= 'a' && c <= 'z')
        return true;
    if (c >= 'A' && c <= 'Z')
        return true;
    if (c >= '0' && c <= '9')
        return true;
    return c == '_';
}

static bool has_keyword(char *line, char *key)
{
    char *found = strstr(line, key);
    int len = my_strlen(key);
    char before;
    char after;

    while (found != NULL) {
        before = (found == line) ? ' ' : *(found - 1);
        after = found[len];
        if (!is_ident_char(before) && !is_ident_char(after))
            return true;
        found = strstr(found + 1, key);
    }
    return false;
}

static bool is_bash_script_line(char *line)
{
    if (strstr(line, "[[") != NULL || strstr(line, "]]") != NULL)
        return true;
    if (strstr(line, "((") != NULL || strstr(line, "))") != NULL)
        return true;
    if (has_keyword(line, "function"))
        return true;
    if (has_keyword(line, "if") && has_keyword(line, "then"))
        return true;
    if (has_keyword(line, "for") && has_keyword(line, "do"))
        return true;
    if (has_keyword(line, "while") && has_keyword(line, "do"))
        return true;
    return has_keyword(line, "case") && has_keyword(line, "esac");
}

static void wait_bash_child(shell_t *shell, pid_t pid)
{
    int status = 0;

    if (shell->interactive)
        tcsetpgrp(shell->shell_terminal, pid);
    waitpid(pid, &status, WUNTRACED);
    if (WIFSIGNALED(status)) {
        check_strsignal(status);
        shell->exit_status = WTERMSIG(status) + 128;
    }
    if (WIFEXITED(status))
        shell->exit_status = WEXITSTATUS(status);
    if (shell->interactive)
        tcsetpgrp(shell->shell_terminal, shell->shell_pgid);
}

static void reset_child_signals(void)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    signal(SIGTSTP, SIG_DFL);
    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);
    signal(SIGCHLD, SIG_DFL);
}

static int run_bash_script(shell_t *shell, char *line)
{
    char *bash_args[] = {"/bin/bash", "-c", line, NULL};
    pid_t pid = fork();

    if (pid < 0)
        return 1;
    if (pid == 0) {
        reset_child_signals();
        setpgid(0, 0);
        if (execve("/bin/bash", bash_args, shell->copy_env) == -1) {
            check_execve_output_error("/bin/bash");
            exit(1);
        }
    }
    setpgid(pid, pid);
    wait_bash_child(shell, pid);
    return 0;
}

bool try_execute_bash_script(shell_t *shell, char *line)
{
    if (!is_bash_script_line(line))
        return false;
    if (run_bash_script(shell, line) != 0)
        shell->exit_status = 1;
    return true;
}
