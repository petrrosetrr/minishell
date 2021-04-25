/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 17:43:13 by jalease           #+#    #+#             */
/*   Updated: 2021/04/13 17:43:16 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*exec_check_path(char **dir, char *command)
{
	DIR		*dir_s;
	size_t	j;
	t_dir	*item;
	char	*path;

	j = 0;
	path = NULL;
	while (dir[j] != NULL && path == NULL)
	{
		if ((dir_s = opendir(dir[j])) != NULL)
		{
			while ((item = readdir(dir_s)) != NULL)
			{
				if ((ft_strcmp(item->d_name, command)) == 0
				&& (item->d_type != DT_DIR))
				{
					path = exec_strjoin(dir[j], "/", command);
					break ;
				}
			}
			closedir(dir_s);
		}
		j++;
	}
	return (path);
}

char	**exec_split_path(t_keyval *env_head)
{
	t_keyval	*path;
	char		**ret;

	ret = NULL;
	if ((path = env_contains(env_head, "PATH")) != NULL)
	{
		ret = ft_split(path->value, ':');
	}
	return (ret);
}

char	**exec_join_env(t_keyval *env_head)
{
	char	**env_arr;
	size_t	i;

	if (env_head != NULL)
	{
		i = 0;
		env_arr = ft_calloc((env_length(env_head) + 1), sizeof(char *));
		while (env_head != NULL)
		{
			if (env_head->value != NULL)
				env_arr[i] = exec_strjoin(env_head->key, "=", env_head->value);
			i++;
			env_head = env_head->next;
		}
		return (env_arr);
	}
	return (NULL);
}

void	exec_fork(char *path, char **args, char **env, int *fds)
{
	int pid;

	pid = fork();
	if (pid == 0)
	{
		if (fds != NULL)
		{
			dup2(fds[1], 1);
			close(fds[0]);
		}
		execve(path, args, env);
		if (fds != NULL)
			close(fds[1]);
		exec_errors(errno, path);
		exit(errno);
	}
}

void	exec(t_pars_list *command, t_keyval *env, int *fds)
{
	char	**path_arr;
	char	**env_arr;
	char	*path;

	env_arr = exec_join_env(env);
	if (ft_strrchr(command->args[0], '/') == 0)
	{
		if ((path_arr = exec_split_path(env)) != NULL)
		{
			if ((path = exec_check_path(path_arr, command->args[0])) != NULL)
			{
				exec_fork(path, command->args, env_arr, fds);
				free(path);
			}
			else
				exec_errors(ENOENT, command->args[0]);
			free_2d(path_arr);
		}
		else
			exec_errors(ENOENT, command->args[0]);
	}
	else
		exec_fork(command->args[0], command->args, env_arr, fds);
	free_2d(env_arr);
}
