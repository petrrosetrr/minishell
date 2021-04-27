/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 00:41:25 by jalease           #+#    #+#             */
/*   Updated: 2021/04/22 00:41:27 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void		env_inc_sh(t_keyval **env_head)
{
	t_keyval	*tmp;
	int			val;

	val = 1;
	if ((tmp = env_contains(*env_head, "SHLVL")) != NULL)
		val += ((tmp->value != NULL) ? ft_atoi(tmp->value) : 0);
	env_set(env_head, ft_strdup("SHLVL"), ft_itoa(val), 0);
}

char		*env_get(t_keyval *env_head, char *key)
{
	t_keyval *tmp;

	if ((tmp = env_contains(env_head, key)) != NULL)
		return (tmp->value);
	else
		return (ft_strdup(""));
}

t_keyval	**env_to_array(t_keyval *env_head)
{
	size_t		i;
	t_keyval	**env;

	i = 0;
	env = ft_calloc(sizeof(t_keyval*), 1 + env_length(env_head));
	while (env_head)
	{
		env[i++] = env_head;
		env_head = env_head->next;
	}
	env[i] = NULL;
	return (env);
}

t_keyval	*env_to_list(char **env)
{
	t_keyval	*list_head;
	int			i;

	if (env != NULL)
	{
		i = 1;
		list_head = env_split(env[0]);
		while (env[i] != NULL)
		{
			env_lst_addback(&list_head, env_split(env[i]));
			i++;
		}
		return (list_head);
	}
	return (NULL);
}

t_keyval	*env_split(char *env_str)
{
	t_keyval *ret;

	if (env_str != NULL)
	{
		ret = env_lst_new(NULL, NULL);
		if (ft_strchr(env_str, '=') != NULL)
		{
			ret->key = ft_strndup(env_str, ft_strchr(env_str, '=') - env_str);
			ret->value = ft_strdup(ft_strchr(env_str, '=') + 1);
		}
		else
		{
			ret->key = ft_strdup(env_str);
			ret->value = NULL;
		}
		return (ret);
	}
	return (NULL);
}
