/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpatrica <dpatrica@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 07:10:24 by dpatrica          #+#    #+#             */
/*   Updated: 2021/05/04 07:10:27 by dpatrica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	pars_env_2(t_param *param, char **str, int *i, char *env)
{
	char *tmp;
	char *env_content;

	tmp = NULL;
	env_content = NULL;
	if (param->com[*i] == '?')
	{
		tmp = *str;
		env_content = ft_itoa(g_status);
		*str = ft_strjoin(*str, env_content);
		overfree(&tmp, &env_content, NULL);
		(*i)++;
	}
	else if (env)
	{
		tmp = *str;
		env_content = env_get(param->env_list, env);
		*str = ft_strjoin(*str, env_content);
		overfree(&tmp, &env, &env_content);
	}
}

int			pars_env(t_param *param, char **str, int *i)
{
	char *env;

	env = NULL;
	(*i)++;
	if (param->com[*i] && !ft_rhr(";'\"\\$|<> ?", param->com[*i]))
		env = ft_calloc(2, sizeof(char));
	else if (!param->com[*i] || ft_rhr(";\\|<> ", param->com[*i]))
		join_symbol(str, '$');
	while (param->com[*i] && !ft_rhr(";'\"\\$|<> ?", param->com[*i]))
	{
		join_symbol(&env, param->com[*i]);
		(*i)++;
	}
	pars_env_2(param, str, i, env);
	return (0);
}
