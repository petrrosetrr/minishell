/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpatrica <dpatrica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 20:20:39 by dpatrica          #+#    #+#             */
/*   Updated: 2020/11/20 00:09:24 by dpatrica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		gln_free(char *tbuf, char *buf, int ret)
{
	free(buf);
	if (tbuf)
		free(tbuf);
	return (ret);
}

static size_t	glen(char *buf, int n)
{
	size_t i;

	i = 0;
	if (!buf)
		return (0);
	if (n == 0)
		while (buf[i])
			i++;
	else if (n == 1)
		while (buf[i] != '\n' && buf[i])
			i++;
	else if (n == 2)
		while (*buf)
			if (*buf++ == '\n')
				return (1);
	return (i);
}

static char		*gnl_strdup(char *s1, int n)
{
	char	*arr;
	char	*rar;

	if ((arr = (char*)malloc((glen(s1, n) + 1) * sizeof(char))) == NULL)
		return (NULL);
	rar = arr;
	if (n == 0)
		while (*s1)
			*arr++ = *s1++;
	else
		while (*s1 != '\n' && *s1)
			*arr++ = *s1++;
	*arr = '\0';
	return (rar);
}

static char		*gnl_strjoin(char *tbuf, char *buf, int fri)
{
	char	*arr;
	size_t	sh;
	int		i;

	if (!tbuf || fri == 1)
	{
		arr = gnl_strdup(buf, 0);
		if (fri == 1)
			free(tbuf);
		return (arr);
	}
	sh = sizeof(char);
	if (!(arr = (char*)malloc((glen(tbuf, 0) + glen(buf, 0) + 1) * sh)))
		return (NULL);
	i = -1;
	while (tbuf[++i])
		arr[i] = tbuf[i];
	while (*buf)
		arr[i++] = *buf++;
	arr[i] = '\0';
	free(tbuf);
	return (arr);
}

int				get_next_line(int fd, char **line)
{
	ssize_t		j;
	int			n;
	char		*buf;
	static char	*tbuf[1025];

	if ((BUFFER_SIZE < 1) || (BUFFER_SIZE > 2147483646))
		return (-1);
	if ((buf = (char*)malloc((BUFFER_SIZE + 1) * sizeof(char))) == NULL)
		return (-1);
	j = BUFFER_SIZE;
	while (((n = glen(tbuf[fd], 2)) == 0) && (j == BUFFER_SIZE))
	{
		if ((j = read(fd, buf, BUFFER_SIZE)) < 0)
			return (gln_free(tbuf[fd], buf, -1));
		buf[j] = '\0';
		if ((tbuf[fd] = gnl_strjoin(tbuf[fd], buf, 0)) == NULL)
			return (gln_free(tbuf[fd], buf, -1));
	}
	if ((*line = gnl_strdup(tbuf[fd], n)) == NULL)
		return (gln_free(tbuf[fd], buf, -1));
	if (n == 0)
		return (gln_free(tbuf[fd], buf, 0));
	free(buf);
	tbuf[fd] = gnl_strjoin(tbuf[fd], (tbuf[fd] + glen(tbuf[fd], n) + 1), 1);
	return (tbuf[fd] == NULL ? -1 : 1);
}
