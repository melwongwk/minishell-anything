# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: melwong <melwong@student.42kl.edu.my>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/22 13:51:19 by melwong           #+#    #+#              #
#    Updated: 2025/05/23 18:24:04 by melwong          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
SRC_DIR		=	sources
INC_DIR		=	includes
NAME		=	libft.a

# Enable silent mode unless VERBOSE=1
SILENT		=	@
ifeq ($(VERBOSE), 1)
SILENT		=
endif

# Colours
RED			=	\033[0;31m
GREEN		=	\033[0;32m
BLUE		=	\033[0;34m
MAGENTA		=	\033[0;35m
CYAN        =   \033[0;36m
RESET		=	\033[0m

SRCS		=	$(SRC_DIR)/ft_abs.c \
				$(SRC_DIR)/ft_max.c \
				$(SRC_DIR)/ft_min.c \
				$(SRC_DIR)/ft_isalpha.c \
				$(SRC_DIR)/ft_isdigit.c \
				$(SRC_DIR)/ft_isalnum.c \
				$(SRC_DIR)/ft_isascii.c \
				$(SRC_DIR)/ft_isprint.c \
				$(SRC_DIR)/ft_isspace.c \
				$(SRC_DIR)/ft_strlen.c \
				$(SRC_DIR)/ft_memset.c \
				$(SRC_DIR)/ft_bzero.c \
				$(SRC_DIR)/ft_swap.c \
				$(SRC_DIR)/ft_memcpy.c \
				$(SRC_DIR)/ft_memmove.c \
				$(SRC_DIR)/ft_strlcpy.c \
				$(SRC_DIR)/ft_strlcat.c \
				$(SRC_DIR)/ft_toupper.c \
				$(SRC_DIR)/ft_tolower.c \
				$(SRC_DIR)/ft_strchr.c \
				$(SRC_DIR)/ft_strrchr.c \
				$(SRC_DIR)/ft_strcmp.c \
				$(SRC_DIR)/ft_strncmp.c \
				$(SRC_DIR)/ft_memchr.c \
				$(SRC_DIR)/ft_memcmp.c \
				$(SRC_DIR)/ft_strnstr.c \
				$(SRC_DIR)/ft_atoi.c \
				$(SRC_DIR)/ft_atoi_safe.c \
				$(SRC_DIR)/ft_calloc.c \
				$(SRC_DIR)/ft_strdup.c \
				$(SRC_DIR)/ft_strndup.c \
				$(SRC_DIR)/ft_substr.c \
				$(SRC_DIR)/ft_strjoin.c \
				$(SRC_DIR)/ft_strjoin_free.c \
				$(SRC_DIR)/ft_strtrim.c \
				$(SRC_DIR)/ft_count_words.c \
				$(SRC_DIR)/ft_count_words_charset.c \
				$(SRC_DIR)/ft_split.c \
				$(SRC_DIR)/ft_split_charset.c \
				$(SRC_DIR)/ft_split_int.c \
				$(SRC_DIR)/ft_quick_sort.c \
				$(SRC_DIR)/ft_bubblesort_asc.c \
				$(SRC_DIR)/ft_itoa.c \
				$(SRC_DIR)/ft_ultoa_base.c \
				$(SRC_DIR)/ft_strmapi.c \
				$(SRC_DIR)/ft_striteri.c \
				$(SRC_DIR)/ft_putchar_fd.c \
				$(SRC_DIR)/ft_putstr_fd.c \
				$(SRC_DIR)/ft_putendl_fd.c \
				$(SRC_DIR)/ft_putnbr_fd.c \
				$(SRC_DIR)/ft_lstnew.c \
				$(SRC_DIR)/ft_lstadd_front.c \
				$(SRC_DIR)/ft_lstsize.c \
				$(SRC_DIR)/ft_lstlast.c \
				$(SRC_DIR)/ft_lstadd_back.c \
				$(SRC_DIR)/ft_lstdelone.c \
				$(SRC_DIR)/ft_lstclear.c \
				$(SRC_DIR)/ft_lstiter.c \
				$(SRC_DIR)/ft_lstmap.c \
				$(SRC_DIR)/get_next_line.c \
				$(SRC_DIR)/ft_printf.c \
				$(SRC_DIR)/ft_printf_utils.c \
				$(SRC_DIR)/ft_printf_utils2.c \
				$(SRC_DIR)/print_char.c \
				$(SRC_DIR)/print_str.c \
				$(SRC_DIR)/print_ptr.c \
				$(SRC_DIR)/print_int.c \
				$(SRC_DIR)/print_unsigned.c \
				$(SRC_DIR)/print_hex.c \
				$(SRC_DIR)/print_percent.c

OBJS		=	$(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJ_DIR		=	objects

# Rules

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	@echo "$(MAGENTA)[INFO] Archiving $(NAME)...$(RESET)"
	$(SILENT)ar rcs $@ $(OBJS)
	@echo "$(GREEN)[DONE] $(NAME) created.$(RESET)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "$(BLUE)[DONE] $(OBJ_DIR)/ created.$(RESET)"
	@echo "$(CYAN)[CC] Compiling libft object files...$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(SILENT)$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	@echo "$(RED)[CLEAN] Removing libft object files...$(RESET)"
	@echo "$(RED)[CLEAN] Removing libft object directory...$(RESET)"
	$(SILENT)rm -rf $(OBJ_DIR)

fclean:	clean
	@echo "$(RED)[FCLEAN] Removing $(NAME)...$(RESET)"
	$(SILENT)rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
