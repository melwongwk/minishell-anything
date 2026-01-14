# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/06 19:01:56 by melwong           #+#    #+#              #
#    Updated: 2026/01/14 14:26:49 by hho-jia-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell
CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
LIBS			=	-lreadline
SRC_DIR			=	sources
INC_DIR			=	includes

# Enable silent mode unless VERBOSE=1
SILENT			=	@
ifeq ($(VERBOSE), 1)
SILENT			=
endif

# Colours
RED				=	\033[0;31m
GREEN			=	\033[0;32m
BLUE			=	\033[0;34m
MAGENTA			=	\033[0;35m
CYAN			=   \033[0;36m
RESET			=	\033[0m

INC				=	$(INC_DIR)/minishell.h
SRCS			=	$(SRC_DIR)/main.c \
					$(SRC_DIR)/prompt.c \
					$(SRC_DIR)/env.c \
					$(SRC_DIR)/signal.c \
					$(SRC_DIR)/validation.c \
					$(SRC_DIR)/heredocs.c \
					$(SRC_DIR)/cleanup.c \
					$(SRC_DIR)/lexer/token_utils.c \
					$(SRC_DIR)/lexer/lexer.c \
					$(SRC_DIR)/lexer/lexer_utils.c \
					$(SRC_DIR)/parser/parser_utils.c \
					$(SRC_DIR)/parser/parser.c \
					$(SRC_DIR)/parser/redirections.c \
					$(SRC_DIR)/parser/expansion.c \
					$(SRC_DIR)/builtins/cd_builtin.c $(SRC_DIR)/builtins/echo_builtin.c $(SRC_DIR)/builtins/env_builtin.c \
					$(SRC_DIR)/builtins/exit_builtin.c $(SRC_DIR)/builtins/export_builtin.c $(SRC_DIR)/builtins/pwd_builtin.c \
					$(SRC_DIR)/builtins/unset_builtin.c \
					$(SRC_DIR)/env/env_set.c $(SRC_DIR)/env/env_utils.c \
					$(SRC_DIR)/executes/execute_utils.c $(SRC_DIR)/executes/execute_cmd.c \
					$(SRC_DIR)/executes/execute.c $(SRC_DIR)/executes/parse_path.c \
					$(SRC_DIR)/redirection/pipe.c $(SRC_DIR)/redirection/file_io.c \
					$(SRC_DIR)/utils/cleanup.c $(SRC_DIR)/utils/error.c $(SRC_DIR)/utils/exit.c

OBJS			=	$(SRCS:$(SRC_DIR)/%.c=$(OBJS_DIR)/%.o)
OBJS_DIR		=	objects

LIBFT_DIR		=	libft
LIBFT_INC		=	$(LIBFT_DIR)/includes
LIBFT			=	$(LIBFT_DIR)/libft.a

# Rules

all:$(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(SILENT)$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(LIBS)
	@echo "$(GREEN)[DONE] $(NAME) created.$(RESET)"

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(SILENT)$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_INC) -c $< -o $@

clean:
	@echo "$(RED)[CLEAN] Removing $(NAME) object files and $(NAME) object directory...$(RESET)"
	@make -C $(LIBFT_DIR) clean
	$(SILENT)rm -rf $(OBJS_DIR)

fclean:	clean
	@echo "$(RED)[FCLEAN] Removing $(NAME)...$(RESET)"
	@make -C $(LIBFT_DIR) fclean
	$(SILENT)rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
