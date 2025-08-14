# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/14 20:39:10 by ocviller          #+#    #+#              #
#    Updated: 2025/08/14 20:51:22 by ocviller         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_SERVER = server
NAME_CLIENT = client
NAME_SERVER_BONUS = server_bonus
NAME_CLIENT_BONUS = client_bonus

CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I./includes -I./includes/libft

SRCDIR = src/
BONUSDIR = bonus/
LIBFTDIR = includes/libft/

SRCS_SERVER = $(SRCDIR)server.c
SRCS_CLIENT = $(SRCDIR)client.c
SRCS_SERVER_BONUS = $(BONUSDIR)server_bonus.c
SRCS_CLIENT_BONUS = $(BONUSDIR)client_bonus.c

OBJS_SERVER = $(SRCS_SERVER:.c=.o)
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)
OBJS_SERVER_BONUS = $(SRCS_SERVER_BONUS:.c=.o)
OBJS_CLIENT_BONUS = $(SRCS_CLIENT_BONUS:.c=.o)

LIBFT = $(LIBFTDIR)libft.a

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m
RESET = \033[0m

# Header function
define HEADER
	@echo ""
	@echo "$(CYAN)████████████████████████████████████████████████████████████████████████████████$(RESET)"
	@echo "$(CYAN)█$(RESET)                                                                              $(CYAN)█$(RESET)"
	@echo "$(CYAN)█$(RESET)    $(YELLOW)███╗   ███╗██╗███╗   ██╗██╗████████╗ █████╗ ██╗     ██╗  ██╗$(RESET)              $(CYAN)█$(RESET)"
	@echo "$(CYAN)█$(RESET)    $(YELLOW)████╗ ████║██║████╗  ██║██║╚══██╔══╝██╔══██╗██║     ██║ ██╔╝$(RESET)              $(CYAN)█$(RESET)"
	@echo "$(CYAN)█$(RESET)    $(YELLOW)██╔████╔██║██║██╔██╗ ██║██║   ██║   ███████║██║     █████╔╝$(RESET)               $(CYAN)█$(RESET)"
	@echo "$(CYAN)█$(RESET)    $(YELLOW)██║╚██╔╝██║██║██║╚██╗██║██║   ██║   ██╔══██║██║     ██╔═██╗$(RESET)               $(CYAN)█$(RESET)"
	@echo "$(CYAN)█$(RESET)    $(YELLOW)██║ ╚═╝ ██║██║██║ ╚████║██║   ██║   ██║  ██║███████╗██║  ██╗$(RESET)              $(CYAN)█$(RESET)"
	@echo "$(CYAN)█$(RESET)    $(YELLOW)╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝   ╚═╝   ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝$(RESET)              $(CYAN)█$(RESET)"
	@echo "$(CYAN)█$(RESET)                                                                              $(CYAN)█$(RESET)"
	@echo "$(CYAN)█$(RESET)                                                                              $(CYAN)█$(RESET)"
	@echo "$(CYAN)█$(RESET)                                                                              $(CYAN)█$(RESET)"
	@echo "$(CYAN)█$(RESET)                          $(GREEN)Par: ocviller$(RESET)                                       $(CYAN)█$(RESET)"
	@echo "$(CYAN)█$(RESET)                          $(GREEN)École: 42$(RESET)                                           $(CYAN)█$(RESET)"
	@echo "$(CYAN)█$(RESET)                                                                              $(CYAN)█$(RESET)"
	@echo "$(CYAN)█$(RESET)                                                                              $(CYAN)█$(RESET)"
	@echo "$(CYAN)████████████████████████████████████████████████████████████████████████████████$(RESET)"
	@echo ""
	@echo "$(YELLOW)🔧 Compilation en cours...$(RESET)"
	@echo ""
endef

all: $(LIBFT) $(NAME_SERVER) $(NAME_CLIENT)

bonus: $(LIBFT) $(NAME_SERVER_BONUS) $(NAME_CLIENT_BONUS)


all: $(LIBFT) $(NAME_SERVER) $(NAME_CLIENT)

bonus: $(LIBFT) $(NAME_SERVER_BONUS) $(NAME_CLIENT_BONUS)

$(LIBFT):
	@$(MAKE) -C $(LIBFTDIR)

$(NAME_SERVER): $(OBJS_SERVER) $(LIBFT)
	$(HEADER)
	@$(CC) $(CFLAGS) $(OBJS_SERVER) $(LIBFT) -o $(NAME_SERVER)
	@echo "$(MAGENTA)✅ Compilation du server...$(RESET)"

$(NAME_CLIENT): $(OBJS_CLIENT) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS_CLIENT) $(LIBFT) -o $(NAME_CLIENT)
	@echo "$(MAGENTA)✅ Compilation du client...$(RESET)"

$(NAME_SERVER_BONUS): $(OBJS_SERVER_BONUS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS_SERVER_BONUS) $(LIBFT) -o $(NAME_SERVER_BONUS)
	@echo "$(GREEN)✅ Compilation du server (Version Bonus)...$(RESET)"

$(NAME_CLIENT_BONUS): $(OBJS_CLIENT_BONUS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS_CLIENT_BONUS) $(LIBFT) -o $(NAME_CLIENT_BONUS)
	@echo "$(GREEN)✅ Compilation du client (Version Bonus)...$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@$(MAKE) -C $(LIBFTDIR) clean
	@rm -f $(OBJS_SERVER) $(OBJS_CLIENT) $(OBJS_SERVER_BONUS) $(OBJS_CLIENT_BONUS)
	@echo "$(YELLOW)⚙️ Nettoyage des objets...$(RESET)"

fclean: clean
	@$(MAKE) -C $(LIBFTDIR) fclean
	@rm -f $(NAME_SERVER) $(NAME_CLIENT) $(NAME_SERVER_BONUS) $(NAME_CLIENT_BONUS)
	@echo "$(YELLOW)⚙️ Nettoyage des objets et programmes...$(RESET)"

re: fclean all

.PHONY: all bonus clean fclean re