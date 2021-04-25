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

