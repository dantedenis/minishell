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

SRC_LST		=	main.c	builtin_cd.c builtin_echo.c builtin_env.c\
				builtin_exit.c	builtin_export.c	builtin_pwd.c\
				builtin_unset.c	global_env.c	signal_well.c

SRC		= $(addprefix $(SRC_PATH), $(SRC_LST))

HEADERS	= ./inc/minishell.h

OBJ		= $(addprefix $(OBJ_PATH), $(patsubst %.c,%.o,$(SRC_LST)))

LIBS	= -L./libft -lft -L/opt/homebrew/opt/readline/lib -lreadline

.PHONY : all clean fclean re

all: $(LIBS) $(OBJ_PATH) $(NAME)

$(LIBS):
	make -C ./libft all

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LIBS) -o $@

$(OBJ_PATH)%.o : $(SRC_PATH)%.c $(HEADERS)
	$(CC) $(FLAGS) -I ./inc -I ./libft -I /opt/homebrew/opt/readline/include -c $< -o $@

clean:
	make -C ./libft clean
	rm -rf $(OBJ_PATH)

fclean: clean
	make -C ./libft fclean 
	rm -f $(NAME)

re: fclean all