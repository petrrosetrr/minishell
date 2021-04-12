//
// Created by Daisey Patrica on 4/12/21.
//

#include "../includes/minishell.h"

int parser(t_param *param)
{
	if (pre_parser(param))
		return (1);
	return (0);
}
