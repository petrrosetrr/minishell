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

#include "../../../includes/minishell.h"

void		env_set(t_keyval **env_head, char *key, char *value, int plus)
{
	t_keyval	*tmp;
	char		*new_value;

	if ((tmp = env_contains(*env_head, key)) != NULL)
	{
		if (value != NULL)
		{
			if (plus)
			{
				new_value = ft_strjoin(tmp->value, value);
				free(value);
			}
			else
				new_value = value;
			free(tmp->value);
			tmp->value = new_value;
		}
		free(key);
	}
	else
		env_lst_addback(env_head, env_lst_new(key, value));
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

void		env_builtin(t_keyval *env_head)
{
	while (env_head != NULL)
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
	g_status = 0;
}
