NAME = libft.a
AR = ar -rcs
RM = rm -f
CC = cc
CCFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -MMD -MP -I includes/
PROJECT_NAME = libft

PART1 = ft_isalpha.c \
				ft_isdigit.c \
				ft_isalnum.c \
				ft_isascii.c \
				ft_isprint.c \
				ft_strlen.c \
				ft_memset.c \
				ft_bzero.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_strlcpy.c \
				ft_strlcat.c \
				ft_toupper.c \
				ft_tolower.c \
				ft_strchr.c \
				ft_strrchr.c \
				ft_strncmp.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_strnstr.c \
				ft_atoi.c \
				ft_calloc.c \
				ft_strdup.c \
				ft_atdbl.c \
				ft_strcmp.c \
				ft_strtok.c \
				ft_strndup.c \
				ft_is_whitespace.c

PART2 = ft_substr.c \
				ft_strjoin.c \
				ft_strtrim.c \
				ft_split.c \
				ft_itoa.c \
				ft_strmapi.c \
				ft_striteri.c \
				ft_putchar_fd.c \
				ft_putstr_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \

PRINTF = ft_printf.c \
				ft_char_handler.c \
				ft_str_handler.c \
				ft_nbr_handler.c \
				ft_unbr_handler.c \
				ft_ptr_handler.c \
				ft_hex_handler.c 

BONUS = ft_lstnew_bonus.c \
				ft_lstadd_front_bonus.c \
				ft_lstsize_bonus.c \
				ft_lstlast_bonus.c \
				ft_lstadd_back_bonus.c \
				ft_lstdelone_bonus.c \
				ft_lstclear_bonus.c \
				ft_lstiter_bonus.c \
				ft_lstmap_bonus.c

GNL = get_next_line.c \

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

OBJS_DIR = objs
SRCS_DIR = src

SRC := $(addprefix $(SRCS_DIR)/, $(PART1) $(PART2) $(PRINTF) $(GNL) $(BONUS))

OBJS := $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRC))

DEPS := $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS)
	@echo "$(GREEN)🛠️ Finished compiling $(PROJECT_NAME) objects$(RESET)"
	@echo "$(GREEN)📦 Built library: $(NAME)$(RESET)"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CCFLAGS) $(CPPFLAGS) -c $< -o $@

-include $(DEPS)

clean:
	@$(RM) $(OBJS) $(BONUS_OBJS)
	@rm -rf $(OBJS_DIR)
	@echo "$(RED)🧹 $(PROJECT_NAME) object files removed$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)💥 $(NAME) deleted$(RESET)"

re: fclean all
	@echo "$(GREEN)🔄 $(NAME) rebuild$(RESET)"

.PHONY: all clean fclean re
