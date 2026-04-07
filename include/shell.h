/*
** EPITECH PROJECT, 2026
** minishell.h
** File description:
** Include of Project
*/

#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include "my.h"

#ifndef MINISHELL
    #define MINISHELL

    #define BLUE "\e[1;94m"
    #define PURPLE "\e[1;95m"
    #define RESET "\033[0m"
    #define PERM_NORM 0644
    #define FD_ERROR -1

typedef enum node_type_e {
    SIMPLE_COMMAND,
    SEMICOLONS,
    PIPE,
    REDIR_DROITE,
    REDIR_DB_DROITE,
    REDIR_GAUCHE,
    REDIR_DB_GAUCHE,
} node_type_t;

typedef struct token_tree_s {
    node_type_t type;
    char **args;
    char *file;
    struct token_tree_s *left;
    struct token_tree_s *right;
} token_tree_t;

typedef struct struct_parse_s {
    int type;
    int count_stopped;
    int end_line;
    token_tree_t *(*left_function)(char *);
    token_tree_t *(*right_function)(char *);
} struct_parse_t;

typedef struct history_s {
    int index;
    char *command;
    char *time;
    struct history_s *next;
} history_t;

typedef struct shell_s {
    int continue_shell;
    char **arg_col;
    char **copy_env;
    char *oldpwd;
    history_t *history;
} shell_t;


void add_to_history_linked_list(shell_t *shell, char *line);
void display_history(shell_t *shell);
char *check_history_feature(shell_t *shell, char *line);


int builtin_assembly(shell_t *shell);
void exec_cd(shell_t *shell);
void display_env(shell_t *shell);
void exec_setenv(shell_t *shell);
void exec_unsetenv(shell_t *shell);

char **copy_environment(char **env);
char *find_word_in_env(char **env, char *word);
char *add_line_in_env(char *nom, char *valeur);
char *find_command_path(char *cmd, char **env);

void print_shell_line(char **env);
void execute_command(shell_t *shell);
void line_executor(shell_t *shell, char *line);


void run_pipe(shell_t *shell, token_tree_t *tree);
void left_double_redirection(char *delimiter);
void run_redirection(shell_t *shell, token_tree_t *tree);
void run_tree(shell_t *shell, token_tree_t *tree);

char *clear_string(char *str, int start, int end);
token_tree_t *create_branch_by_type(node_type_t type);
token_tree_t *create_redirection_branch(char *line,
    int i, int len, node_type_t type);
token_tree_t *cut_branch(char *line, struct_parse_t *data);

token_tree_t *parse_redirections(char *line);
token_tree_t *parse_line(char *line);

void check_execve_output_error(char *path);
void check_strsignal(int status);
void free_array(char **array);
void free_history(history_t *history);
void free_cd(shell_t *shell);
void free_tree(token_tree_t *tree);

#endif /* MINISHELL */
