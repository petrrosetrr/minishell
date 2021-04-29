/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_fun.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 10:00:24 by jalease           #+#    #+#             */
/*   Updated: 2021/04/29 10:00:26 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	freesher(t_param *param)
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
