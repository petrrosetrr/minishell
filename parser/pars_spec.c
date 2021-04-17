//
// Created by neo on 14.04.2021.
//

#include "../includes/minishell.h"

int pars_backslash(t_param *param, t_pars_list *pars_list, int *i, int *arg)
{
	if (pars_list->args == NULL)
		add_first_array(pars_list);
	else if (pars_list->args[*arg] == NULL)
		add_array(&pars_list->args, *arg);
	(*i)++;
	if (param->com[*i])
	{
		join_symbol(&(pars_list->args[*arg]), param->com[*i]);
		(*i)++;
	}
	return (0);
}

int pars_quo_one(t_param *param, t_pars_list *pars_list, int *i, int *arg)
{
	if (pars_list->args == NULL)
		add_first_array(pars_list);
	else if (pars_list->args[*arg] == NULL)
		add_array(&pars_list->args, *arg);
	(*i)++;
	while (param->com[*i] && param->com[*i] != '\'')
	{
		join_symbol(&(pars_list->args[*arg]), param->com[*i]);
		(*i)++;
	}
	if (param->com[*i])
		(*i)++;
	return (0);
}

int pars_quo_two(t_param *param, t_pars_list *pars_list, int *i, int *arg)
{
	if (pars_list->args == NULL)
		add_first_array(pars_list);
	else if (pars_list->args[*arg] == NULL)
		add_array(&pars_list->args, *arg);
	(*i)++;
	while (param->com[*i] && param->com[*i] != '"')
	{
		if (param->com[*i] == '\\' && ft_rhr("\"\\$", param->com[(*i) + 1]))
			(*i)++;
		join_symbol(&(pars_list->args[*arg]), param->com[*i]);
		(*i)++;
	}
	if (param->com[*i])
		(*i)++;
	return (0);
}