/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 09:59:55 by jalease           #+#    #+#             */
/*   Updated: 2021/04/29 09:59:57 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

static void	init(t_param *param, char **env)
{
	param->all_com = NULL;
	param->com_tmp = NULL;
	param->cur = 0;
	param->last = 0;
	param->tmp_list = NULL;
	param->env_list = handler_init(env);
}

int			main(int argc, char **argv, char **env)
{
	t_param param;

	(void)argc;
	(void)argv;
	param.com = NULL;
	init(&param, env);
	termcap(&param);
	return (0);
}
