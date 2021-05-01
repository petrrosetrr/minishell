/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 03:07:54 by jalease           #+#    #+#             */
/*   Updated: 2021/05/01 03:07:56 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			redir_errors(int ecode, char *path)
{
	if (ecode > 0)
	{
		g_status = ecode;
		ft_putstr_fd("minishell: ", ERR);
		ft_putstr_fd(path, ERR);
		ft_putstr_fd(": ", ERR);
		ft_putstr_fd(strerror(ecode), ERR);
		ft_putstr_fd("\n", ERR);
		return (0);
	}
	else
		return (1);
}

int			redir_in(t_pars_list *command_list)
{
	int		fd;
	t_rdr	*redir;

	redir = command_list->rdr_in;
	while (redir != NULL)
	{
		if ((fd = open(redir->f_name, O_RDONLY)) > 0)
		{
			if (redir->next == NULL)
			{
				dup2(fd, 0);
				command_list->fd_in = fd;
			}
			else
				close(fd);
		}
		else
			return (redir_errors(errno, redir->f_name));
		redir = redir->next;
	}
	return (1);
}

void		redir_out_norme(t_pars_list *command_list, t_rdr *redir, int fd)
{
	if (redir->next == NULL)
	{
		if (command_list->fds_pipe != NULL)
			close(command_list->fds_pipe[1]);
		else
		{
			command_list->fds_pipe = malloc(sizeof(int) * 2);
			command_list->fds_pipe[0] = -1;
		}
		command_list->fds_pipe[1] = fd;
	}
	else
		close(fd);
}

int			redir_out(t_pars_list *command_list)
{
	int		fd;
	int		flags;
	DIR		*tmp;
	t_rdr	*redir;

	redir = command_list->rdr_out;
	while (redir != NULL)
	{
		flags = O_WRONLY | O_CREAT;
		if (redir->type == R_APPEND)
			flags |= O_APPEND;
		else
			flags |= O_TRUNC;
		if ((tmp = opendir(redir->f_name)) != NULL)
		{
			closedir(tmp);
			return (redir_errors(EISDIR, redir->f_name));
		}
		if ((fd = open(redir->f_name, flags)) < 0)
			return (redir_errors(errno, redir->f_name));
		redir_out_norme(command_list, redir, fd);
		redir = redir->next;
	}
	return (1);
}
