//
// Created by neo on 28.04.2021.
//

#include "../includes/minishell.h"

static int pars_rdr_out(t_param *param, t_pars_list *pars_list, int *i, int *arg)
{
	(*i)++;
	if (!pars_list->rdr_out)
		pars_list->rdr_out = init_rdr();
	else
	{
		while (pars_list->rdr_out->next)
			pars_list->rdr_out = pars_list->rdr_out->next;
		pars_list->rdr_out->next = init_rdr();
		pars_list->rdr_out = pars_list->rdr_out->next;
	}
	if (param->com[*i] && param->com[*i] == '>' && ++(*i))
		pars_list->rdr_out->type = R_APPEND;
	while (param->com[*i] == ' ')
		(*i)++;
	while (param->com[*i] && !ft_rhr(";>|<", param->com[*i]))
	{
		if (!pars_list->rdr_out->f_name)
			pars_list->rdr_out->f_name = ft_calloc(sizeof(char), 2);
		if (param->com[*i] == '\'')
			pars_quo_one(param, &pars_list->rdr_out->f_name, i);
		else if (param->com[*i] == '"')
			pars_quo_two(param, &pars_list->rdr_out->f_name, i);
		else if (param->com[*i] == '\\')
			pars_backslash(param, &pars_list->rdr_out->f_name, i);
		else if (param->com[*i] == '$')
			;
		else
		{
			join_symbol(&(pars_list->rdr_out->f_name), param->com[*i]);
			(*i)++;
		}
	}
	return (0); // FIXME если пустая строка, удалять RDR ?
}

static int pars_rdr_in(t_param *param, t_pars_list *pars_list, int *i, int *arg)
{
	(*i)++;
	if (!pars_list->rdr_in)
		pars_list->rdr_in = init_rdr();
	else
	{
		while (pars_list->rdr_in->next)
			pars_list->rdr_in = pars_list->rdr_in->next;
		pars_list->rdr_in->next = init_rdr();
		pars_list->rdr_in = pars_list->rdr_in->next;
	}
	while (param->com[*i] == ' ')
		(*i)++;
	while (param->com[*i] && !ft_rhr(";>|<", param->com[*i]))
	{
		if (!pars_list->rdr_in->f_name)
			pars_list->rdr_in->f_name = ft_calloc(sizeof(char), 2);
		if (param->com[*i] == '\'')
			pars_quo_one(param, &pars_list->rdr_in->f_name, i);
		else if (param->com[*i] == '"')
			pars_quo_two(param, &pars_list->rdr_in->f_name, i);
		else if (param->com[*i] == '\\')
			pars_backslash(param, &pars_list->rdr_in->f_name, i);
		else if (param->com[*i] == '$')
			;
		else
		{
			join_symbol(&(pars_list->rdr_in->f_name), param->com[*i]);
			(*i)++;
		}
	}
	return (0);
}

int pars_rdr(t_param *param, t_pars_list *pars_list, int *i, int *arg)
{
	while (param->com[*i] && !ft_rhr(";|", param->com[*i]))
	{
		if (param->com[*i] == '>')
			pars_rdr_out(param, pars_list, i, arg);
		else if (param->com[*i] == '<')
			pars_rdr_in(param, pars_list, i, arg);
	}
	return (0);
}
