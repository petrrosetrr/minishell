//
// Created by Daisey Patrica on 4/12/21.
//

#include "../includes/minishell.h"

static int pars_str(t_param *param, t_pars_list *pars_list, int *i, int *arg)
{
	if (pars_list->args == NULL)
		add_first_array(pars_list);
	else if (pars_list->args[*arg] == NULL)
		add_array(&pars_list->args, *arg);
	while (param->com[*i] && !ft_rhr(";'\"\\$|<> ", param->com[*i]))
	{
//		printf("arg:%d\n", *arg);
//		write(1, "1\n", 2);
//		printf("str:%c\n", pars_list->args[*arg][0]);
//		write(1, "2\n", 2);
		join_symbol(&(pars_list->args[*arg]), param->com[*i]);
//		write(1, "4\n", 2);
		(*i)++;
	}
	return (0);
}

static int parser_2(t_param *param, t_pars_list *pars_list, int *i, int *arg)
{
	while (param->com[*i])
	{
		if (param->com[*i] == ';')
			pars_str(param, pars_list, i, arg);
		else if (param->com[*i] == '\'') // хард кавычка '
			pars_str(param, pars_list, i, arg);
		else if (param->com[*i] == '"')
			pars_str(param, pars_list, i, arg);
		else if (param->com[*i] == '\\')
			pars_str(param, pars_list, i, arg);
		else if (param->com[*i] == '$')
			pars_str(param, pars_list, i, arg);
		else if (param->com[*i] == '|')
			pars_str(param, pars_list, i, arg);
		else if (param->com[*i] == '>')
			pars_str(param, pars_list, i, arg);
		else if (param->com[*i] == '<')
			pars_str(param, pars_list, i, arg);
		else if (param->com[*i] == ' ' && ++(*arg))
			while (param->com[*i] == ' ')
				(*i)++;
		else
			pars_str(param, pars_list, i, arg);
	}
	return (0);
}

int parser(t_param *param)
{
	int i;
	int arg;
	t_pars_list *pars_list;
	t_pars_list *temp_pars_list;

	pars_list = init_pars_list();
	temp_pars_list = pars_list;
	if (pre_parser(param))
		return (1);
	arg = 0;
	i = 0;
	while (param->com[i])
	{
		if (param->com[i] == ' ')
			i++;
		else
			parser_2(param, pars_list, &i, &arg);
	}
	i = -1;
	while (pars_list->args[++i])
		printf("%s\n", pars_list->args[i]);
	//парсим одинарный или последний аргумент, если flag == 1;
	return (0);
}
