
#include "../includes/minishell.h"

static int	pars_rdr_out(t_param *param, t_rdr *rdr_out, int *i, int *arg)
{
	(*i)++;
	while (rdr_out->next)
		rdr_out = rdr_out->next;
	if (rdr_out->f_name)
	{
		rdr_out->next = init_rdr();
		rdr_out = rdr_out->next;
	}
	if (param->com[*i] && param->com[*i] == '>' && ++(*i))
		rdr_out->type = R_APPEND;
	while (param->com[*i] == ' ')
		(*i)++;
	while (param->com[*i] && !ft_rhr(";>|< ", param->com[*i]))
	{
		if (!rdr_out->f_name)
			rdr_out->f_name = ft_calloc(2, sizeof(char));
		if (param->com[*i] == '\'')
			pars_quo_one(param, &rdr_out->f_name, i);
		else if (param->com[*i] == '"')
			pars_quo_two(param, &rdr_out->f_name, i);
		else if (param->com[*i] == '\\')
			pars_backslash(param, &rdr_out->f_name, i);
		else if (param->com[*i] == '$')
			pars_env(param, &rdr_out->f_name, i);
		else
		{
			join_symbol(&(rdr_out->f_name), param->com[*i]);
			(*i)++;
		}
	}
	while (param->com[*i] && !ft_rhr(";>|<", param->com[*i]))
		(*i)++;
	return (0); // FIXME если пустая строка, удалять RDR ?
}

static int	pars_rdr_in(t_param *param, t_rdr *rdr_in, int *i, int *arg)
{
	(*i)++;
	while (rdr_in->next)
		rdr_in = rdr_in->next;
	if (rdr_in->f_name)
	{
		rdr_in->next = init_rdr();
		rdr_in = rdr_in->next;
	}
	while (param->com[*i] == ' ')
		(*i)++;
	while (param->com[*i] && !ft_rhr(";>|< ", param->com[*i]))
	{
		if (!rdr_in->f_name)
			rdr_in->f_name = ft_calloc(2, sizeof(char));
		if (param->com[*i] == '\'')
			pars_quo_one(param, &rdr_in->f_name, i);
		else if (param->com[*i] == '"')
			pars_quo_two(param, &rdr_in->f_name, i);
		else if (param->com[*i] == '\\')
			pars_backslash(param, &rdr_in->f_name, i);
		else if (param->com[*i] == '$')
			pars_env(param, &rdr_in->f_name, i);
		else
		{
			join_symbol(&(rdr_in->f_name), param->com[*i]);
			(*i)++;
		}
	}
	while (param->com[*i] && !ft_rhr(";>|<", param->com[*i]))
		(*i)++;
	return (0);
}

int			pars_rdr(t_param *param, t_pars_list *pars_list, int *i, int *arg)
{
	while (param->com[*i] && !ft_rhr(";|", param->com[*i]))
	{
		if (param->com[*i] == '>')
		{
			if (!pars_list->rdr_out)
				pars_list->rdr_out = init_rdr();
			pars_rdr_out(param, pars_list->rdr_out, i, arg);
		}
		else if (param->com[*i] == '<')
		{
			if (!pars_list->rdr_in)
				pars_list->rdr_in = init_rdr();
			pars_rdr_in(param, pars_list->rdr_in, i, arg);
		}
	}
	return (0);
}
