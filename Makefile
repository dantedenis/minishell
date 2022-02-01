# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/20 12:42:26 by bstrong           #+#    #+#              #
#    Updated: 2021/10/20 12:42:26 by bstrong          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
CC			= clang
FLAGS		= -Wall -Wextra -Werror

OBJ_PATH	=	./bin/
SRC_PATH	=	./src/
SRC_LST		=	main.c	parser.c

HEADERS	= ./inc/minishell.h

SRC		= $(addprefix $(SRC_PATH), $(SRC_LST))

OBJ		= $(addprefix $(OBJ_PATH), $(patsubst %.c,%.o,$(SRC_LST)))

LIBS	= -L./libft -lft

.PHONY : all clean fclean re

all: $(LIBS) $(OBJ_PATH) $(NAME)

$(LIBS):
	make -C ./libft all

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LIBS) -o $@

$(OBJ_PATH)%.o : $(SRC_PATH)%.c $(HEADERS)
	$(CC) $(FLAGS) -I ./inc -I ./libft -c $< -o $@

clean:
	make -C ./libft clean
	rm -rf $(OBJ_PATH)

fclean: clean
	make -C ./libft fclean 
	rm -f $(NAME)

re: fclean all