//
// Created by Daisey Patrica on 4/4/21.
//

#ifndef MINISHELL_H
# define MINISHELL_H
# define EXIT 2
# define CTRL_C 3

# define HARD_RDR 1
# define EZ_RDR 2

#define RDR_OUT 1
#define RDR_IN 2
#define PIPE 3

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
typedef struct	s_rdr
{
	int				type;
	char			*f_name;
	struct s_rdr	*next;
}					t_rdr;
typedef struct	s_pars_list
{
	char				**args;
	t_rdr				*next_rdr_out;
	t_rdr				*next_rdr_in;
	struct s_pars_list	*next_pipe;
}				t_pars_list;

int			termcap(t_param *param);
int			key_func(char *str, t_param *param, int len, int *i);
char		*delete_last_char(char *com);
int			parser(t_param *param);
int			pre_parser(t_param *param);
void 		freesher(t_param *param);
t_pars_list	*init_pars_list(void);
t_rdr		*init_rdr(void);
int			add_first_array(t_pars_list *pars_list);
int			add_array(char ***array, int i);
int			join_symbol(char **str, char symbol);
int			pars_backslash(t_param *param, t_pars_list *pars_list, int *i, int *arg);
int			pars_quo_one(t_param *param, t_pars_list *pars_list, int *i, int *arg);
int			pars_quo_two(t_param *param, t_pars_list *pars_list, int *i, int *arg);

#endif
