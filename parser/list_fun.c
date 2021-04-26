//
// Created by neo on 14.04.2021.
//

#include "../includes/minishell.h"

t_pars_list *init_pars_list(void)
{
	t_pars_list *pars_list;

	pars_list = (t_pars_list*)malloc(sizeof(t_pars_list));
	pars_list->args = NULL;
	pars_list->rdr_out = NULL;
	pars_list->rdr_in = NULL;
	pars_list->next_pipe = NULL;
	pars_list->fds_pipe = NULL;
	pars_list->fd_in = -1;
	return (pars_list);
}

t_rdr *init_rdr(void)
{
	t_rdr  *rdr;

	rdr = (t_rdr*)malloc(sizeof(t_rdr));
	rdr->type = 0;
	rdr->f_name = NULL;
	rdr->next = NULL;
	return (rdr);
}

t_pars_list next_pars_list(t_pars_list *pars_list, int spec)
{
	t_pars_list temp;


//	if (spec == RDR_OUT)
//	else if (spec == RDR_IN)
//	else if (spec == PIPE)
	return (temp);
}
