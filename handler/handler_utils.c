/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 03:09:18 by jalease           #+#    #+#             */
/*   Updated: 2021/05/01 03:09:20 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			is_builtin(char *command)
{
	if (ft_strcmp(command, "echo") == 0)
		return (1);
	else if (ft_strcmp(command, "cd") == 0)
		return (1);
	else if (ft_strcmp(command, "pwd") == 0)
		return (1);
	else if (ft_strcmp(command, "exit") == 0)
		return (1);
	else if (ft_strcmp(command, "export") == 0)
		return (1);
	else if (ft_strcmp(command, "unset") == 0)
		return (1);
	else if (ft_strcmp(command, "env") == 0)
		return (1);
	return (0);
}

int			c_list_len(t_pars_list *command_list)
{
	int i;

	i = 0;
	while (command_list != NULL)
	{
		command_list = command_list->next_pipe;
		i++;
	}
	return (i);
}

void		wait_n_close(t_pars_list *command_list)
{
	int i;
	int ret;

	i = 0;
	ret = 0;
	while (i < c_list_len(command_list))
	{
		wait(&ret);
		g_status = ret;
		ret = 0;
		i++;
	}
	while (command_list)
	{
		if (command_list->fds_pipe != NULL)
		{
			if (command_list->fds_pipe[0] > 0)
				close(command_list->fds_pipe[0]);
			free(command_list->fds_pipe);
			command_list->fds_pipe = NULL;
		}
		if (command_list->fd_in > 0)
			close(command_list->fd_in);
		command_list = command_list->next_pipe;
	}
}

void		sig_handler(int signal)
{
	if (signal == 3)
		ft_putstr_fd("Quit: 3", OUT);
	write(1, "\n", 1);
}
