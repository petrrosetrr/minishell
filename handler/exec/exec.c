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

void	exec_errors(int ret_code, char *path)
{
	if (ret_code > 0)
	{
		ft_putstr_fd("minishell: ", ERR);
		ft_putstr_fd(path, ERR);
		//TODO: создать глобальную переменную для ошибок
		if (ret_code == NO_PATH)
			ft_putstr_fd(": No such file or directory\n", ERR);
		else if (ret_code == IS_A_DIR)
			ft_putstr_fd(": is a directory\n", ERR);
		else
			ft_putstr_fd(": command not found\n", ERR);
	}
}

char	*exec_strjoin(char *s1, char *s2, char *s3)
{
	char *tmp[2];

	if (s1 != NULL && s2 !=NULL && s3!= NULL)
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

char	*exec_check_path(char **dir, char *command)
{
	DIR		*dir_s;
	size_t	j;
	s_dir	*item;
	char	*path;

	j = 0;
	path = NULL;
	while(dir[j] != NULL && path == NULL)
	{
		if ((dir_s = opendir(dir[j])) != NULL)
		{
			while((item = readdir(dir_s)) != NULL)
			{
				if ((ft_strcmp(item->d_name, command)) == 0 && (item->d_type != DT_DIR))
				{
					path = exec_strjoin(dir[j], "/", command);
//					puts(item->d_name);
//					puts(path);
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
		while(env_head != NULL)
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

int		exec_fork(char *path, char **args, char **env)
{
	int pid;
	int ret;

	ret = 0;
	pid = fork();
	if (pid == 0)
	{
		execve(path, args, env);
		exit(errno);
	}
	else if (pid > 0)
	{
		wait(&ret);
		printf("child return code is: %d\n", ret);
	}
	return ret;
}

int 	exec(char **args, t_keyval *env_head)
{
	char	**path_arr;
	char	**env_arr;
	char	*path;

	env_arr = exec_join_env(env_head);
	if (ft_strrchr(args[0], '/') == 0)
	{
		if ((path_arr = exec_split_path(env_head)) != NULL)
		{
			if ((path = exec_check_path(path_arr, args[0])) != NULL)
			{
				exec_errors(exec_fork(path, args, env_arr), path);
				free(path);
			}
			else
				exec_errors(NO_EXECUTABLE, args[0]);
			free_2d(path_arr);
		}
		else
			exec_errors(NO_PATH, args[0]);
	}
	else
		exec_errors(exec_fork(args[0], args, env_arr), args[0]);
	free_2d(env_arr);
	return (0);
}

// TODO: unset old pwd
// TODO: pipes
// TODO: errors
// TODO: redirs
// TODO: shlvl
// TODO: отрефакторить билдины
// TODO: handler

/*
 * по итогу будет что-то типа
 * while (i < n_of_child_processes)
 * 	if (wait(&ret) == -1)
 * 		errno = 0;
 *
 */
