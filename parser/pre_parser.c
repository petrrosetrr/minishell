//
// Created by Daisey Patrica on 4/12/21.
//

#include "../includes/minishell.h"

int pre_parser(t_param *param)
{
	int i;
	int valid;

	valid = 0;
	i = drop_space(&param->com);
	param->com -= i;
	if (param->com[i] == ';')
		valid = write(1, "\nMiniHell: syntax error near unexpected token `;'", 49);
	return (valid);
}
