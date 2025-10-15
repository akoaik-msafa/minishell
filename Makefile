# **************************************************************************** #
#                                   CONFIG                                     #
# **************************************************************************** #

CC       = cc
CFLAGS   = -g -Wall -Wextra -Werror -Iincludes
LDFLAGS  = -lreadline -lncurses

NAME     = minishell
SRC_DIR  = src
SRCS     = $(shell find $(SRC_DIR) -name "*.c")
OBJS     = $(SRCS:.c=.o)

LIBFT_DIR = libft
LIBFT     = $(LIBFT_DIR)/libft.a

# **************************************************************************** #
#                                   COLORS                                     #
# **************************************************************************** #

RESET    = \033[0m
BOLD     = \033[1m
GREEN    = \033[32m
YELLOW   = \033[33m
CYAN     = \033[36m
MAGENTA  = \033[35m
RED      = \033[31m
BLUE     = \033[34m
GRAY     = \033[90m

# **************************************************************************** #
#                                   RULES                                      #
# **************************************************************************** #

all: silent_header $(LIBFT) $(NAME) silent_footer

# NOTE: ALL LINES BELOW HERE STARTING WITH @ MUST HAVE A TAB BEFORE THEM
# The error "missing separator" happens if you use spaces instead of a TAB.

silent_header:
	@clear
	@echo "$(CYAN)╔══════════════════════════════════════════════════════════════╗$(RESET)"
	@echo "$(CYAN)║                                                              ║$(RESET)"
	@echo "$(CYAN)║$(BOLD)         PROJECT: $(YELLOW)$(NAME)$(RESET)$(CYAN) - SHELL IMPLEMENTATION$(CYAN)            ║$(RESET)"
	@echo "$(CYAN)║$(BOLD)         AUTHORS: $(MAGENTA)akoaik$(RESET)$(CYAN), $(MAGENTA)msafa$(RESET)$(CYAN)                               ║$(RESET)"
	@echo "$(CYAN)║                                                              ║$(RESET)"
	@echo "$(CYAN)╚══════════════════════════════════════════════════════════════╝$(RESET)"
	@echo ""
	@printf "$(BLUE)🚀 Starting build process..."
	@for i in 1 2; do sleep 0.3; printf "."; done; echo "$(RESET)\n"

$(LIBFT):
	@printf "$(YELLOW)📚 Building libft..."
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) CFLAGS="$(CFLAGS) -I ../includes" > /dev/null
	@printf "\t$(GREEN)OK$(RESET)\n"
	@sleep 0.3

$(NAME): $(OBJS) $(LIBFT)
	@printf "$(YELLOW)⚙️  Linking $(BOLD)$(NAME)$(RESET)$(YELLOW) objects..."
	@$(CC) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)
	@printf "\t$(GREEN)OK$(RESET)\n"
	@sleep 0.3
	@echo ""
	@echo "$(GREEN)==================================================================$(RESET)"
	@echo "$(GREEN)  ✅ $(BOLD)BUILD SUCCESSFUL!$(RESET)$(GREEN) $(NAME) is ready to use!$(RESET)"
	@echo "$(GREEN)  ▶️  Run with: $(CYAN)./$(NAME)$(RESET)"
	@echo "$(GREEN)==================================================================$(RESET)"
	@echo ""

%.o: %.c
	@printf "$(GRAY)  [COMPILING] $<$(RESET)\r"
	@$(CC) $(CFLAGS) -c $< -o $@ > /dev/null

clean:
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean > /dev/null
	@rm -f $(OBJS)
	@echo "$(RED)🧹 Object files cleaned.$(RESET)"

fclean: clean
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean > /dev/null
	@rm -f $(NAME)
	@echo "$(RED)💣 Executable '$(NAME)' removed.$(RESET)"

re: fclean all

silent_footer:
	@sleep 0.3
	@echo "$(MAGENTA)✨ Build process completed. Have fun, akoaik & msafa! ✨$(RESET)"
	@echo ""

.PHONY: all clean fclean re silent_header silent_footer