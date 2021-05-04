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

NAME    =   minishell

SRCS 	:=	$(shell find . -name '*.c')

HEAD	:=	$(shell find . -name '*.h')

NAME	= 	minishell
LIBA	=	./libft/libft.a
OBJS	=	$(SRCS:.c=.o)

.c.o:
			$(GCC) $(FLAG) -c $< -o $(<:.c=.o)

GCC		= 	gcc -g
FLAG	=	-Wall -Wextra -Werror
RM		=	rm -f
C		=	-c
O		=	-o
AR		=	ar rc
MAKE_L	=	$(MAKE) -C ./libft
MAKE_FC	=	$(MAKE) fclean -C ./libft

all:		$(NAME)

$(NAME):    $(OBJS)
			make -C ./libft
			$(GCC) $(FLAG) $(OBJS) $(LIBA) -o $(NAME) -ltermcap

clean:
			$(RM) $(OBJS)
			make clean -C ./libft

$(OBJS):	$(HEAD)

fclean:		clean
			$(RM) $(NAME)
			make fclean -C ./libft

re:         fclean all

.PHONY:		all clean fclean re
