/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Handle shell_line
*/

#include "shell.h"

/**
 * @brief Detects a trailing background token and removes it from argv
 *
 * @param shell Shell structure
 * @return bool. True when the command should run in background
 */
static bool command_is_background(shell_t *shell)
{
    int count = 0;

    while (shell->arg_col[count] != NULL)
        count++;
    if (count == 0)
        return false;
    if (my_strcmp(shell->arg_col[count - 1], "&") != 0)
        return false;
    free(shell->arg_col[count - 1]);
    shell->arg_col[count - 1] = NULL;
    return true;
}

/**
 * @brief Restores the default child signal handlers before execve
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
 * @brief Prints the not found error for the current command
 *
 * @param shell Shell structure
 * @return int. Always returns 0
 */
static int handle_not_found(shell_t *shell)
{
    write(2, shell->arg_col[0], my_strlen(shell->arg_col[0]));
    write(2, ": Command not found.\n", 21);
    shell->exit_status = 1;
    return 0;
}

/**
 * @brief Prepares a child process for command execution
 *
 * @param shell Shell structure
 * @param path Resolved executable path
 * @param is_background True when the command runs in background
 */
static void execute_child(shell_t *shell, char *path, bool is_background)
{
    reset_child_signals();
    setpgid(0, 0);
    if (shell->interactive && !is_background)
        tcsetpgrp(shell->shell_terminal, getpid());
    if (execve(path, shell->arg_col, shell->copy_env) == -1) {
        check_execve_output_error(path);
        exit(1);
    }
}

/**
 * @brief Registers a background job after fork
 *
 * @param shell Shell structure
 * @param pid Child process id
 */
static void handle_background_job(shell_t *shell, pid_t pid)
{
    int job_id = add_job(shell, pid, shell->arg_col, JOB_RUNNING);

    if (job_id > 0)
        my_printf("[%d] %d\n", job_id, pid);
}

/**
 * @brief Stores a stopped foreground job in the job list
 *
 * @param shell Shell structure
 * @param pid Child process id
 */
static void handle_stopped_job(shell_t *shell, pid_t pid)
{
    int job_id = add_job(shell, pid, shell->arg_col, JOB_STOPPED);

    if (job_id > 0)
        my_printf("[%d] Stopped %s\n", job_id, shell->arg_col[0]);
}

/**
 * @brief Waits for a foreground job and restores the shell terminal
 *
 * @param shell Shell structure
 * @param pid Child process id
 */
static void handle_foreground_job(shell_t *shell, pid_t pid)
{
    int status = 0;

    if (shell->interactive)
        tcsetpgrp(shell->shell_terminal, pid);
    waitpid(pid, &status, WUNTRACED);
    if (WIFSTOPPED(status))
        handle_stopped_job(shell, pid);
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
 * @brief Updates the parent side of a forked command execution
 *
 * @param shell Shell structure
 * @param pid Child process id
 * @param is_background True when the command runs in background
 */
static void handle_parent(shell_t *shell, pid_t pid, bool is_background)
{
    setpgid(pid, pid);
    if (is_background)
        handle_background_job(shell, pid);
    if (!is_background)
        handle_foreground_job(shell, pid);
}

/**
 * @brief Executes an external command in a child process
 *
 * @param shell Shell structure
 */
void execute_command(shell_t *shell)
{
    char *path = find_command_path(shell->arg_col[0], shell->copy_env);
    pid_t pid;
    bool is_background = command_is_background(shell);

    if (!shell->arg_col[0])
        return;
    if (path == NULL) {
        handle_not_found(shell);
        return;
    }
    pid = fork();
    if (pid == 0)
        execute_child(shell, path, is_background);
    if (pid > 0)
        handle_parent(shell, pid, is_background);
    free(path);
}

/**
 * @brief Parses and executes a command line entered by the user
 *
 * @param shell Shell structure
 * @param line Command line to process
 */
void line_executor(shell_t *shell, char *line)
{
    token_tree_t *tree = NULL;
    bool is_user = false;

    if (!line || line[0] == '\0')
        return;
    if (check_user(line, shell) == 1)
        is_user = true;
    if (is_user == false) {
        if (try_execute_bash_script(shell, line)) {
            return;
        }
        tree = parse_line(line);
        if (tree != NULL) {
            shell->current_line = line;
            run_tree(shell, tree);
            shell->current_line = NULL;
            free_tree(tree);
        }
    }
}
