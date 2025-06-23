RED =		\033[0;31m
GREEN =		\033[0;32m
YELLOW =	\033[0;33m
RESETCOLOR =	\033[0m

NAME =		minishell

CC =		cc
CFLAGS +=	-Wall -Wextra -Werror -g

SRC_DIR =	src/
SRCS =		main.c \
			process.c \
			init.c \
			clear_and_exit.c \
			executor/builtin.c \
			executor/builtin_cd.c \
			executor/builtin_echo.c \
			executor/builtin_unset.c \
			executor/builtin_export.c \
			executor/builtin_exit.c \
			executor/execute_command.c \
			executor/executor.c \

OBJ_DIR =	objs/
OBJS =		$(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

HEADERS =	includes/minishell.h includes/executor.h
HEADERS_PATH = -I./includes -I./libft/includes


LIBS =		-lreadline -lm -L./libft -lft
LIBFT =		libft/libft.a
LIBFT_DIR = ./libft
LIBFT_GIT = git@github.com:hyun-1324/libft.git


.SECONDARY: $(OBJS)

all: $(NAME)

$(LIBFT):
	@if [ ! -d "$(LIBFT_DIR)" ]; then \
		git clone $(LIBFT_GIT) $(LIBFT_DIR); \
	fi
	@make -C $(LIBFT_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS)
	@mkdir -p $(dir $@)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) $(HEADERS_PATH) -c $< -o $@

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(OBJS) $(LIBS) -o $(NAME)
	@echo "$(GREEN)Minishell: Compilation complete!$(RESETCOLOR)"

clean:
	@rm -rf $(OBJ_DIR)
	@if [ -d "$(LIBFT_DIR)" ]; then \
		make -C $(LIBFT_DIR) clean; \
	fi
	@echo "$(YELLOW)Minishell: Clean complete.$(RESETCOLOR)"

fclean: clean
	@if [ -d "$(LIBFT_DIR)" ]; then \
		make -C $(LIBFT_DIR) fclean; \
	fi
	@rm -rf $(OBJ_DIR) $(LIBFT_DIR) $(NAME)
	@echo "$(YELLOW) Minishell: FClean complete.$(RESETCOLOR)"

re: fclean all

.PHONY: all clean fclean re
