/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 22:28:45 by jalease           #+#    #+#             */
/*   Updated: 2021/04/08 22:28:47 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cd_errors(int error_code, char *path)
{
	if (error_code == 1)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", ERR);
	}
	else if (error_code == 2)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", ERR);
	}
	else
	{
		ft_putstr_fd("minishell: cd: ", ERR);
		ft_putstr_fd(path, ERR);
		ft_putstr_fd(": ", ERR);
		ft_putstr_fd(strerror(errno), ERR);
		ft_putstr_fd("\n", ERR);
	}
	errno = 1;
}

void	cd_home(t_keyval **env_head)
{
	char *home;
	char buf[PATH_MAX + 1];

	if (env_contains(*env_head, "HOME") != NULL &&
	(home = env_contains(*env_head, "HOME")->value) != NULL)
	{
		getcwd(buf, PATH_MAX + 1);
		if (!chdir(home))
		{
			env_set(env_head, ft_strdup("OLDPWD"), ft_strdup(buf), 0);
			env_set(env_head, ft_strdup("PWD"), ft_strdup(home), 0);
			errno = 0;
		}
		else
			cd_errors(-1, home);
	}
	else
		cd_errors(1, NULL);
}

void	cd_prev(t_keyval **env_head)
{
	char *prev;
	char buf[PATH_MAX + 1];

	if (env_contains(*env_head, "OLDPWD") != NULL &&
	(prev = env_contains(*env_head, "OLDPWD")->value) != NULL)
	{
		getcwd(buf, PATH_MAX + 1);
		if (!chdir(prev))
		{
			env_set(env_head, ft_strdup("OLDPWD"), ft_strdup(buf), 0);
			env_set(env_head, ft_strdup("PWD"), ft_strdup(prev), 0);
			errno = 0;
		}
		else
			cd_errors(-1, prev);
	}
	else
		cd_errors(2, NULL);
}

void	cd_path(t_keyval **env_head, char *path)
{
	char buf[PATH_MAX + 1];

	getcwd(buf, PATH_MAX + 1);
	if (chdir(path) == 0)
	{
		env_set(env_head, ft_strdup("OLDPWD"), ft_strdup(buf), 0);
		env_set(env_head, ft_strdup("PWD"), ft_strdup(path), 0);
		errno = 0;
	}
	else
		cd_errors(-1, path);
}

void	cd_builtin(t_keyval **env_head, char **args)
{
	if (args != NULL)
	{
		if (ft_arrlen(args) == 0 || ft_strcmp(args[0], "~") == 0)
			cd_home(env_head);
		else if (ft_strcmp(args[0], "-") == 0)
			cd_prev(env_head);
		else
			cd_path(env_head, args[0]);
	}
}
