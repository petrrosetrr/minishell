//
// Created by Daisey Patrica on 4/12/21.
//

#include "../includes/minishell.h"

static int pars_str(t_param *param, t_pars_list *pars_list, int *i, int *arg)
{
//	if (pars_list->args == NULL)
//		add_first_array(pars_list);
//	if (pars_list->args[*arg] == NULL)
//		add_array(&pars_list->args, *arg);
	while (param->com[*i] && !ft_rhr(";'\"\\$|<> ", param->com[*i]))
	{
		join_symbol(&(pars_list->args[*arg]), param->com[*i]);
		(*i)++;
	}
	return (0);
}

static int parser_2(t_param *param, t_pars_list *pars_list, int *i, int *arg)
{
	while (param->com[*i])
	{
		if (pars_list->args[*arg] == NULL)
			add_array(&pars_list->args, *arg);
		if (param->com[*i] == ';')
			pars_end_com(param, &pars_list, i, arg);
		else if (param->com[*i] == '\'') // хард кавычка '
			pars_quo_one(param, &(pars_list->args[*arg]), i);
		else if (param->com[*i] == '"')
			pars_quo_two(param, &(pars_list->args[*arg]), i);
		else if (param->com[*i] == '\\')
			pars_backslash(param, &(pars_list->args[*arg]), i);
		else if (param->com[*i] == '$')
			pars_str(param, pars_list, i, arg);
		else if (param->com[*i] == '|') // доработать два пайпа подряд || после арг (сега)
			pars_list = pars_pipe(param, pars_list, i, arg);
		else if (param->com[*i] == '>' || param->com[*i] == '<')
			pars_rdr(param, pars_list, i, arg);
		else if (param->com[*i] == ' ' && ++(*arg))
			while (param->com[*i] == ' ')
				(*i)++;
		else
			pars_str(param, pars_list, i, arg);
	}
	if (pars_list->args[*arg] && !pars_list->args[*arg][0])
	{
		free(pars_list->args[*arg]);
		pars_list->args[*arg] = NULL;
	}
	return (0);
}

int parser(t_param *param)
{
	int i;
	int arg;
	t_pars_list *pars_list;

	if (pre_parser(param)) // FIXME добавить обработку строки с пробелами
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
//	while (param->tmp_list)
//	{
//		i = -1;
//		while (param->tmp_list->args[++i])
//			printf("%s\n", param->tmp_list->args[i]);
//		write(1, "_pipe_\n", 7);
//		param->tmp_list = param->tmp_list->next_pipe;
//	}
	handler(param->tmp_list, &param->env_list);
	free_pars_list(&param->tmp_list);
	return (0);
}
