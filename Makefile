# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jalease <jalease@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/22 19:04:38 by jalease           #+#    #+#              #
#    Updated: 2020/11/22 19:16:01 by jalease          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

<<<<<<< HEAD
NAME    =   minishell
=======
SRCS	=	./main.c\
			./termcap/termcap.c\
			./termcap/key_function.c\
			./termcap/dop_func.c\
			./parser/parser.c\
			./parser/pre_parser.c\
			./other_fun.c\
			./parser/list_fun.c\
			./parser/join_malloc.c\
			./parser/pars_spec.c

LIBSRCS	=	./libft/ft_strlen.c\
			./libft/ft_memset.c\
			./libft/ft_bzero.c\
			./libft/ft_memcpy.c\
			./libft/ft_memccpy.c\
			./libft/ft_memmove.c\
			./libft/ft_memchr.c\
			./libft/ft_memcmp.c\
			./libft/ft_strlcpy.c\
			./libft/ft_strlcat.c\
			./libft/ft_strchr.c\
			./libft/ft_strrchr.c\
			./libft/ft_strnstr.c\
			./libft/ft_strncmp.c\
			./libft/ft_isalpha.c\
			./libft/ft_isdigit.c\
			./libft/ft_isalnum.c\
			./libft/ft_isascii.c\
			./libft/ft_isprint.c\
			./libft/ft_toupper.c\
			./libft/ft_tolower.c\
			./libft/ft_atoi.c\
			./libft/ft_calloc.c\
			./libft/ft_strdup.c\
			./libft/ft_substr.c\
			./libft/ft_strjoin.c\
			./libft/ft_strtrim.c\
			./libft/ft_split.c\
			./libft/ft_putchar_fd.c\
			./libft/ft_putstr_fd.c\
			./libft/ft_putendl_fd.c\
			./libft/ft_putnbr_fd.c\
			./libft/ft_strmapi.c\
			./libft/ft_itoa.c\
			./libft/ft_digitlen.c\
			./libft/ft_mpldig.c\
			./libft/ft_putnbr.c\
			./libft/ft_ungitlen.c\
			./libft/ft_putstr.c\
			./libft/ft_dig16len.c\
			./libft/ft_digplen.c\
			./libft/get_next_line.c\
			./libft/ft_rhr.c\
			./libft/ft_mstr.c\
			./libft/ft_putchar.c\
			./libft/drop_space.c\
			./libft/overfree.c

HEAD	=	./includes/minishell.h
NAME	= 	minishell
LIBA	=	./libft/libft.a
LIBH	=	./libft/libft.h
OBJS	=	$(SRCS:.c=.o)
LIBOBJS	=	$(LIBSRCS:.c=.o)

GCC		= 	gcc
FLAG	=	-Wall -Wextra -Werror
RM		=	rm -f
C		=	-c
O		=	-o
AR		=	ar rc
MAKE_L	=	$(MAKE) -C ./libft
MAKE_FC	=	$(MAKE) fclean -C ./libft
>>>>>>> dpatrica

SRCS 	:= $(shell find . -name '*.c')

HEAD	:=	$(shell find . -name '*.h')

LIBFT	=	./libft/libft.a

OBJS    =   $(SRCS:.c=.o)

GCC     =   gcc -Wall -Wextra -g -fsanitize=address #-Werror

RM      =   rm -f

all:		$(NAME)

$(NAME):    $(OBJS)
			make -C ./libft
			$(GCC) $(OBJS) ./libft/libft.a -o $(NAME)

clean:
			$(RM) $(OBJS)
			make clean -C ./libft

$(OBJS):	$(HEAD)

fclean:		clean
			$(RM) $(NAME)
			make fclean -C ./libft

re:         fclean all

.PHONY:		all clean fclean re

.c.o:
			$(GCC) -c $< -o $(<:.c=.o)

