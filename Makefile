# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/06 18:36:44 by akoaik            #+#    #+#              #
#    Updated: 2025/10/28 22:45:12 by msafa            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -Iincludes
LDFLAGS		= -lreadline -lncurses

NAME		= minishell

SRCS		= src/Built-ins/cd.c \
			  src/Built-ins/cd_utils.c \
			  src/Built-ins/echo.c \
			  src/Built-ins/echo_utils.c \
			  src/Built-ins/env.c \
			  src/Built-ins/exit.c \
			  src/Built-ins/heredoc.c \
			  src/Built-ins/heredoc_utils.c \
			  src/Built-ins/pwd.c \
			  src/Built-ins/redirections.c \
			  src/Built-ins/unset.c \
			  src/Execution/builtin_exec.c \
			  src/Execution/cmd_fork.c \
			  src/Execution/cmd_validation.c \
			  src/Execution/command_exec.c \
			  src/Execution/exit_code.c \
			  src/Execution/expand.c \
			  src/Execution/expand_helpers2.c \
			  src/Execution/expand_helpers.c \
			  src/Execution/path_utils.c \
			  src/export/add_append_env.c \
			  src/export/export.c \
			  src/export/export_handle.c \
			  src/export/export.utils.c \
			  src/export/sort.c \
			  src/main.c \
			  src/parsing/create.c \
			  src/parsing/parser.c \
			  src/parsing/pipe_exec.c \
			  src/parsing/pipe_exec_utils.c \
			  src/parsing/redirection_parser.c \
			  src/parsing/redirection_parser_utils.c \
			  src/parsing/token_fill.c \
			  src/read_line.c \
			  src/split/count_condition.c \
			  src/split/count_refactored.c \
			  src/split/count_utils.c \
			  src/split/extract_word.c \
			  src/split/extract_word_utils.c \
			  src/split/helpers.c \
			  src/split/split.c \
			  src/split/split_cmd.c \
			  src/utils/cpy_env.c \
			  src/utils/cpy_env_utils.c \
			  src/utils/data_init.c \
			  src/utils/ft_malloc.c \
			  src/utils/init_envp.c \
			  src/utils/my_ft_strtrim.c \
			  src/utils/my_strdup.c \
			  src/utils/my_strjoin.c

OBJS		= $(SRCS:.c=.o)

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

all: $(NAME)

$(LIBFT):
	@make --no-print-directory -C $(LIBFT_DIR) CFLAGS="$(CFLAGS) -I ../includes" > /dev/null 2>&1

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)
	@echo "minishell compiled successfully"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make --no-print-directory -C $(LIBFT_DIR) clean > /dev/null 2>&1
	@rm -f $(OBJS)

fclean: clean
	@make --no-print-directory -C $(LIBFT_DIR) fclean > /dev/null 2>&1
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
