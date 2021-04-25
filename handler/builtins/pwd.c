/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 22:13:57 by jalease           #+#    #+#             */
/*   Updated: 2021/04/08 22:13:59 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	pwd_builtin(void)
{
	char buf[PATH_MAX + 1];

	getcwd(buf, PATH_MAX + 1);
	ft_putstr_fd(buf, OUT);
	ft_putstr_fd("\n", OUT);
	errno = 0;
}
