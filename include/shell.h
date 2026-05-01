/*
** EPITECH PROJECT, 2026
** minishell.h
** File description:
** Include of Project
*/

#include <sys/stat.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <dirent.h>
#include <glob.h>
#include <termios.h>
#include "my.h"

#ifndef MINISHELL
    #define MINISHELL


// Define color in shell

    #define ORANGE "\033[38;5;208m"
    #define BLUE "\e[1;94m"
    #define PURPLE "\e[1;95m"
    #define GREY "\033[90m"
    #define RESET "\033[0m"
    #define STYLE_BOLD "\033[1m"

// Define speed of write for Epi Claude

    #define FAST 20000
    #define BASIC 40000
    #define SLOW 50000
    #define ULTRA_SLOW 175000

// Define numbers in shell

    #define PERM_NORM 0644
    #define FD_ERROR -1


/**
 * @brief Define type for parse line command
 */
typedef enum node_type_e {
    SIMPLE_COMMAND,
    SEMICOLONS,
    AND_OPERATOR,
    OR_OPERATOR,
    PIPE,
    REDIR_DROITE,
    REDIR_DB_DROITE,
    REDIR_GAUCHE,
    REDIR_DB_GAUCHE,
} node_type_t;

/**
 * @brief Variables for the line edition
 */
typedef struct line_edition_s {
    char *entire_line;
    char *arrow_key;
    char key;
    struct termios config;
    struct termios config_copy;
    int i;
    int cursor_spot;
} line_edition_t;

/**
 * @brief Variables for the inhibitors
 */
typedef struct inhibitors_s {
    char *user;
} inhibitors_t;

/**
 * @brief Node of the parsed command tree
 */
typedef struct token_tree_s {
    node_type_t type;
    char **args;
    char *file;
    struct token_tree_s *left;
    struct token_tree_s *right;
} token_tree_t;

/**
 * @brief Parser for branch creation
 */
typedef struct struct_parse_s {
    int type;
    int count_stopped;
    int end_line;
    token_tree_t *(*left_function)(char *);
    token_tree_t *(*right_function)(char *);
} struct_parse_t;

/**
 * @brief Linked list of aliases
 */
typedef struct alias_s {
    char *name;
    char *command;
    struct alias_s *next;
} alias_t;

/**
 * @brief Linked list of history
 */
typedef struct history_s {
    int index;
    char *command;
    char *time;
    struct history_s *next;
} history_t;

/**
 * @brief Linked list for local env variables
 */
typedef struct env_s {
    char *var;
    char *value;
    int temp;
    struct env_s *next;
} env_t;

/**
 * @brief State of a shell job
 */
typedef enum job_state_e {
    JOB_RUNNING,
    JOB_STOPPED,
    JOB_DONE,
} job_state_t;

/**
 * @brief Linked list of jobs for job control
 */
typedef struct job_s {
    int id;
    pid_t pgid;
    char *command;
    job_state_t state;
    struct job_s *next;
} job_t;

/**
 * @brief Shell basic struct
 */
typedef struct shell_s {
    int continue_shell;
    char **arg_col;
    char **copy_env;
    char *oldpwd;
    env_t *local_env;
    alias_t *aliases;
    history_t *history;
    inhibitors_t *inhibitors;
    line_edition_t *le;
    job_t *jobs;
    int next_job_id;
    pid_t shell_pgid;
    int shell_terminal;
    int interactive;
    int exit_status;
} shell_t;


// bonus/echo_output/echo_output.c
int exec_echo(shell_t *shell);

// bonus/easter-egg/epiclaude_encyclo.c
void print_more_of_command(char *command);

// bonus/easter-egg/claude_explain.c
void explain_tree(token_tree_t *tree, int *step);
void explain_command_line(char *command);

// bonus/ester-egg/claude_input.c
void handle_input(char *line);

// bonus/ester-egg/claude_print.c
void print_header(shell_t *shell);
void print_explication_shell(void);

// bonus/easter-egg/claude_utils.c
char *user_of_shell(char **env);
void display_line_in_file(char *line_in_file, int size);
void ia_style_text_writer(char *text, int speed);

// bonus/easter-egg/claude.c
void start_claude(shell_t *shell);

// bonus/travis_builtin/travis_builtin.c
void bonus_builtin_ascii_art_cactus(void);

// src/buitlins/features/aliases/alias_builtin.c
void exec_alias(shell_t *shell);

// src/builtins/features/aliases/alias_utils.c
alias_t *find_alias_by_name(alias_t *aliases, char *name);
void add_alias(shell_t *shell, char *name, char *command);

// src/buitlins/features/aliases/unalias_builtin.c
void delete_alias_node(shell_t *shell, alias_t *aliases, alias_t *old);

// src/builtins/features/aliases/unalias_builtin.c
void exec_unalias(shell_t *shell);

// src/builtins/features/history/history_builtin.c
void add_to_history_linked_list(shell_t *shell, char *line);
void display_history(shell_t *shell);

// src/builtins/features/history/history_feature.c
char *check_history_feature(shell_t *shell, char *line);

// src/nuiltins/features/inhibitors/inhibitors.c
int check_user(char *line, shell_t *env);

