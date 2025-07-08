BRED = \033[1;31m
BGREEN = \033[1;32m
BYELLOW=\033[1;33m
BBLUE = \033[1;34m
BPURPLE = \033[1;35m
RESET_COLOR = \033[0m

NAME = minishell

CC = cc
FLAGS = -Wall -Wextra -Werror -g

SRC_DIR = src
SRC =	main.c \
		env/env_copy.c \
		env/env_list.c \
		input_validation/initial_validation.c \
		input_validation/validation_utils.c \
		lexer/lexer.c \
		lexer/utils.c \
		parser/cmd_utils.c \
		parser/expand.c \
		parser/expand_utils.c \
		parser/parser.c \
		parser/redirection_utils.c \
		parser/utils.c \
		executor/builtins/builtin_cd.c \
		executor/builtins/builtin_echo.c \
		executor/builtins/builtin_exit.c \
		executor/builtins/builtin_export.c \
		executor/builtins/builtin_unset.c \
		executor/builtins/builtin.c \
		executor/exec_error_check.c \
		executor/exec_utils.c \
		executor/execute_command.c \
		executor/executor.c \
		executor/heredoc.c \
		executor/redirection.c \
		utils/signals.c \
		utils/clear_and_exit.c \
		utils/info.c \
		utils/memory.c \
		tester.c \


OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

HEADERS = includes/minishell.h includes/env.h includes/executor.h \
			includes/lexer.h includes/memory.h includes/parser.h \
			includes/validation.h
HEADER_DIR = -I./includes -I$(LIBFT_DIR)

LIBS = -lreadline -L./libft -lft
LIBFT = libft/libft.a
LIBFT_DIR = ./libft
LIBFT_GIT = git@github.com:hyun-1324/libft.git

.SECONDARY: $(OBJ)

all: $(NAME)

$(LIBFT):
	@if [ ! -d "$(LIBFT_DIR)" ]; then git clone $(LIBFT_GIT) $(LIBFT_DIR); fi
	@make --no-print-directory -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS) $(HEADER_DIR) -c $< -o $@
	@echo "$(BYELLOW) Compiled $< $(RESET_COLOR)"

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(LIBS) -o $(NAME)
	@echo "$(BGREEN) Linked $(RESET_COLOR)"

clean:
	if [ -d "$(OBJ_DIR)" ]; then rm -rf $(OBJ_DIR); fi
	@if [ -d "$(LIBFT_DIR)" ]; then make clean -C $(LIBFT_DIR); fi
	@echo "$(BBLUE) Cleaned .o files $(RESET_COLOR)"

fclean: clean
	@if [ -d "$(LIBFT_DIR)" ]; then make fclean -C $(LIBFT_DIR); fi
	rm -rf $(LIBFT_DIR) $(NAME)
	@echo "$(BPURPLE) Cleaned all $(RESET_COLOR)"

re: fclean all

.PHONY: all clean fclean re
