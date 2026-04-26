/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Handle bash script execution fallback
*/

#include "shell.h"

/**
 * @brief Checks whether a character can be used in an identifier
 *
 * @param c Character to test
 * @return bool True when c is alphanumeric or '_'
 */
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

/**
 * @brief Finds a keyword as a standalone token in a line
 *
 * @param line Input line
 * @param key Keyword to detect
 * @return bool True when key is found as a complete token
 */
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

/**
 * @brief Detects lines that should be delegated to bash
 *
 * @param line Input line
 * @return bool True when bash-specific syntax is detected
 */
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

/**
 * @brief Waits for the bash child and updates shell status
 *
 * @param shell Shell structure
 * @param pid Child process id
 */
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

    /**
     * @brief Restores default signal handlers in the child process
     */
static void reset_child_signals(void)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    signal(SIGTSTP, SIG_DFL);
    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);
    signal(SIGCHLD, SIG_DFL);
}

/**
 * @brief Runs one command line through /bin/bash -c
 *
 * @param shell Shell structure
 * @param line Script line to execute
 * @return int 0 on success, 1 on fork error
 */
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

/**
 * @brief Tries to execute bash-style scripting syntax
 *
 * @param shell Shell structure
 * @param line Input line
 * @return bool True when the line was handled by this function
 */
bool try_execute_bash_script(shell_t *shell, char *line)
{
    if (!is_bash_script_line(line))
        return false;
    if (run_bash_script(shell, line) != 0)
        shell->exit_status = 1;
    return true;
}
