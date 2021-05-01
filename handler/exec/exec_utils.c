/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 02:32:09 by jalease           #+#    #+#             */
/*   Updated: 2021/04/22 02:32:11 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_errors(int ecode, char *path)
{
	if (ecode > 0)
	{
		g_status = ecode;
		ft_putstr_fd("minishell: ", ERR);
		ft_putstr_fd(path, ERR);
		if (ecode == ENOENT)
			ft_putstr_fd(": No such file or directory\n", ERR);
		else if (ecode == EISDIR)
			ft_putstr_fd(": is a directory\n", ERR);
		else if (ecode == EACCES)
			ft_putstr_fd(": Permission denied\n", ERR);
		else if (ecode == ENOCOMMAND)
			ft_putstr_fd(": command not found\n", ERR);
		else
		{
			ft_putstr_fd(strerror(ecode), ERR);
			ft_putstr_fd("\n", ERR);
		}
	}
}

char	*exec_strjoin(char *s1, char *s2, char *s3)
{
	char *tmp[2];

	if (s1 != NULL && s2 != NULL && s3 != NULL)
	{
		tmp[0] = ft_strjoin(s1, s2);
		tmp[1] = ft_strjoin(tmp[0], s3);
		free(tmp[0]);
		return (tmp[1]);
	}
	else if (s1 != NULL && s2 != NULL)
		return (ft_strjoin(s1, s2));
	return (NULL);
}
