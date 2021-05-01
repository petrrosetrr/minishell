//
// Created by neo on 30.04.2021.
//

#include "../includes/minishell.h"

int pars_env(t_param *param, char **str, int *i)
{
	char *env;
	char *tmp;
	char *env_content;

	tmp = NULL;
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
	return (0);
}
