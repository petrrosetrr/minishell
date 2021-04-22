/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 06:45:14 by jalease           #+#    #+#             */
/*   Updated: 2021/04/11 06:45:16 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int			unset_print_error(char *key, int error_code)
{
	if (error_code == INVALID_ID)
	{
		ft_putstr_fd("minishell: unset: `", ERR);
		ft_putstr_fd(key, ERR);
		ft_putstr_fd("': not a valid identifier\n", ERR);
		errno = INVALID_ID;
	}
	return (error_code);
}

int			unset_valid(char *key)
{
	size_t i;

	if (ft_strlen(key) == 0)
		return (unset_print_error(key, INVALID_ID));
	if (!((key[0] >= 'a' && key[0] <= 'z')
	|| (key[0] >= 'A' && key[0] <= 'Z')
	|| (key[0] == '_')))
		return (unset_print_error(key, INVALID_ID));
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
			return (unset_print_error(key, INVALID_ID));
		}
	}
	return (0);
}

void		unset_builtin(t_keyval **env_head, char **args)
{
	size_t i;

	if (args != NULL)
	{
		i = 0;
		while (args[i])
		{
			if (unset_valid(args[i]) == 0)
			{
				env_delete(env_head, args[i]);
				errno = 0;
			}
			i++;
		}
	}
}