// src/builtins/features/variables/export_builtin.c
void export_builtin(shell_t *shell);
void export_helper(shell_t *shell, env_t *var);
env_t *find_var_by_name(env_t *local, char *name);

// src/builtins/features/variables/var_declared.c
int var_declared(shell_t *shell, int n);

// src/builtins/features/variables/local_env_utils.c
void display_local_env(shell_t *shell);
void add_to_local_env(shell_t *shell, char *line, int state);
void rm_local_env_var(shell_t *shell, char *name);
void handle_local_var(shell_t *shell);
void local_var_only(shell_t *shell);

// src/builtins/features/variables/temp_var.c
void local_and_cmd(shell_t *shell);

// src/builtins/features/variables/set_unset_builtin.c
int set_builtin(shell_t *shell);
int unset_builtin(shell_t *shell);

// src/builtins/features/special_var/cwd_builtin.c
void cwd_builtin(shell_t *shell);

//src/builtins/features/wh_builtins/wh_utils.c
int check_if_builtin(char *command);
void print_when_where_match(char *copy_pathway, char *command);

//src/builtins/features/wh_builtins/where_builtin.c
void exec_where(shell_t *shell);

//src/builtins/features/wh_builtins/which_builtin.c
void exec_which(shell_t *shell);

// src/builtins/builtin_assembly.c
int builtin_assembly(shell_t *shell);

// src/builtins/cd_builtin.c
void exec_cd(shell_t *shell);

// src/builtins/env_builtin.c
void display_env(shell_t *shell);

// src/builtins/setenv_builtin.c
void exec_setenv(shell_t *shell);
void make_env_bigger(shell_t *shell, char *new_line);

// src/builtins/unsetenv_builtin.c
void exec_unsetenv(shell_t *shell);

// src/environment/env_interract.c
char **copy_environment(char **env);
char *find_word_in_env(char **env, char *word);
char *add_line_in_env(char *nom, char *valeur);

// src/environment/find_pathway.c
char *create_path_way(char *dir, char *command);
char *find_command_path(char *cmd, char **env);

// src/job_control/job_control.c
void init_job_control(shell_t *shell);
void refresh_jobs(shell_t *shell);
void notify_done_jobs(shell_t *shell);
int add_job(shell_t *shell, pid_t pgid, char **args, job_state_t state);
int exec_jobs(shell_t *shell);
int exec_fg(shell_t *shell);
int exec_bg(shell_t *shell);

// src/line_edition/arrow.c
void check_arrows(shell_t *shell);

// src/line_edition/keys.c
int handle_ctrl_d(line_edition_t *le);
int handle_keys(shell_t *keys);
int handle_backspace(line_edition_t *le);

// src/line_edition/line_edition.c
line_edition_t *check_config(line_edition_t *le);
char *key_loop(shell_t *shell);
char *detect_keys(shell_t *shell);

// src/shell/backticks/backticks_utils.c
char *read_pipe(int fd);
char *rebuild_line(char *line, int start, int end, char *out);

// src/shell/backticks/backticks.c
char *handle_backticks(shell_t *shell, char *line);

// src/shell/shell_prompt_line.c
void print_shell_line(char **env);

// src/shell/shell_request.c
void execute_command(shell_t *shell);
void line_executor(shell_t *shell, char *line);

// src/shell/shell_scripting.c
bool try_execute_bash_script(shell_t *shell, char *line);

// src/token_tree/execution/features/aliases/alias_checker.c
void alias_checker(shell_t *shell, token_tree_t *tree);

//src/token_tree/execution/exec_operators.c
void exec_operators(shell_t *shell, token_tree_t *tree);

// src/token_tree/execution/exec_pipe.c
void run_pipe(shell_t *shell, token_tree_t *tree);

// src/token_tree/execution/exec_globbings.c
int is_globbing_pattern(char *str);
int count_args(char **args);
int append_match(char ***exp, int *count, int *cap, char *str);
char **collect_matches(char *pattern);
int expand_all_args(char **args, char **expanded, int *count, int *capacity);
char **expand_globbing(char **args);

// src/token_tree/execution/exec_redirection_utils.c
void left_double_redirection(char *delimiter);

// src/token_tree/execution/exec_redirection.c
void run_redirection(shell_t *shell, token_tree_t *tree);

// src/token_tree/execution/exec_tree.c
void run_tree(shell_t *shell, token_tree_t *tree);

// src/token_tree/parse/clean_string.c
char *clear_string(char *str, int start, int end);

// src/token_tree/parse/parse_utils.c
token_tree_t *create_branch_by_type(node_type_t type);
token_tree_t *create_redirection_branch(char *line,
    int i, int len, node_type_t type);
token_tree_t *cut_branch(char *line, struct_parse_t *data);

// src/token_tree/parse/parser.c
token_tree_t *parse_redirections(char *line);
token_tree_t *parse_line(char *line);

// src/error.c
void handle_sigint(int sigint);
void check_execve_output_error(char *path);
void check_strsignal(int status);

// src/free.c
void free_array(char **array);
void free_aliases(alias_t *aliases);
void free_history(history_t *history);
void free_jobs(job_t *jobs);
void free_tree(token_tree_t *tree);

#endif /* MINISHELL */
