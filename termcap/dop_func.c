//
// Created by Daisey Patrica on 4/11/21.
//

#include "../includes/minishell.h"

char *delete_last_char(char *com)
{
	char *temp;

	if (!com)
		return (NULL);
	temp = com;
	com[ft_strlen(com) - 1] = '\0';
	com = ft_strdup(com);
	free(temp);
	return (com);
}
