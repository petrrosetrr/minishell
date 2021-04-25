/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utiils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 00:40:16 by jalease           #+#    #+#             */
/*   Updated: 2021/04/22 00:40:18 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_keyval	**export_sort(t_keyval *env_head)
{
	t_keyval	**env;
	t_keyval	*tmp;
	int			is_sorted;
	size_t		i;

	is_sorted = 0;
	env = env_to_array(env_head);
	while (!is_sorted)
	{
		i = 0;
		is_sorted = 1;
		while (i < env_length(env_head) - 1)
		{
			if (ft_strcmp(env[i]->key, env[i + 1]->key) > 0)
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
