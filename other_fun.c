//
// Created by Daisey Patrica on 4/12/21.
//

#include "includes/minishell.h"

void freesher(t_param *param)
{
	int i;

	i = -1;
	if (param->com)
		free(param->com);
	if (param->com_tmp)
		free(param->com_tmp);
	while (param->all_com && param->all_com[++i])
		free(param->all_com[i]);
	if (param->all_com)
		free(param->all_com);
}