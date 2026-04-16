/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Job control builtin commands
*/

#include "shell.h"

/**
 * @brief Finds a job by its id
 *
 * @param shell Shell structure
 * @param id Job identifier
 * @return job_t*. Matching job or NULL
 */
static job_t *find_job_by_id(shell_t *shell, int id)
{
    job_t *job = shell->jobs;

    while (job) {
        if (job->id == id)
            return job;
        job = job->next;
    }
    return NULL;
}

/**
 * @brief Returns the newest non-finished job
 *
 * @param shell Shell structure
 * @return job_t*. Latest active job or NULL
 */
static job_t *find_latest_job(shell_t *shell)
{
    job_t *job = shell->jobs;
    job_t *latest = NULL;

    while (job) {
        if (job->state != JOB_DONE)
            latest = job;
        job = job->next;
    }
    return latest;
}

/**
 * @brief Converts a foreground or background job reference to an id
 *
 * @param arg Argument provided to fg or bg
 * @return int. Parsed job id or -1
 */
static int parse_job_id(char *arg)
{
    if (!arg)
        return -1;
    if (arg[0] == '%')
        arg++;
    return my_getnbr(arg);
}

/**
 * @brief Converts a job state to a printable string
 *
 * @param state Job state
 * @return char*. Human-readable state label
 */
static char *job_state_to_string(job_state_t state)
{
    if (state == JOB_RUNNING)
        return "Running";
    if (state == JOB_STOPPED)
        return "Stopped";
    return "Done";
}

/**
 * @brief Prints the current job list
 *
 * @param shell Shell structure
 */
static void show_jobs(shell_t *shell)
{
    job_t *job = shell->jobs;

    while (job) {
        my_printf("[%d] %s %s\n", job->id,
            job_state_to_string(job->state), job->command);
        job = job->next;
    }
}

/**
 * @brief Waits for a foreground job to finish or stop
 *
 * @param job Job to wait for
 * @return int. Always returns 0
 */
static int wait_foreground_job(job_t *job)
{
    int status = 0;
    pid_t waited = waitpid(-job->pgid, &status, WUNTRACED);

    if (waited < 0)
        return 0;
    if (WIFSTOPPED(status)) {
        job->state = JOB_STOPPED;
        my_printf("[%d] Stopped %s\n", job->id, job->command);
    }
    if (WIFSIGNALED(status))
        check_strsignal(status);
    if (WIFEXITED(status) || WIFSIGNALED(status))
        job->state = JOB_DONE;
    return 0;
}

/**
 * @brief Selects the job referenced by the user or the latest active job
 *
 * @param shell Shell structure
 * @return job_t*. Selected job or NULL
 */
static job_t *pick_job(shell_t *shell)
{
    int id = parse_job_id(shell->arg_col[1]);

    if (id > 0)
        return find_job_by_id(shell, id);
    return find_latest_job(shell);
}

/**
 * @brief Displays the shell job list
 *
 * @param shell Shell structure
 * @return int. 1 because the builtin is handled
 */
int exec_jobs(shell_t *shell)
{
    refresh_jobs(shell);
    show_jobs(shell);
    notify_done_jobs(shell);
    return 1;
}

/**
 * @brief Brings a job back to the foreground
 *
 * @param shell Shell structure
 * @return int. 1 because the builtin is handled
 */
int exec_fg(shell_t *shell)
{
    job_t *job = NULL;

    refresh_jobs(shell);
    job = pick_job(shell);
    if (!job) {
        write(2, "fg: no such job\n", 16);
        return 1;
    }
    if (shell->interactive)
        tcsetpgrp(shell->shell_terminal, job->pgid);
    kill(-job->pgid, SIGCONT);
    job->state = JOB_RUNNING;
    wait_foreground_job(job);
    if (shell->interactive)
        tcsetpgrp(shell->shell_terminal, shell->shell_pgid);
    return 1;
}

/**
 * @brief Resumes a stopped job in the background
 *
 * @param shell Shell structure
 * @return int. 1 because the builtin is handled
 */
int exec_bg(shell_t *shell)
{
    job_t *job = NULL;

    refresh_jobs(shell);
    job = pick_job(shell);
    if (!job) {
        write(2, "bg: no such job\n", 16);
        return 1;
    }
    kill(-job->pgid, SIGCONT);
    job->state = JOB_RUNNING;
    my_printf("[%d] %s\n", job->id, job->command);
    return 1;
}
