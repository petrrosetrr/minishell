/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 00:44:00 by jalease           #+#    #+#             */
/*   Updated: 2021/04/22 00:44:03 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "env.h"

void		env_free_one(t_keyval *env_item)
{
	if (env_item->key != NULL)
		free(env_item->key);
	if (env_item->value != NULL)
		free(env_item->value);
	free(env_item);
}

size_t		env_length(t_keyval *env_head)
{
	size_t i;

	i = 0;
	while (env_head)
	{
		env_head = env_head->next;
		i++;
	}
	return (i);
}

t_keyval	*env_lst_new(char *key, char *value)
{
	t_keyval *new;

	if ((new = malloc(sizeof(t_keyval))) == NULL)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

t_keyval	*env_contains(t_keyval *env_head, char *key)
{
	while (env_head != NULL)
	{
		if (ft_strcmp(env_head->key, key) == 0)
			return (env_head);
		env_head = env_head->next;
	}
	return (NULL);
}

void		env_lst_addback(t_keyval **env_head, t_keyval *new)
{
	t_keyval *tmp;

	tmp = *env_head;
	if (env_head != NULL && *env_head != NULL && new != NULL)
	{
		new->next = NULL;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else if (new != NULL)
	{
		*env_head = new;
	}
}
