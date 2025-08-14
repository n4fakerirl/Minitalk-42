# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/14 18:17:42 by ocviller          #+#    #+#              #
#    Updated: 2025/08/14 18:19:55 by ocviller         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_CLIENT	= client
NAME_SERVER	= server
BONUS_CLIENT = bonus_client
BONUS_SERVER = bonus_server

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -g
INCLUDES	= -I includes -I includes/libft -I includes/libft/get_next_line -I includes/libft/ft_printf

LIBFT_DIR	= includes/libft
LIBFT		= $(LIBFT_DIR)/libft.a

SRC_CLIENT	= src/client.c
SRC_SERVER	= src/server.c
SRC_BCLIENT	= bonus/client_bonus.c
SRC_BSERVER	= bonus/server_bonus.c

OBJ_CLIENT	= $(SRC_CLIENT:.c=.o)
OBJ_SERVER	= $(SRC_SERVER:.c=.o)
OBJ_BCLIENT	= $(SRC_BCLIENT:.c=.o)
OBJ_BSERVER	= $(SRC_BSERVER:.c=.o)

# ========================= Rules ========================= #

all: $(LIBFT) $(NAME_CLIENT) $(NAME_SERVER)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME_CLIENT): $(OBJ_CLIENT) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) $(LIBFT) -o $(NAME_CLIENT)

$(NAME_SERVER): $(OBJ_SERVER) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_SERVER) $(LIBFT) -o $(NAME_SERVER)

bonus: $(LIBFT) $(BONUS_CLIENT) $(BONUS_SERVER)

$(BONUS_CLIENT): $(OBJ_BCLIENT) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_BCLIENT) $(LIBFT) -o $(BONUS_CLIENT)

$(BONUS_SERVER): $(OBJ_BSERVER) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_BSERVER) $(LIBFT) -o $(BONUS_SERVER)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ_CLIENT) $(OBJ_SERVER) $(OBJ_BCLIENT) $(OBJ_BSERVER)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME_CLIENT) $(NAME_SERVER) $(BONUS_CLIENT) $(BONUS_SERVER)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus
