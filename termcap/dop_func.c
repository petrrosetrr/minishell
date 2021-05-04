
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

void dop_pre_pars_pipe(t_param *param, char **error, int i)
{
	if (param->com[i] == '|' && param->com[i + 1] == '|')
		*error = "\033[01;34mMiniHell: "
				 "syntax error near unexpected token `||'\n";
	else if (param->com[i] == '|')
		*error = "\033[01;34mMiniHell: "
				 "syntax error near unexpected token `|'\n";
}