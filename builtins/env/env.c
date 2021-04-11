/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 22:29:46 by jalease           #+#    #+#             */
/*   Updated: 2021/04/08 22:29:48 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"


t_keyval	**env_to_array(t_keyval *env_head)
{
	size_t		i;
	t_keyval	**env;

	i = 0;
	env = ft_calloc(sizeof (t_keyval*), 1 + env_length(env_head));
	while (env_head)
	{
		env[i++] = env_head;
		env_head = env_head->next;
	}
	env[i] = NULL;
	return (env);
}

size_t		env_length(t_keyval *env_head)
{
	size_t i;

	i = 0;
	while(env_head)
	{
		env_head = env_head->next;
		i++;
	}
	return (i);
}

t_keyval	*env_lst_new(char *key, char *value)
{
	t_keyval *new;

	if (!(new = malloc(sizeof (t_keyval))))
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return new;
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

t_keyval	*env_contains(t_keyval *env_head, char *key)
{
	while(env_head != NULL)
	{
		if (ft_strcmp(env_head->key, key) == 0)
			return (env_head);
		env_head = env_head->next;
	}
	return (NULL);
}

void		env_lst_addback(t_keyval *env_head, t_keyval *new)
{
	if (env_head != NULL && new != NULL)
	{
		new->next = NULL;
		while (env_head->next)
			env_head = env_head->next;
		env_head->next = new;
	}
}

void		env_set(t_keyval *env_head, char *key, char *value, int plus)
{
	t_keyval *tmp;
	char	 *new_value;

	if ((tmp = env_contains(env_head, key)) != NULL)
	{
		if (tmp->value != NULL)
		{
			if (plus)
			{
				new_value = ft_strjoin(tmp->value, value);
				free(value);
			}
			else
				new_value = value;
			free(tmp->value);
			free(key);
			tmp->value = new_value;
		}
	}
	else
		env_lst_addback(env_head, env_lst_new(key, value));
}

void		env_free_one(t_keyval *env_item)
{
	if (env_item->key != NULL)
		free(env_item->key);
	if (env_item->value != NULL)
		free(env_item->value);
	free(env_item);
}

void		env_delete(t_keyval **env_head, char *key)
{
	t_keyval *tmp_prev;
	t_keyval *tmp;
	t_keyval *tmp_next;

	if (env_head != NULL && key != NULL)
	{
		tmp_prev = NULL;
		tmp = *env_head;
		while (tmp != NULL)
		{
			if (ft_strcmp(tmp->key, key) == 0)
			{
				tmp_next = tmp->next;
				env_free_one(tmp);
				if (tmp_prev != NULL)
					tmp_prev->next = tmp_next;
				if (*env_head == tmp)
					*env_head = tmp_next;
				return ;
			}
			tmp_prev = tmp;
			tmp = tmp->next;
		}
	}
}

t_keyval	*env_to_list(char **env)
{
	t_keyval	*list_head;
	int			i;
	errno = 13;
	if (env != NULL)
	{
		i = 1;
		list_head = env_split(env[0]);
		while (env[i] != NULL)
		{
			env_lst_addback(list_head, env_split(env[i]));
			i++;
		}
		return (list_head);
	}
	return (NULL);
}

int			env_builtin(t_keyval *env_head)
{
	while(env_head != NULL)
	{
		if (env_head->value != NULL)
		{
			ft_putstr_fd(env_head->key, OUT);
			ft_putstr_fd("=", OUT);
			ft_putstr_fd(env_head->value, OUT);
			ft_putstr_fd("\n", OUT);
		}
		env_head = env_head->next;
	}
	return (1);
}
