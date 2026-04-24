/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Job control core helpers
*/

#include "shell.h"

/**
 * @brief Copies one command word into a job command buffer
 *
 * @param dst Destination buffer
 * @param src Source word
 * @param start Write offset in the destination buffer
 * @return int. New write offset after the copy
 */
static int copy_word(char *dst, char *src, int start)
{
    int i = start;

    for (int j = 0; src[j] != '\0'; j++) {
        dst[i] = src[j];
        i++;
    }
    return i;
}

/**
 * @brief Builds a printable command line from the current argument array
 *
 * @param args Command arguments
 * @return char*. Allocated command string or NULL
 */
static char *build_command_from_args(char **args)
{
    int size = 1;
    char *command = NULL;
    int index = 0;

    if (!args || !args[0])
        return my_strdup("");
    for (int i = 0; args[i] != NULL; i++)
        size += my_strlen(args[i]) + 1;
    command = malloc(sizeof(char) * size);
    if (!command)
        return NULL;
    for (int i = 0; args[i] != NULL; i++) {
        index = copy_word(command, args[i], index);
        if (args[i + 1] != NULL) {
            command[index] = ' ';
            index++;
        }
    }
    command[index] = '\0';
    return command;
}

/**
 * @brief Finds a job by its process group id
 *
 * @param shell Shell structure
 * @param pgid Process group id
 * @return job_t*. Matching job or NULL
 */
static job_t *find_job_by_pgid(shell_t *shell, pid_t pgid)
{
    job_t *job = shell->jobs;

    while (job) {
        if (job->pgid == pgid)
            return job;
        job = job->next;
    }
    return NULL;
}

/**
 * @brief Removes a job from the shell job list
 *
 * @param shell Shell structure
 * @param target Job node to remove
 */
static void remove_job(shell_t *shell, job_t *target)
{
    job_t *job = shell->jobs;
    job_t *prev = NULL;

    while (job && job != target) {
        prev = job;
        job = job->next;
    }
    if (!job)
        return;
    if (!prev)
        shell->jobs = job->next;
    if (prev)
        prev->next = job->next;
    free(job->command);
    free(job);
}

/**
 * @brief Updates a job state from a wait status value
 *
 * @param job Job to update
 * @param status Status returned by waitpid
 */
static void update_job_state(job_t *job, int status)
{
    if (WIFSTOPPED(status))
        job->state = JOB_STOPPED;
#ifdef WCONTINUED
    if (WIFCONTINUED(status))
        job->state = JOB_RUNNING;
#endif
    if (WIFEXITED(status) || WIFSIGNALED(status))
        job->state = JOB_DONE;
}

/**
 * @brief Initializes interactive job-control state for the shell
 *
 * @param shell Shell structure
 */
void init_job_control(shell_t *shell)
{
    shell->shell_terminal = STDIN_FILENO;
    shell->shell_pgid = getpid();
    shell->interactive = isatty(shell->shell_terminal);
    signal(SIGTTOU, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    if (!shell->interactive)
        return;
    setpgid(shell->shell_pgid, shell->shell_pgid);
    tcsetpgrp(shell->shell_terminal, shell->shell_pgid);
}

/**
 * @brief Adds a job to the shell job list
 *
 * @param shell Shell structure
 * @param pgid Process group id
 * @param args Command arguments used to build the display string
 * @param state Initial job state
 * @return int. New job id or -1 on error
 */
int add_job(shell_t *shell, pid_t pgid, char **args, job_state_t state)
{
    job_t *new_job = malloc(sizeof(job_t));
    job_t *last = shell->jobs;
    int current_id = shell->next_job_id;

    if (!new_job)
        return -1;
    shell->next_job_id++;
    new_job->id = current_id;
    new_job->pgid = pgid;
    new_job->command = build_command_from_args(args);
    new_job->state = state;
    new_job->next = NULL;
    if (!shell->jobs)
        shell->jobs = new_job;
    while (last && last->next)
        last = last->next;
    if (last)
        last->next = new_job;
    return new_job->id;
}

/**
 * @brief Refreshes job states using non-blocking waitpid
 *
 * @param shell Shell structure
 */
void refresh_jobs(shell_t *shell)
{
    int status = 0;
    pid_t pid = 0;
    job_t *job = NULL;
    int flags = WNOHANG | WUNTRACED;

#ifdef WCONTINUED
    flags |= WCONTINUED;
#endif
    pid = waitpid(-1, &status, flags);
    while (pid > 0) {
        job = find_job_by_pgid(shell, pid);
        if (job)
            update_job_state(job, status);
        pid = waitpid(-1, &status, flags);
    }
}

/**
 * @brief Prints and removes jobs that reached the done state
 *
 * @param shell Shell structure
 */
void notify_done_jobs(shell_t *shell)
{
    job_t *job = shell->jobs;
    job_t *next = NULL;

    while (job) {
        next = job->next;
        if (job->state == JOB_DONE) {
            my_printf("[%d] Done %s\n", job->id, job->command);
            remove_job(shell, job);
        }
        job = next;
    }
}

/**
 * @brief Frees the shell job list
 *
 * @param jobs Job list head
 */
void free_jobs(job_t *jobs)
{
    job_t *next = NULL;

    while (jobs) {
        next = jobs->next;
        free(jobs->command);
        free(jobs);
        jobs = next;
    }
}
