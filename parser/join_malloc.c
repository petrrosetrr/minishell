
#include "../includes/minishell.h"

int	add_array(char ***array, int i)
{
	char	**temp;
	int		k;

	k = -1;
	if (!array)
		return (1);
	temp = *array;
	*array = (char**)malloc(sizeof(char*) * (i + 2));
	while (temp[++k])
		(*array)[k] = temp[k];
	free(temp);
	(*array)[k] = (char*)malloc(sizeof(char) * 2);
	(*array)[k][0] = '\0';
	(*array)[k][1] = '\0';
	(*array)[++k] = NULL;
	return (0);
}

int	add_first_array(t_pars_list *pars_list)
{
	pars_list->args = (char**)malloc(sizeof(char*) * 2);
	pars_list->args[0] = (char*)malloc(sizeof(char) * 2);
	pars_list->args[0][0] = '\0';
	pars_list->args[0][1] = '\0';
	pars_list->args[1] = NULL;
	return (0);
}

int	join_symbol(char **str, char symbol)
{
	char	*temp;
	char	*sym;

	if ((*str)[0] == '\0')
	{
		free(*str);
		*str = (char*)malloc(sizeof(char) * 2);
		(*str)[0] = symbol;
		(*str)[1] = '\0';
	}
	else
	{
		sym = (char*)malloc(sizeof(char) * 2);
		sym[0] = symbol;
		sym[1] = '\0';
		temp = *str;
		*str = ft_strjoin(*str, sym);
		free(temp);
		free(sym);
	}
	return (0);
}
