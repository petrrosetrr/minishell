//
// Created by Daisey Patrica on 4/4/21.
//

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <termcap.h>
#include <term.h>
#include <sys/ioctl.h>
#include <signal.h>

typedef struct	s_param
{
	char	*com;
	char 	*com_tmp;
	char	**all_com;
	int 	cur;
	int		last;
}				t_param;

int			termcap(t_param *param);
int			key_func(char *str, t_param *param, int len, int *i);
char		*delete_last_char(char *com);

#endif
