/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overfree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpatrica <dpatrica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 21:19:43 by dpatrica          #+#    #+#             */
/*   Updated: 2021/04/12 05:48:27 by dpatrica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	overfree(char **str1, char **str2, char **str3)
{
	int i;

	i = 0;
	if (str1 && *str1 && ++i)
	{
		free(*str1);
		*str1 = NULL;
	}
	if (str2 && *str2 && ++i)
	{
		free(*str2);
		*str2 = NULL;
	}
	if (str3 && *str3 && ++i)
	{
		free(*str3);
		*str3 = NULL;
	}
	return (i);
}
