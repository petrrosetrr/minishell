/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 06:21:11 by jalease           #+#    #+#             */
/*   Updated: 2021/04/14 06:21:14 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_keyval	*handler_init(char **env)
{
	t_keyval	*env_list;
	char		**args;

	env_list = env_to_list(env);
	args = malloc(sizeof (char*) * 2);
	args[0] = ft_strdup("OLDPWD");
	args[1] = NULL;
	unset_builtin(&env_list, args);
	free_2d(args);
	env_inc_sh(&env_list);
	return env_list;
}

void		exec_builtin(t_pars_list *command, t_keyval **env, int *fds)
{
	int fd_1;

	fd_1 = dup(1);
	if (fds != NULL)
		dup2(fds[1], 1);
	if (ft_strcmp(command->args[0], "echo") == 0)
		echo_builtin(&command->args[1]);
	else if (ft_strcmp(command->args[0], "cd") == 0)
		cd_builtin(env, &command->args[1]);
	else if (ft_strcmp(command->args[0], "pwd") == 0)
		pwd_builtin();
	else if (ft_strcmp(command->args[0], "exit") == 0)
		exit_builtin(&command->args[1]);
	else if (ft_strcmp(command->args[0], "export") == 0)
		export_builtin(env, &command->args[1]);
	else if (ft_strcmp(command->args[0], "unset") == 0)
		unset_builtin(env, &command->args[1]);
	else if (ft_strcmp(command->args[0], "env") == 0)
		env_builtin(*env);
	if (fds != NULL)
		dup2(fd_1, 1);
}

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
	while(command_list != NULL)
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
		errno = ret;
		ret = 0;
		i++;
	}

	while (command_list->next_pipe)
	{
		if(command_list->fds_pipe[0] > 0)
			close(command_list->fds_pipe[0]);
		if(command_list->fd_in > 0)
			close(command_list->fd_in);
		free(command_list->fds_pipe);
		command_list->fds_pipe = NULL;
		command_list = command_list->next_pipe;
	}
}

void		handler_exec(t_pars_list *command_list,  t_keyval **env)
{
	if (is_builtin(command_list->args[0]))
		exec_builtin(command_list, env, command_list->fds_pipe);
	else
		exec(command_list, *env, command_list->fds_pipe);
}

int			redir_errors(int ecode, char *path)
{
	if (ecode > 0)
	{
		errno = ecode;
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
	int fd;
	t_rdr *redir;

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
			return redir_errors(errno, redir->f_name);
		redir = redir->next;
	}
	return (1);
}

int			redir_out(t_pars_list *command_list)
{
	int fd;
	int flags;
	DIR *tmp;
	t_rdr *redir;

	redir = command_list->rdr_out;
	while (redir != NULL)
	{
		flags = O_WRONLY | O_CREAT;
		if (redir->type == R_APPEND)
			flags |= O_APPEND;
		else
			flags |= O_TRUNC;
		if ((tmp = opendir(redir->f_name)) == NULL)
		{
			if ((fd = open(redir->f_name, flags)) > 0)
			{
				if (redir->next == NULL)
				{
					if (command_list->fds_pipe != NULL)
						close(command_list->fds_pipe[1]);
					else
					{
						command_list->fds_pipe = malloc(sizeof (int) * 2);
						command_list->fds_pipe[0] = -1;
					}
					command_list->fds_pipe[1] = fd;
				}
				else
					close(fd);
			}
			else
				return redir_errors(errno, redir->f_name);
		}
		else
		{
			closedir(tmp);
			return redir_errors(EISDIR, redir->f_name);
		}
		redir = redir->next;
	}
	return (1);
}

void		handler(t_pars_list *command_list, t_keyval **env)
{
	int fd_0;
	t_pars_list *list;

	if (command_list != NULL)
	{
		fd_0 = dup(0);
		list = command_list;
		while (list != NULL)
		{
			if (list->next_pipe != NULL)
			{
				list->fds_pipe = malloc(sizeof (int) * 2);
				pipe(list->fds_pipe);
			}
			if (!redir_in(list) || !redir_out(list))
			{
				list = list->next_pipe;
				continue ;
			}
			handler_exec(list, env);

			if (list->next_pipe != NULL)
			{
				close(list->fds_pipe[1]);
				dup2(list->fds_pipe[0], IN);
			}
			if(command_list->next_pipe == NULL)
			{
				dup2(fd_0, 0);
			}
			list = list->next_pipe;
		}
		wait_n_close(command_list);
	}
}
