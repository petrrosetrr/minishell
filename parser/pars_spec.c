/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_spec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpatrica <dpatrica@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 07:10:51 by dpatrica          #+#    #+#             */
/*   Updated: 2021/05/04 07:10:54 by dpatrica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			pars_backslash(t_param *param, char **str, int *i)
{
	(*i)++;
	if (param->com[*i])
	{
		join_symbol(str, param->com[*i]);
		(*i)++;
	}
	return (0);
}

int			pars_quo_one(t_param *param, char **str, int *i)
{
	(*i)++;
	while (param->com[*i] && param->com[*i] != '\'')
	{
		join_symbol(str, param->com[*i]);
		(*i)++;
	}
	if (param->com[*i])
		(*i)++;
	return (0);
}

int			pars_quo_two(t_param *param, char **str, int *i)
{
	(*i)++;
	while (param->com[*i] && param->com[*i] != '"')
	{
		if (param->com[*i] == '$' && param->com[(*i) + 1] &&\
		!ft_rhr("\"'$", param->com[(*i) + 1]))
			pars_env(param, str, i);
		if (param->com[*i] == '\\' &&\
		ft_rhr("\"\\$", param->com[(*i) + 1]))
			(*i)++;
		if (param->com[*i])
		{
			join_symbol(str, param->com[*i]);
			(*i)++;
		}
	}
	if (param->com[*i])
		(*i)++;
	return (0);
}

t_pars_list	*pars_pipe(t_param *param, t_pars_list *pars_list, int *i, int *arg)
{
	if (pars_list->args[*arg] && !pars_list->args[*arg][0])
	{
		free(pars_list->args[*arg]);
		pars_list->args[*arg] = NULL;
	}
	*arg = 0;
	(*i)++;
	if (param->com[*i] == '|')
	{
		while (param->com[*i] && param->com[*i] != ';')
			(*i)++;
		return (pars_list);
	}
	while (param->com[*i] == ' ')
		(*i)++;
	if (param->com[*i] && param->com[*i] != ';')
	{
		pars_list->next_pipe = init_pars_list();
		add_first_array(pars_list->next_pipe);
		return (pars_list->next_pipe);
	}
	return (pars_list);
}

int			pars_end_com(t_param *param, t_pars_list **pars_list,
						int *i, int *arg)
{
	if ((*pars_list)->args[*arg] && !(*pars_list)->args[*arg][0])
	{
		free((*pars_list)->args[*arg]);
		(*pars_list)->args[*arg] = NULL;
	}
	(*i)++;
	while (param->com[*i] == ' ')
		(*i)++;
	if (!param->com[*i])
		return (1);
	*arg = 0;
	handler(param->tmp_list, &param->env_list);
	free_pars_list(&param->tmp_list);
	*pars_list = init_pars_list();
	param->tmp_list = *pars_list;
	add_first_array(*pars_list);
	return (0);
}
