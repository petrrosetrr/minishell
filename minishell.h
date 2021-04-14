#ifndef MINISHELL_H
#define MINISHELL_H

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

#endif
