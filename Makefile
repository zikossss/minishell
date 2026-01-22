CC = cc

CFLAGS  = -Wall -Wextra -Werror // -Wall -Wextra -Werror -I/usr/local/opt/readline/include  for MacOs 

LDFLAGS = -lreadline // -L/usr/local/opt/readline/lib -lreadline for MacOs 

SRC = built_ins/cd/cd.c built_ins/cd/cd_utils.c \
	built_ins/echo/echo.c built_ins/echo/echo_utils.c \
	built_ins/env/env.c built_ins/env/env_utils.c \
	built_ins/export/export.c built_ins/export/export_utils1.c built_ins/export/export_utils2.c built_ins/export/export_utils3.c \
	built_ins/exit.c built_ins/pwd.c built_ins/unset.c \
	command_execution/command_execution.c command_execution/command_exec_utils.c command_execution/command_exec_utils1.c \
	execution/execution.c execution/execution_utils.c \
	expantion/variablexpantion.c expantion/expantion_utils1.c expantion/expantion_utils2.c expantion/expantion_utils3.c \
	helper_functions/helper_function.c helper_functions/helper_function1.c helper_functions/helper_function2.c helper_functions/helper_function3.c helper_functions/helper_function4.c helper_functions/helper_function5.c helper_functions/helper_function6.c \
	heredoc/heredoc.c heredoc/heredoc_utils1.c heredoc/heredoc_utils2.c \
	main/minishell.c main/begin_work.c main/main_utils1.c main/main_utils2.c \
	parce_and_redirection/parcing.c parce_and_redirection/redirections.c parce_and_redirection/signals.c \
	tokenization/split_tokens.c tokenization/utils_tokens1.c tokenization/utils_tokens2.c \

OBJ = $(SRC:.c=.o)

HEADER = minishell.h

NAME = minishell

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(LDFLAGS) $(OBJ)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
