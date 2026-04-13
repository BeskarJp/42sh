/*
** EPITECH PROJECT, 2026
** minishell.h
** File description:
** Include of Project
*/

#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include "my.h"

#ifndef MINISHELL
    #define MINISHELL


// Define color in shell

    #define BLUE "\e[1;94m"
    #define PURPLE "\e[1;95m"
    #define RESET "\033[0m"

// Define numbers in shell

    #define PERM_NORM 0644
    #define FD_ERROR -1

/**
 * @brief Define type for parse line command
 */
typedef enum node_type_e {
    SIMPLE_COMMAND,
    SEMICOLONS,
    PIPE,
    REDIR_DROITE,
    REDIR_DB_DROITE,
    REDIR_GAUCHE,
    REDIR_DB_GAUCHE,
} node_type_t;

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
 * @brief Shell basic struct
 */
typedef struct shell_s {
    int continue_shell;
    char **arg_col;
    char **copy_env;
    char *oldpwd;
    alias_t *aliases;
    history_t *history;
} shell_t;


// src/buitlins/features/aliases/alias_builtin.c
void exec_alias(shell_t *shell);

// src/buitlins/features/aliases/alias_utils.c
alias_t *find_alias_by_name(alias_t *aliases, char *name);
void add_alias(shell_t *shell, char *name, char *command);

// src/buitlins/features/aliases/unalias_builtin.c
void exec_unalias(shell_t *shell);

// src/buitlins/features/history/history_builtin.c
void add_to_history_linked_list(shell_t *shell, char *line);
void display_history(shell_t *shell);

// src/buitlins/features/history/history_feature.c
char *check_history_feature(shell_t *shell, char *line);

// src/buitlins/builtin_assembly.c
int builtin_assembly(shell_t *shell);

// src/buitlins/cd_builtin.c
void exec_cd(shell_t *shell);

// src/buitlins/env_builtin.c
void display_env(shell_t *shell);

// src/buitlins/setenv_builtin.c
void exec_setenv(shell_t *shell);

// src/buitlins/unsetenv_builtin.c
void exec_unsetenv(shell_t *shell);

// src/environment/env_interract.c
char **copy_environment(char **env);
char *find_word_in_env(char **env, char *word);
char *add_line_in_env(char *nom, char *valeur);

// src/environment/find_pathway.c
char *find_command_path(char *cmd, char **env);

// src/shell/shell_prompt_line.c
void print_shell_line(char **env);

// src/shell/shell_request.c
void execute_command(shell_t *shell);
void line_executor(shell_t *shell, char *line);

// src/token_tree/execution/features/aliases/alias_checker.c
void alias_checker(shell_t *shell, token_tree_t *arbre);

// src/token_tree/execution/exec_pipe.c
void run_pipe(shell_t *shell, token_tree_t *tree);

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
void free_cd(shell_t *shell);
void free_tree(token_tree_t *tree);

#endif /* MINISHELL */
