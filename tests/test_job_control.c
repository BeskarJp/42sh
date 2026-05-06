/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Job control unit tests
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "shell.h"

static void setup_shell(shell_t *shell)
{
    memset(shell, 0, sizeof(shell_t));
    shell->next_job_id = 1;
    shell->interactive = 0;
}

Test(job_control_core, add_job_builds_command)
{
    shell_t shell;
    char *args[] = {"echo", "hello", NULL};

    setup_shell(&shell);
    cr_assert_eq(add_job(&shell, 999999, args, JOB_RUNNING), 1);
    cr_assert_not_null(shell.jobs);
    cr_assert_eq(shell.jobs->id, 1);
    cr_assert_eq(shell.jobs->pgid, 999999);
    cr_assert_eq(shell.jobs->state, JOB_RUNNING);
    cr_assert_str_eq(shell.jobs->command, "echo hello");
    cr_assert_null(shell.jobs->next);
    free_jobs(shell.jobs);
}

Test(job_control_core, add_job_with_null_args_creates_empty_command)
{
    shell_t shell;

    setup_shell(&shell);
    cr_assert_eq(add_job(&shell, 999999, NULL, JOB_RUNNING), 1);
    cr_assert_not_null(shell.jobs);
    cr_assert_str_eq(shell.jobs->command, "");
    free_jobs(shell.jobs);
}

Test(job_control_core, notify_done_jobs_removes_done_job)
{
    shell_t shell;
    char *args[] = {"echo", "hello", NULL};

    setup_shell(&shell);
    cr_assert_eq(add_job(&shell, 999999, args, JOB_DONE), 1);
    cr_redirect_stdout();
    notify_done_jobs(&shell);
    cr_assert_stdout_eq_str("[1] Done echo hello\n");
    cr_assert_null(shell.jobs);
}

Test(job_control_builtins, exec_jobs_displays_job_list)
{
    shell_t shell;
    char *args1[] = {"echo", "hello", NULL};
    char *args2[] = {"sleep", "1", NULL};

    setup_shell(&shell);
    cr_assert_eq(add_job(&shell, 999998, args1, JOB_RUNNING), 1);
    cr_assert_eq(add_job(&shell, 999999, args2, JOB_STOPPED), 2);
    cr_redirect_stdout();
    cr_assert_eq(exec_jobs(&shell), 1);
    cr_assert_stdout_eq_str("[1] Running echo hello\n[2] Stopped sleep 1\n");
    free_jobs(shell.jobs);
}

Test(job_control_builtins, exec_fg_no_such_job)
{
    shell_t shell;
    char *args[] = {"fg", "%1", NULL};

    setup_shell(&shell);
    shell.arg_col = args;
    shell.jobs = NULL;
    cr_redirect_stderr();
    cr_assert_eq(exec_fg(&shell), 1);
    cr_assert_stderr_eq_str("fg: no such job\n");
}

Test(job_control_builtins, exec_bg_no_such_job)
{
    shell_t shell;
    char *args[] = {"bg", "%1", NULL};

    setup_shell(&shell);
    shell.arg_col = args;
    shell.jobs = NULL;
    cr_redirect_stderr();
    cr_assert_eq(exec_bg(&shell), 1);
    cr_assert_stderr_eq_str("bg: no such job\n");
}

Test(job_control_builtins, exec_fg_sets_job_running_when_job_exists)
{
    shell_t shell;
    char *args[] = {"fg", "%1", NULL};
    char *job_args[] = {"sleep", "1", NULL};

    setup_shell(&shell);
    shell.arg_col = args;
    cr_assert_eq(add_job(&shell, 999999, job_args, JOB_STOPPED), 1);
    cr_assert_eq(exec_fg(&shell), 1);
    cr_assert_eq(shell.jobs->state, JOB_RUNNING);
    free_jobs(shell.jobs);
}

Test(job_control_builtins, exec_bg_sets_job_running_and_prints)
{
    shell_t shell;
    char *args[] = {"bg", "%1", NULL};
    char *job_args[] = {"sleep", "1", NULL};

    setup_shell(&shell);
    shell.arg_col = args;
    cr_assert_eq(add_job(&shell, 999999, job_args, JOB_STOPPED), 1);
    cr_redirect_stdout();
    cr_assert_eq(exec_bg(&shell), 1);
    cr_assert_stdout_eq_str("[1] sleep 1\n");
    cr_assert_eq(shell.jobs->state, JOB_RUNNING);
    free_jobs(shell.jobs);
}
