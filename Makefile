# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/10 02:02:56 by ocviller          #+#    #+#              #
#    Updated: 2025/08/10 02:05:39 by ocviller         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/01 00:00:00 by ocviller          #+#    #+#              #
#    Updated: 2025/01/01 00:00:00 by ocviller         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program names
SERVER		= server
CLIENT		= client

# Source files
SERVER_SRC	= server.c
CLIENT_SRC	= client.c

# Object files
SERVER_OBJ	= $(SERVER_SRC:.c=.o)
CLIENT_OBJ	= $(CLIENT_SRC:.c=.o)

# Libft
LIBFT_DIR	= includes/libft
LIBFT		= $(LIBFT_DIR)/libft.a

# Headers
INCLUDES	= -I. -I$(LIBFT_DIR)

# Compiler and flags
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f

# Colors for pretty output
RED			= \033[0;31m
GREEN		= \033[0;32m
YELLOW		= \033[0;33m
BLUE		= \033[0;34m
MAGENTA		= \033[0;35m
CYAN		= \033[0;36m
WHITE		= \033[0;37m
RESET		= \033[0m

# Rules
all: $(LIBFT) $(SERVER) $(CLIENT)

$(LIBFT):
	@echo "$(YELLOW)Compiling libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR)
	@echo "$(GREEN)Libft compiled successfully!$(RESET)"

$(SERVER): $(SERVER_OBJ) $(LIBFT)
	@echo "$(BLUE)Linking $(SERVER)...$(RESET)"
	@$(CC) $(CFLAGS) $(SERVER_OBJ) $(LIBFT) -o $(SERVER)
	@echo "$(GREEN)$(SERVER) compiled successfully!$(RESET)"

$(CLIENT): $(CLIENT_OBJ) $(LIBFT)
	@echo "$(BLUE)Linking $(CLIENT)...$(RESET)"
	@$(CC) $(CFLAGS) $(CLIENT_OBJ) $(LIBFT) -o $(CLIENT)
	@echo "$(GREEN)$(CLIENT) compiled successfully!$(RESET)"

%.o: %.c
	@echo "$(CYAN)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(YELLOW)Cleaning object files...$(RESET)"
	@$(RM) $(SERVER_OBJ) $(CLIENT_OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "$(GREEN)Object files cleaned!$(RESET)"

fclean: clean
	@echo "$(RED)Full clean...$(RESET)"
	@$(RM) $(SERVER) $(CLIENT)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "$(GREEN)Full clean completed!$(RESET)"

re: fclean all

.PHONY: all clean fclean re