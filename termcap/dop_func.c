
#include "../includes/minishell.h"

char	*delete_last_char(char *com)
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

void	freesher(t_param *param)
{
	int i;

	i = -1;
	if (param->com)
		free(param->com);
	if (param->com_tmp)
		free(param->com_tmp);
	while (param->all_com && param->all_com[++i])
		free(param->all_com[i]);
	if (param->all_com)
		free(param->all_com);
}

void 	dop_up_down(t_param *param)
{
	if (++param->cur < param->last)
	{
		overfree(&param->com, NULL, NULL);
		param->com = ft_strdup(param->all_com[param->cur]);
		write(1, param->com, ft_strlen(param->com));
	}
	else
	{
		overfree(&param->com, NULL, NULL);
		if (param->com_tmp)
		{
			param->com = ft_strdup(param->com_tmp);
			write(1, param->com, ft_strlen(param->com));
		}
	}
}

void 	add_first_arr(t_param *param)
{
	param->all_com = (char**)malloc(sizeof(char*) * 2);
	param->all_com[0] = ft_strdup(param->com);
	param->all_com[1] = NULL;
	param->cur = ++param->last;
}

void	add_last_arr(t_param *param)
{
	char **temp;
	int i;

	i = -1;
	temp = param->all_com;
	param->last++;
	param->all_com = (char**)malloc(sizeof(char*) * (param->last + 1));
	param->all_com[param->last] = NULL;
	while (temp[++i])
		param->all_com[i] = temp[i];
	param->all_com[i] = ft_strdup(param->com);
	param->cur = param->last;
	free(temp);
}