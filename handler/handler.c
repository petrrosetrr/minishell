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
	args = malloc(sizeof(char*) * 2);
	args[0] = ft_strdup("OLDPWD");
	args[1] = NULL;
	unset_builtin(&env_list, args);
	free_2d(args);
	env_inc_sh(&env_list);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	g_status = 0;
	return (env_list);
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

void		handler_exec(t_pars_list *command_list, t_keyval **env)
{
	if (is_builtin(command_list->args[0]))
		exec_builtin(command_list, env, command_list->fds_pipe);
	else
		exec(command_list, *env, command_list->fds_pipe);
}

void		handler(t_pars_list *command_list, t_keyval **env)
{
	int			fd_0;
	t_pars_list	*list;

	fd_0 = dup(0);
	list = command_list;
	while (list != NULL)
	{
		if (list->next_pipe != NULL)
		{
			list->fds_pipe = malloc(sizeof(int) * 2);
			pipe(list->fds_pipe);
		}
		if (redir_in(list) && redir_out(list))
			handler_exec(list, env);
		if (list->next_pipe != NULL)
		{
			close(list->fds_pipe[1]);
			dup2(list->fds_pipe[0], IN);
		}
		if (list->next_pipe == NULL)
			dup2(fd_0, 0);
		list = list->next_pipe;
	}
	wait_n_close(command_list);
}
