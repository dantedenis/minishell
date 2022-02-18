# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/20 12:42:26 by bstrong           #+#    #+#              #
#    Updated: 2022/02/17 21:14:27 by bstrong          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIB_DIR				=	libft/
LIB					=	libft.a
LIBFT				=	${addprefix ${LIB_DIR}, ${LIB}}
NAME				=   minishell
OBJ_PATH			=	./bin/
SRC_PATH			=	./builtin/

SRC_LST				=	builtin_cd.c	builtin_echo.c		builtin_env.c\
						builtin_exit.c	builtin_export.c	builtin_pwd.c\
						builtin_unset.c			

 SRC					= $(addprefix $(SRC_PATH), $(SRC_LST))

# HEADERS				= ./inc/minishell.h

# OBJ					= $(addprefix $(OBJ_PATH), $(patsubst %.c,%.o,$(SRC_LST)))

LIBS				= -L./libft -lft -L/opt/homebrew/opt/readline/lib -lreadline
PARSER_FILES   		=   parser.c			handle_signs.c	preparser.c\
						redirect.c
PIPE_FILES   		=   execute_cmd.c		get_cmd.c
UTILS_FILES			=	utils.c				signal_well.c	global_env.c
						#data.c
# SRC_FILES_BONUS		=	pipex_bonus.c		parser_bonus.c	run_child_bonus.c
PARSER_DIR			=	parser/
PIPE_DIR			=	pipe/
UTILS_DIR			=	utils/
INC_FILES			=	minishell.h
# INC_FILES_BONUS		=	pipex_bonus.h
INC_DIR				=	includes/
CC          		=   clang
CFLAGS      		=   -Wall -Wextra -Werror -I${LIB_DIR} -I${INC_DIR}
SRC_LIBFT_FILES		=	ft_isalpha.c		ft_isdigit.c	ft_isalnum.c\
						ft_atoi.c			ft_bzero.c		ft_calloc.c\
						ft_isascii.c		ft_isprint.c	ft_memchr.c\
						ft_memcmp.c			ft_memmove.c	ft_memset.c\
						ft_strchr.c			ft_strdup.c		ft_strlcat.c\
						ft_strlcpy.c		ft_strlen.c		ft_strncmp.c\
						ft_strnstr.c		ft_strrchr.c	ft_tolower.c\
						ft_toupper.c		ft_memcpy.c		ft_strtrim.c\
						ft_strjoin.c		ft_substr.c		ft_split.c\
						ft_itoa.c			ft_strmapi.c	ft_striteri.c\
						ft_putchar_fd.c		ft_putstr_fd.c	ft_putendl_fd.c\
						ft_putnbr_fd.c		ft_freearr.c
INC_LIBFT_FILES		=	libft.h
INC_LIBFT			=	${addprefix ${LIB_DIR}, ${INC_LIBFT_FILES}}
SRC_LIBFT			=	${addprefix ${LIB_DIR}, ${SRC_LIBFT_FILES}}
PARSER_SRC			=	${addprefix ${PARSER_DIR}, ${PARSER_FILES}}
PIPE_SRC			=	${addprefix ${PIPE_DIR}, ${PIPE_FILES}}
UTILS_SRC			=	${addprefix ${UTILS_DIR}, ${UTILS_FILES}}
# SRC_BONUS			=	${addprefix ${SRC_DIR}, ${SRC_FILES_BONUS}}
INC					=	${addprefix ${INC_DIR}, ${INC_FILES}}
# INC_BONUS			=	${addprefix ${INC_DIR}, ${INC_FILES_BONUS}}
SRC					+=	main.c				${PARSER_SRC}	${UTILS_SRC}\
						${PIPE_SRC}
OBJ					=	${SRC:%.c=%.o}
# OBJ_BONUS			=	${SRC_BONUS:%.c=%.o}
.PHONY	:   all re clean fclean bonus libft

all :   ${NAME}

${LIBFT}	:	${SRC_LIBFT} ${INC_LIBFT}
	cd ${LIB_DIR} && ${MAKE} && ${MAKE}

%.o :   %.c ${LIBFT}
	${CC} ${CFLAGS} -c $< -o $@

${NAME} :  ${OBJ} ${INC}
	${CC} -o ${NAME} ${OBJ} ${CFLAGS} -lreadline -L${LIB_DIR} -lft 

bonus	:	${LIBFT}
	@make OBJ="${OBJ_BONUS}" INC=${INC_BONUS} all

clean   :
	rm -rf ${OBJ} ${OBJ_BONUS}

fclean  :   clean
	rm -rf ${NAME}
	@cd ${LIB_DIR} && ${MAKE} fclean

re		:	fclean all


# all: $(LIBS) $(OBJ_PATH) $(NAME)

# $(LIBS):
# 	make -C ./libft all

# $(OBJ_PATH):
# 	mkdir -p $(OBJ_PATH)

# $(NAME): $(OBJ)
# 	$(CC) $(OBJ) $(LIBS) -o $@

# $(OBJ_PATH)%.o : $(SRC_PATH)%.c $(HEADERS)
# 	$(CC) $(FLAGS) -I ./inc -I ./libft -I /opt/homebrew/opt/readline/include -c $< -o $@

# clean:
# 	make -C ./libft clean
# 	rm -rf $(OBJ_PATH)

# fclean: clean
# 	make -C ./libft fclean 
# 	rm -f $(NAME)

# re: fclean all
