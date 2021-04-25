/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 18:34:21 by jalease           #+#    #+#             */
/*   Updated: 2021/04/09 18:34:23 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int		ft_strcmp(char *s1, char *s2)
{
	size_t length;

	length = (ft_strlen(s1) > ft_strlen(s2)) ? ft_strlen(s1) : ft_strlen(s2);
	return ft_strncmp(s1, s2, length);
}

size_t	ft_arrlen(char **arr)
{
	size_t i;

	i = 0;
	while(arr != NULL && arr[i])
		i++;
	return (i);
}

void	free_2d(char **arr)
{
	size_t i;

	i = 0;
	if (arr != NULL)
	{
		while(arr[i] != NULL)
			free(arr[i++]);
	}
	free(arr);
	arr = NULL;
}

int		isdigitstr(char *str)
{
	if (!str)
		return (0);
	if ((int)(ft_strlen(str)) == ft_digitlen(ft_atoi(str)))
		return (1);
	else
		return (0);
}

void	*fixed_free(void *content)
{
	if (content != NULL)
	{
		free(content);
		content = NULL;
	}
	return (NULL);
}

char	*ft_strndup(const char *s1, size_t length)
{
	char	*ret;
	size_t	i;

	i = 0;
	ret = ft_calloc(length > ft_strlen(s1) ? ft_strlen(s1) + 1: length + 1, 1);
	while (i < length && i < ft_strlen(s1))
	{
		ret[i] = s1[i];
		i++;
	}
	return ret;
}
