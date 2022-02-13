LIB_DIR				=	libft/
LIB					=	libft.a
LIBFT				=	${addprefix ${LIB_DIR}, ${LIB}}
NAME        		=   minishell
PARSER_FILES   		=   parser.c			handle_signs.c	preparser.c
PIPE_FILES   		=   execute_cmd.c		parser.c
UTILS_FILES			=	utils.c				
# SRC_FILES_BONUS		=	pipex_bonus.c		parser_bonus.c	run_child_bonus.c\
# 						pipex_utils.c
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
SRC					=	main.c				${PARSER_SRC}	${UTILS_SRC}\
						${PIPE_SRC}
OBJ					=	${SRC:%.c=%.o}
# OBJ_BONUS			=	${SRC_BONUS:%.c=%.o}
.PHONY	:   all re clean fclean bonus libft

all :   ${NAME}

${LIBFT}	:	${SRC_LIBFT} ${INC_LIBFT}
	cd ${LIB_DIR} && ${MAKE} && ${MAKE} bonus

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
