/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpatrica <dpatrica@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 07:11:03 by dpatrica          #+#    #+#             */
/*   Updated: 2021/05/04 07:11:05 by dpatrica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	pars_str(t_param *param, t_pars_list *pars_list, int *i, int *arg)
{
	while (param->com[*i] && !ft_rhr(";'\"\\$|<> ", param->com[*i]))
	{
		join_symbol(&(pars_list->args[*arg]), param->com[*i]);
		(*i)++;
	}
	return (0);
}

static int	parser_3(t_param *param, t_pars_list **pars_list, int *i, int *arg)
{
	if (param->com[*i] == ';')
		pars_end_com(param, &(*pars_list), i, arg);
	else if (param->com[*i] == '\'')
		pars_quo_one(param, &((*pars_list)->args[*arg]), i);
	else if (param->com[*i] == '"')
		pars_quo_two(param, &((*pars_list)->args[*arg]), i);
	else if (param->com[*i] == '\\')
		pars_backslash(param, &((*pars_list)->args[*arg]), i);
	else if (param->com[*i] == '$')
		pars_env(param, &((*pars_list)->args[*arg]), i);
	else if (param->com[*i] == '|')
		*pars_list = pars_pipe(param, *pars_list, i, arg);
	else if (param->com[*i] == '>' || param->com[*i] == '<')
		pars_rdr(param, &(*pars_list)->rdr_out, &(*pars_list)->rdr_in, i);
	else if (param->com[*i] == ' ' && ++(*arg))
		while (param->com[*i] == ' ')
			(*i)++;
	else
		pars_str(param, *pars_list, i, arg);
	return (0);
}

static int	parser_2(t_param *param, t_pars_list *pars_list, int *i, int *arg)
{
	while (param->com[*i])
	{
		if (pars_list->args[*arg] == NULL)
			add_array(&pars_list->args, *arg);
		parser_3(param, &pars_list, i, arg);
	}
	if (pars_list->args[*arg] && !pars_list->args[*arg][0])
	{
		free(pars_list->args[*arg]);
		pars_list->args[*arg] = NULL;
	}
	return (0);
}

int			parser(t_param *param)
{
	int			i;
	int			arg;
	t_pars_list	*pars_list;

	if (pre_parser(param))
		return (1);
	pars_list = init_pars_list();
	param->tmp_list = pars_list;
	add_first_array(pars_list);
	arg = 0;
	i = 0;
	while (param->com[i])
	{
		if (param->com[i] == ' ')
			i++;
		else
			parser_2(param, pars_list, &i, &arg);
	}
	handler(param->tmp_list, &param->env_list);
	free_pars_list(&param->tmp_list);
	return (0);
}
