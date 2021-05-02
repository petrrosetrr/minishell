
#include "../includes/minishell.h"

t_pars_list		*init_pars_list(void)
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

t_rdr			*init_rdr(void)
{
	t_rdr	*rdr;

	rdr = (t_rdr*)malloc(sizeof(t_rdr));
	rdr->type = R_REWRITE;
	rdr->f_name = NULL;
	rdr->next = NULL;
	return (rdr);
}

t_rdr			*free_null_elem(t_rdr *rdr)
{
	t_rdr *head;
	t_rdr *prev_elem;

	head = rdr;
	prev_elem = NULL;
	while (rdr->next)
	{
		prev_elem = rdr;
		rdr = rdr->next;
	}
	if (prev_elem && !rdr->f_name)
	{
		free(prev_elem->next);
		prev_elem->next = NULL;
	}
	else if (!prev_elem && !rdr->f_name)
	{
		free(head);
		head = NULL;
	}
	return (head);
}

static void		free_rdr(t_rdr *rdr)
{
	t_rdr *temp;

	while (rdr)
	{
		if (rdr->f_name)
			free(rdr->f_name);
		rdr->f_name = NULL;
		temp = rdr;
		rdr = rdr->next;
		free(temp);
	}
}

void			free_pars_list(t_pars_list **pars_list)
{
	t_pars_list	*temp;
	int			i;

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
		if ((*pars_list)->rdr_out)
			free_rdr((*pars_list)->rdr_out);
		if ((*pars_list)->rdr_in)
			free_rdr((*pars_list)->rdr_in);
		temp = *pars_list;
		*pars_list = (*pars_list)->next_pipe;
		free(temp);
	}
}
