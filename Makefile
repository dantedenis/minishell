# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/20 12:42:26 by bstrong           #+#    #+#              #
#    Updated: 2022/02/15 09:29:13 by bstrong          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
CC		= clang
FLAGS	= -Wall -Wextra -Werror
HEADERS	= ./include/minishell.h

SRC_BUILTIN	=	./builtin/
SRC_PARSER	=	./parser/
SRC_UTILS	=	./utils/
SRC_PIPE	=	./pipe/

SRC_LST_BIN		=	builtin_cd.c		builtin_echo.c		builtin_env.c\
					builtin_exit.c		builtin_export.c	builtin_pwd.c\
					builtin_unset.c

SRC_LST_PARS	=	handle_signs.c		parser.c			preparser.c\
					redirect.c

SRC_LST_PIPE	=	execute_cmd.c		parser_pipe.c

SRC_LST_UTILS	=	utils.c				global_env.c		signal_well.c

SRC_PATH		=	$(SRC_BUILTIN)
#$(addprefix $(SRC_BUILTIN), $(SRC_LST_BIN))
#$(addprefix $(SRC_PARSER), $(SRC_LST_PARS))\
#$(addprefix $(SRC_PIPE), $(SRC_LST_PIPE))\
#$(addprefix $(SRC_UTILS), $(SRC_LST_UTILS))

OBJ_PATH		=	./bin/

OBJ				=	$(addprefix $(OBJ_PATH), $(patsubst %.c, %.o, $(SRC_LST_BIN)))
#$(addprefix $(OBJ_PATH), $(patsubst %.c, %.o, $(SRC_LST_PARS)))\
$(addprefix $(OBJ_PATH), $(patsubst %.c, %.o, $(SRC_LST_PIPE)))\
$(addprefix $(OBJ_PATH), $(patsubst %.c, %.o, $(SRC_LST_UTILS)))

LIBS			=	-L./libft -lft -L/opt/homebrew/opt/readline/lib -lreadline

.PHONY	:	all clean fclean re

all	:	$(LIBS) $(OBJ_PATH) $(NAME)

$(LIBS)	:
		@make -C ./libft

$(OBJ_PATH)	:
		echo $(SRC_PATH)
		mkdir -p $(OBJ_PATH)

$(NAME) : $(OBJ)
		$(CC) $(OBJ) $(LIBS) -o $@

$(OBJ_PATH)%.o : ./builtin/%.c $(HEADERS)
		$(CC) $(FLAGS) -I ./inlcude -I ./libft -I /opt/homebrew/opt/readline/include -c $< -o $@

clean :
	make -C ./libft clean
	rm -rf $(OBJ_PATH)

fclean : clean
	make -C ./libft fclean
	rm -f $(NAME)

re :fclean all