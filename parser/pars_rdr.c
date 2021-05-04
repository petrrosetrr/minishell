/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_rdr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpatrica <dpatrica@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 07:10:34 by dpatrica          #+#    #+#             */
/*   Updated: 2021/05/04 07:10:37 by dpatrica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	put_f_name(t_param *param, t_rdr *rdr, int *i)
{
	if (!rdr->f_name)
		rdr->f_name = ft_calloc(2, sizeof(char));
	if (param->com[*i] == '\'')
		pars_quo_one(param, &rdr->f_name, i);
	else if (param->com[*i] == '"')
		pars_quo_two(param, &rdr->f_name, i);
	else if (param->com[*i] == '\\')
		pars_backslash(param, &rdr->f_name, i);
	else if (param->com[*i] == '$')
		pars_env(param, &rdr->f_name, i);
	else
	{
		join_symbol(&(rdr->f_name), param->com[*i]);
		(*i)++;
	}
}

static int	pars_rdr_f_name(t_param *param, t_rdr *rdr, int *i)
{
	(*i)++;
	while (rdr->next)
		rdr = rdr->next;
	if (rdr->f_name)
	{
		rdr->next = init_rdr();
		rdr = rdr->next;
	}
	rdr->type = R_REWRITE;
	if (param->com[*i] && param->com[*i] == '>' && ++(*i))
		rdr->type = R_APPEND;
	while (param->com[*i] == ' ')
		(*i)++;
	while (param->com[*i] && !ft_rhr(";>|< ", param->com[*i]))
		put_f_name(param, rdr, i);
	while (param->com[*i] && !ft_rhr(";>|<", param->com[*i]))
		(*i)++;
	return (0);
}

int			pars_rdr(t_param *param, t_rdr **rdr_out, t_rdr **rdr_in, int *i)
{
	if (param->com[*i] == '>')
	{
		if (!*rdr_out)
			*rdr_out = init_rdr();
		pars_rdr_f_name(param, *rdr_out, i);
	}
	else if (param->com[*i] == '<')
	{
		if (!*rdr_in)
			*rdr_in = init_rdr();
		pars_rdr_f_name(param, *rdr_in, i);
	}
	if (*rdr_out)
		*rdr_out = free_null_elem(*rdr_out);
	if (*rdr_in)
		*rdr_in = free_null_elem(*rdr_in);
	return (0);
}
