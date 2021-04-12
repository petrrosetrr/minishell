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

SRCS	=	builtins/main.c \
			builtins/cd.c \
			builtins/echo.c \
			builtins/env/env.c \
			builtins/env/export.c \
			builtins/env/unset.c \
			builtins/exit.c \
			builtins/pwd.c \
			utils/utils.c

NAME    =   minishell

HEAD	=	./builtins/builtins.h \
 			./utils/utils.h \

LIBFT	=	./libft/libft.a

OBJS    =   $(SRCS:.c=.o)

GCC     =   gcc -Wall -Wextra -g #-Werror #-fsanitize=address

RM      =   rm -f

C       =   -c

O       =   -o


.PHONY:		all clean fclean re

.c.o:
			$(GCC) $(C) $< $(O) $(<:.c=.o)

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