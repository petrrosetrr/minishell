//
// Created by Daisey Patrica on 4/12/21.
//

#include "../includes/minishell.h"

int pre_parser(t_param *param)
{
	int i;
	char *error;

	error = NULL;
//	param->com -= (i = drop_space(&param->com));
	i = drop_space(&param->com);
	if (*param->com == ';' && *(param->com + 1) == ';')
		error = "\033[01;34m\MiniHell: syntax error near unexpected token `;;'\n";
	else if (*param->com == ';')
		error = "\033[01;34m\MiniHell: syntax error near unexpected token `;'\n";
	else if (*param->com == '|' && *(param->com + 1) == '|') // FIXME добавить еще условие для разделения аргументов тремя пайпами
		error = "\033[01;34m\MiniHell: syntax error near unexpected token `||'\n";
	else if (*param->com == '|')
		error = "\033[01;34m\MiniHell: syntax error near unexpected token `|'\n";
	else if (*param->com == '.' && ++i)
	{
		param->com++;
		i += drop_space(&param->com);
		if (!*param->com)
			error = "\033[01;34m\MiniHell: .: filename argument required\n.: usage: . filename [arguments]\n";
		else if ((param->com -= i))
			i = drop_space(&param->com);
	}
	while (!error && *param->com)
	{
		if (*param->com == ')')
			error = "\033[01;34m\MiniHell: syntax error near unexpected token `)'\n";
		else if (*param->com == ';' && *(param->com + 1) == ';')
			error = "\033[01;34m\MiniHell: syntax error near unexpected token `;;'\n";
		else if (*param->com == '|')
		{
			if (' ')
			i += drop_space(&param->com);
			if (*param->com == '|' && *(param->com + 1) == '|')
				error = "\033[01;34m\MiniHell: syntax error near unexpected token `||'\n";
			else if (*param->com == '|')

		}
		param->com++;
		i++;
	}
//	else if (param->com[i] == ';')
//		error = "\033[01;34m\MiniHell: \n";
//	else if (param->com[i] == ';')
//		error = "\033[01;34m\MiniHell: \n";
//	else if (param->com[i] == ';')
//		error = "\033[01;34m\MiniHell: \n";
//	else if (param->com[i] == ';')
//		error = "\033[01;34m\MiniHell: \n";
//	else if (param->com[i] == ';')
//		error = "\033[01;34m\MiniHell: \n";
//	else if (param->com[i] == ';')
//		error = "\033[01;34m\MiniHell: \n";
//	else if (param->com[i] == ';')
//		error = "\033[01;34m\MiniHell: \n";
//	else if (param->com[i] == ';')
//		error = "\033[01;34m\MiniHell: \n";
//	else if (param->com[i] == ';')
//		error = "\033[01;34m\MiniHell: \n";
//	else if (param->com[i] == ';')
//		error = "\033[01;34m\MiniHell: \n";
//	else if (param->com[i] == ';')
//		error = "\033[01;34m\MiniHell: \n";
	param->com -= i;
	return (error ? (int)(write(1, error, ft_strlen(error))) : 0);
}
