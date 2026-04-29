##
## EPITECH PROJECT, 2026
## Makefile
## File description:
## Makefile of project
##

CC = 	epiclang

CFLAGS	= -Wall -Wextra -I./include

TFLAGS	=	--coverage -lcriterion

SRC	=	lib/my/mini_printf.c	\
		lib/my/my_getnbr.c	\
		lib/my/my_put_nbr.c	\
		lib/my/my_putchar.c	\
		lib/my/my_putstr.c	\
		lib/my/my_str_to_sep_array.c	\
		lib/my/my_str_to_word_array.c	\
		lib/my/my_strcat.c	\
		lib/my/my_strcmp.c	\
		lib/my/my_strcpy.c	\
		lib/my/my_strdup.c	\
		lib/my/my_strlen.c	\
		lib/my/my_strncmp.c	\
		lib/my/str_nfuse.c	\
		bonus/echo_output/echo_output.c	\
		bonus/emac/emac_file.c	\
		bonus/emac/emac_input.c	\
		bonus/emac/emac_move.c	\
		bonus/emac/emac.c	\
		bonus/epiclaude/epiclaude_encyclo.c	\
		bonus/epiclaude/epiclaude_explain.c	\
		bonus/epiclaude/epiclaude_input.c	\
		bonus/epiclaude/epiclaude_print.c	\
		bonus/epiclaude/epiclaude_utils.c	\
		bonus/epiclaude/epiclaude.c	\
		bonus/travis_builtin/travis_builtin.c	\
		src/builtins/features/aliases/alias_builtin.c	\
		src/builtins/features/aliases/alias_utils.c	\
		src/builtins/features/aliases/unalias_builtin.c	\
		src/builtins/features/history/history_builtin.c	\
		src/builtins/features/history/history_feature.c	\
		src/builtins/features/inhibitors/inhibitors.c	\
		src/builtins/features/wh_builtins/wh_utils.c	\
		src/builtins/features/wh_builtins/where_builtin.c	\
		src/builtins/features/wh_builtins/which_builtin.c	\
		src/builtins/features/variables/local_env_utils.c	\
		src/builtins/features/variables/var_declared.c	\
		src/builtins/features/variables/export_builtin.c	\
		src/builtins/features/variables/set_unset_builtin.c	\
		src/builtins/features/variables/temp_var.c	\
		src/builtins/builtin_assembly.c	\
		src/builtins/cd_builtin.c	\
		src/builtins/env_builtin.c	\
		src/builtins/setenv_builtin.c	\
		src/builtins/unsetenv_builtin.c	\
		src/environment/env_interract.c	\
		src/environment/find_pathway.c	\
		src/job_control/job_control_core.c	\
		src/job_control/job_control_builtins.c	\
		src/shell/backticks/backticks_utils.c	\
		src/shell/backticks/backticks.c	\
		src/shell/shell_prompt_line.c	\
		src/shell/shell_scripting.c	\
		src/shell/shell_request.c	\
		src/token_tree/execution/features/aliases/alias_checker.c	\
		src/token_tree/execution/exec_globbings_utils.c	\
		src/token_tree/execution/exec_globbings.c	\
		src/token_tree/execution/exec_operators.c	\
		src/token_tree/execution/exec_pipe.c	\
		src/token_tree/execution/exec_redirection_utils.c	\
		src/token_tree/execution/exec_redirection.c	\
		src/token_tree/execution/exec_tree.c	\
		src/token_tree/parse/clean_string.c	\
		src/token_tree/parse/parse_utils.c	\
		src/token_tree/parse/parser.c	\
		src/error.c	\
		src/free.c	\
		src/main.c

OBJ	=	$(SRC:.c=.o)

NAME	=	42sh

SRC_TESTS	=	$(filter-out src/main.c, $(SRC))

TESTS_FILES	=	tests/test_builtins.c	\
				tests/test_env.c	\
				tests/test_exec_utils.c	\
				tests/test_exec.c	\
				tests/test_parsing.c

NAME_TEST	=	unit_tests


all:	$(NAME)

$(NAME):	$(OBJ)
	@$(CC) -o $(NAME) $(OBJ) -lncurses
	@make clean
	@echo "Everything is compiled"

tests_run:
	@$(CC) -o $(NAME_TEST) $(SRC_TESTS) $(TESTS_FILES) $(CFLAGS) $(TFLAGS)
	@echo Units Tests are compiled
	./$(NAME_TEST)

coverage:
	@gcovr --gcov-executable "llvm-cov gcov" -e tests/

clean:
	@rm -f $(OBJ)
	@rm -f *.gcno *.gcda

fclean:	clean
	@rm -f $(NAME)
	@rm -f $(NAME_TEST)
	@echo "Everything is cleaned"

re:	clean all
