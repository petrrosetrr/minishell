/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 20:51:33 by jalease           #+#    #+#             */
/*   Updated: 2021/04/08 20:51:36 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void echo_builtin(char **args)
{
	int i;
	int n_flag;

	n_flag = 1;
	i = 0;
	if (ft_strcmp(args[0], "-n") == 0)
	{
		n_flag = 0;
		i = 1;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], OUT);
		if (args[i + 1])
			ft_putstr_fd(" ", OUT);
		i++;
	}
	if (n_flag)
		ft_putstr_fd("\n", OUT);
	errno = 0;
}
