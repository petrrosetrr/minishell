# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpatrica <dpatrica@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/05 21:31:17 by dpatrica          #+#    #+#              #
#    Updated: 2020/12/01 17:44:01 by dpatrica         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	./main.c\
			./termcap/termcap.c\
			./termcap/key_function.c\
			./termcap/dop_func.c

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
			./libft/ft_putchar.c

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

all:		$(NAME)

.PHONY:		all clean fclean re

.c.o:
			$(GCC) $(C) $< $(O) $(<:.c=.o)
#FIXME добавь флаги ^ (FLAG) ПЕРЕД СДАЧЕЙ ! ! !

$(NAME):	$(LIBA) $(OBJS)
			$(MK_MLX)
			$(GCC) $(FLAG) $(O) $(NAME) $(LIBOBJS) $(OBJS) -ltermcap

$(LIBA):	$(LIBOBJS)
			$(MAKE_L)

$(OBJS):	$(HEAD)

$(LIBOBJS):	$(LIBH)

clean:
			$(RM) $(OBJS)
			$(MAKE_FC)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all
