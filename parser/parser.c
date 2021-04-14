//
// Created by Daisey Patrica on 4/12/21.
//

#include "../includes/minishell.h"

int parser(t_param *param)
{
	int i;
	int start;
	int flag;

	if (pre_parser(param))
		return (1);
/*	param->com -= (i = drop_space(&param->com));
	start = i;
	flag = 0;
	while (param->com[i])
	{
		if (param->com[i] != ' ')
			flag = 1;
		else if (param->com[i] == (char)39) // хард кавычка '
			;
		else if (param->com[i] == '"')
			;
		else if (param->com[i] == '\\')
			;
		else if (param->com[i] == '$')
			;
		else if (param->com[i] == '|')
			;
		else if (param->com[i] == '>')
			;
		else if (param->com[i] == '<')
			;
		else if (param->com[i] == ' ' && flag)
		{
			pars(start, i);
			while (param->com[i] == ' ')
				i++;
			start = i;
			continue ;
			//парсим аргумент и дропаем лишние пробелы;
		}
		i++;
	}*/
	//парсим одинарный или последний аргумент, если flag == 1;
	return (0);
}
