NAME	=	libft.a

SRC		=	ft_isalpha.c	ft_isdigit.c	ft_isalnum.c\
			ft_atoi.c		ft_bzero.c		ft_calloc.c\
			ft_isascii.c	ft_isprint.c	ft_memchr.c\
			ft_memcmp.c		ft_memmove.c	ft_memset.c\
			ft_strchr.c		ft_strdup.c		ft_strlcat.c\
			ft_strlcpy.c	ft_strlen.c		ft_strncmp.c\
			ft_strnstr.c	ft_strrchr.c	ft_tolower.c\
			ft_toupper.c	ft_memcpy.c		ft_strtrim.c\
			ft_strjoin.c	ft_substr.c		ft_split.c\
			ft_itoa.c		ft_strmapi.c	ft_striteri.c\
			ft_putchar_fd.c	ft_putstr_fd.c	ft_putendl_fd.c\
			ft_putnbr_fd.c	ft_freearr.c	ft_strcmp.c

SRC_B	=	ft_lstadd_back.c	ft_lstadd_front.c	ft_lstclear.c\
            ft_lstdelone.c	ft_lstlast.c		ft_lstnew.c\
            ft_lstsize.c		ft_lstiter.c		ft_lstmap.c

HEADER	= 	libft.h
OBJ		=	${SRC:%.c=%.o}
OBJ_B	=	${SRC_B:%.c=%.o}

CC		=	clang	
CFLAGS	=	-Wall -Wextra -Werror -I${HEADER}

.PHONY	:	all clean fclean re bonus

all		:	${NAME}

${NAME}	:	${OBJ} ${HEADER}
	ar rcs ${NAME} $?

%.o : %.c ${HEADER}
	${CC} ${CFLAGS} -c $< -o $@

bonus	:
	make OBJ="${OBJ_B}" all

clean	:
	rm -f ${OBJ} ${OBJ_B}

fclean	:	clean
	rm -f ${NAME}

re		:	fclean all

