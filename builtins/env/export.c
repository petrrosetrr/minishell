/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 20:59:28 by jalease           #+#    #+#             */
/*   Updated: 2021/04/10 20:59:30 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

t_keyval	**export__sort(t_keyval *env_head)
{
	t_keyval	**env;
	t_keyval	*tmp;
	int			is_sorted;
	size_t		i;

	is_sorted = 0;
	env = env_to_array(env_head);
	while(!is_sorted)
	{
		i = 0;
		is_sorted = 1;
		while (i < env_length(env_head) - 1)
		{
			if(ft_strcmp(env[i]->key, env[i + 1]->key) > 0)
			{
				tmp = env[i];
				env[i] = env[i + 1];
				env[i + 1] = tmp;
				is_sorted = 0;
			}
			i++;
		}
	}
	return (env);
}

void		export_print(t_keyval **env)
{
	size_t i;

	i = 0;
	while(env != NULL && env[i] != NULL)
	{
		ft_putstr_fd("declare -x ", OUT);
		ft_putstr_fd(env[i]->key, OUT);
		if (env[i]->value != NULL)
		{
			ft_putstr_fd("=\"", OUT);
			ft_putstr_fd(env[i]->value, OUT);
			ft_putstr_fd("\"", OUT);
		}
		ft_putstr_fd("\n", OUT);
		i++;
	}
}

int 		export_print_error(char *key, int error_code)
{
	if (error_code == 1)
	{
		ft_putstr_fd("minishell: export: `", ERR);
		ft_putstr_fd(key, ERR);
		ft_putstr_fd("': not a valid identifier\n", ERR);
	}
	return (error_code);
}

int			export_valid(char *key)
{
	size_t i;

	if (ft_strlen(key) == 0)
		return export_print_error(key, INVALID_ID);
	if (!((key[0] >= 'a' && key[0] <= 'z')
		|| (key[0] >= 'A' && key[0] <= 'Z')
		|| (key[0] == '_')))
		return export_print_error(key, INVALID_ID);
	i = 1;
	while (key[i] != '\0')
	{
		if ((key[i] >= 'a' && key[i] <= 'z')
			|| (key[i] >= 'A' && key[i] <= 'Z')
			|| (key[i] == '_')
			|| (key[i] >= '0' && key[i] <= '9'))
			i++;
		else
		{
			if (i == ft_strlen(key) - 1 && key[i] == '+')
				i++;
			else
				return export_print_error(key, INVALID_ID);
		}
	}
	return (0);
}

int			export_set(t_keyval *env_head, char *env_str)
{
	t_keyval	*tmp;
	int			ret;

	tmp = env_split(env_str);
	if ((ret = export_valid(tmp->key)) == 0)
	{
		if (tmp->key[ft_strlen(tmp->key) - 1] == '+')
		{
			tmp->key[ft_strlen(tmp->key) - 1] = '\0';
			env_set(env_head, tmp->key, tmp->value, 1);
		}
		else
		{
			env_set(env_head, tmp->key, tmp->value, 0);
		}
	}
	free(tmp);
	return (ret);
}

int			export_builtin(t_keyval **env_head, char  **args)
{
	size_t i;

	if (env_head != NULL)
	{
		if (ft_arrlen(args) == 0)
		{
			export_print(export__sort(*env_head));
		}
		else
		{
			i = 0;
			while(args[i] != NULL)
			{
				export_set(*env_head, args[i]);
				i++;
			}
		}
		return (1);
	}
	return (0);
}
