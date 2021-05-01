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
	rdr->type = R_REWRITE;
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

void free_pars_list(t_pars_list **pars_list)
{
	t_rdr *tmp;
	t_pars_list *tmp2;
	int i;

	while (*pars_list)
	{
		i = 0;
		if ((*pars_list)->args)
		{
			while ((*pars_list)->args[i])
				free((*pars_list)->args[i++]);
			free((*pars_list)->args);
			(*pars_list)->args = NULL;
		}
		while ((*pars_list)->rdr_out)
		{
			if ((*pars_list)->rdr_out->f_name)
				free((*pars_list)->rdr_out->f_name);
			(*pars_list)->rdr_out->f_name = NULL;
			tmp = (*pars_list)->rdr_out;
			(*pars_list)->rdr_out = (*pars_list)->rdr_out->next;
			free(tmp);
		}
		while ((*pars_list)->rdr_in)
		{
			if ((*pars_list)->rdr_in->f_name)
				free((*pars_list)->rdr_in->f_name);
			(*pars_list)->rdr_in->f_name = NULL;
			tmp = (*pars_list)->rdr_in;
			(*pars_list)->rdr_in = (*pars_list)->rdr_in->next;
			free(tmp);
		}
		tmp2 = *pars_list;
		*pars_list = (*pars_list)->next_pipe;
		free(tmp2);
	}
}
