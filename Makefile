NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -MMD -MP -I ./includes -I ./libft/includes
MAKEFLAGS += --no-print-directory
LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a
DIR_DUP = mkdir -p $(@D)

GREEN = \033[0;32m
RED = \033[0;31m
BLUE = \033[0;34m
RESET = \033[0m

SRCS_DIR = src
OBJS_DIR = objs
LEXER_DIR := $(SRCS_DIR)/lexer
SIGNAL_DIR := $(SRCS_DIR)/signal
INIT_ENV_DIR := $(SRCS_DIR)/init_env
SIMPLE_EXECVE_DIR := $(SRCS_DIR)/simple_execve
BUILTIN_DIR := $(SRCS_DIR)/builtin
PARSER_DIR := $(SRCS_DIR)/parser

SRCS := 		main.c \
				interactive_mode.c \
				non_interactive_mode.c \

LEXER_SRC := 	lexer_utils.c \
				token_utils.c \
				extract_world.c \
				ft_strtok.c \
				handle_op.c

PARSER_SRC := 	parser_cmd.c \
				parser_pipe.c \
				parser_logical.c 

SIGNAL_SRC := signals.c \

INIT_ENV_SRC := init_env.c \
				init_env_utils.c \
				env_to_envp.c \

SIMPLE_EXECVE_SRC := execve_cmd.c \

BUILTIN_SRC :=	builtin_utils.c \
				builtin_env.c \
				builtin_pwd.c \
				builtin_export.c \
				builtin_unset.c \

SRCS := $(addprefix $(SRCS_DIR)/, $(SRCS))
LEXER_SRC := $(addprefix $(LEXER_DIR)/, $(LEXER_SRC))
PARSER_SRC := $(addprefix $(PARSER_DIR)/, $(PARSER_SRC))
SIGNAL_SRC := $(addprefix $(SIGNAL_DIR)/, $(SIGNAL_SRC))
INIT_ENV_SRC := $(addprefix $(INIT_ENV_DIR)/, $(INIT_ENV_SRC))
SIMPLE_EXECVE_SRC := $(addprefix $(SIMPLE_EXECVE_DIR)/, $(SIMPLE_EXECVE_SRC))
BUILTIN_SRC := $(addprefix $(BUILTIN_DIR)/, $(BUILTIN_SRC))

ALL_SRCS := $(SRCS) $(LEXER_SRC) $(SIGNAL_SRC) $(INIT_ENV_SRC) $(SIMPLE_EXECVE_SRC) $(BUILTIN_SRC) $(PARSER_SRC)
OBJS := $(ALL_SRCS:%.c=$(OBJS_DIR)/%.o)

DEPS := $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJS) $(LIBFT) -lreadline -o $@
	@echo "$(GREEN)🛠️ Finished compiling $(NAME) objects$(RESET)"
	@echo "$(GREEN)🚀 $@ was created$(RESET)"

$(OBJS_DIR)/%.o: %.c
	@$(DIR_DUP)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

-include $(DEPS)

$(LIBFT):
	@make $(MAKEFLAGS) -C $(LIBFT_PATH)

clean:
	@rm -rf $(OBJS_DIR)
	@make $(MAKEFLAGS) -C $(LIBFT_PATH) clean
	@echo "$(RED)🧹 $(NAME) objects removed$(RESET)"

fclean: clean
	@rm -rf $(NAME)
	@make $(MAKEFLAGS) -C $(LIBFT_PATH) fclean
	@echo "$(RED)💥 $(NAME) deleted$(RESET)"

re: fclean all
	@make $(MAKEFLAGS) -C $(LIBFT_PATH) re
	@echo "$(BLUE)🔄 $(NAME) rebuild$(RESET)"

.PHONY: all clean fclean re
