//
// Created by Daisey Patrica on 4/12/21.
//

#include "../includes/minishell.h"

//static int test2(t_param *param, int *i, char **error)
//{
//	if (param->com[*i] == ';' && (param->com[(*i) + 1]) == ';')
//		*error = "\033[01;34m\MiniHell: syntax error near unexpected token `;;'\n";
//	else if (param->com[*i] == ';')
//		*error = "\033[01;34m\MiniHell: syntax error near unexpected token `;'\n";
//	else if (param->com[*i] == '|' && (param->com[*i] + 1) == '|') // FIXME добавить еще условие для разделения аргументов тремя пайпами
//		*error = "\033[01;34m\MiniHell: syntax error near unexpected token `||'\n";
//	else if (param->com[*i] == '|')
//		*error = "\033[01;34m\MiniHell: syntax error near unexpected token `|'\n";
//	else if (param->com[*i] == '.' && ++i)
//	{
//		param->com++;
//		i += drop_space(&param->com);
//		if (!param->com[*i])
//			*error = "\033[01;34m\MiniHell: .: filename argument required\n.: usage: . filename [arguments]\n";
//		else if ((param->com -= i))
//			i = drop_space(&param->com);
//	}
//}
//
//static void test(t_param *param)
//{
//	int i;
//	char *error;
//
//	error = NULL;
//	i = 0;
//	while (param->com[i])
//	{
//		if (param->com[i] == ' ')
//			i++;
//		else
//			test2(param, &i, &error);
//	}
//}

static int first_pre_pars(t_param *param, char **error)
{
	int i;

	i = drop_space(&param->com);
	if (*param->com == ';' && *(param->com + 1) == ';')
		*error = "\033[01;34m\MiniHell: syntax error near unexpected token `;;'\n";
	else if (*param->com == ';')
		*error = "\033[01;34m\MiniHell: syntax error near unexpected token `;'\n";
	else if (*param->com == '|' && *(param->com + 1) == '|') // FIXME добавить еще условие для разделения аргументов тремя пайпами
		*error = "\033[01;34m\MiniHell: syntax error near unexpected token `||'\n";
	else if (*param->com == '|')
		*error = "\033[01;34m\MiniHell: syntax error near unexpected token `|'\n";
	else if (*param->com == '.' && ++i)
	{
		param->com++;
		i += drop_space(&param->com);
		if (!*param->com)
			*error = "\033[01;34m\MiniHell: .: filename argument required\n.: usage: . filename [arguments]\n";
	}
	param->com -= i;
	return (0);
}

static int second_pars_end_sym(t_param *param, char **error, int i)
{
	if (param->com[i] == ';' && param->com[i + 1] == ';')
		*error = "\033[01;34m\MiniHell: syntax error near unexpected token `;;'\n";
	else if (param->com[i] == ';')
	{
		i++;
		while (param->com[i] == ' ')
			i++;
		if (param->com[i])
		{
			if (param->com[i] == ';' && param->com[i + 1] == ';')
				*error = "\033[01;34m\MiniHell: syntax error near unexpected token `;;'\n";
			else if (param->com[i] == ';')
				*error = "\033[01;34m\MiniHell: syntax error near unexpected token `;'\n";
			else if (param->com[i] == '|' && param->com[i + 1] == '|')
				*error = "\033[01;34m\MiniHell: syntax error near unexpected token `||'\n";
			else if (param->com[i] == '|')
				*error = "\033[01;34m\MiniHell: syntax error near unexpected token `|'\n";
		}
	}
	return (0);
}

static int second_pars_pipe(t_param *param, char **error, int i)
{
	int space;

	i++;
	space = 0;
	if (param->com[i] && param->com[i] == '|' && param->com[i + 1] &&\
	param->com[i + 1] == '|')
	{
		*error = "\033[01;34m\MiniHell: syntax error near unexpected token `|'\n";
		if (param->com[i + 2] && param->com[i + 2] == '|')
			*error = "\033[01;34m\MiniHell: syntax error near unexpected token `||'\n";
		return (0);
	}
	while (param->com[i] == ' ' && ++space)
		i++;
	if (param->com[i] && space)
	{
		if (param->com[i] == '|' && param->com[i + 1] == '|')
			*error = "\033[01;34m\MiniHell: syntax error near unexpected token `||'\n";
		else if (param->com[i] == '|')
			*error = "\033[01;34m\MiniHell: syntax error near unexpected token `|'\n";
	}
	return (0);
}

static int second_pars_rdr_out(t_param *param, char **error, int i)
{
	return (0);
}

static int second_pars_rdr_in(t_param *param, char **error, int i)
{
	return (0);
}

int pre_parser(t_param *param)
{
	int i;
	char *error;

	i = 0;
	error = NULL;
	first_pre_pars(param, &error);
	while (!error && param->com[i])
	{
		if (param->com[i] == ';')
			second_pars_end_sym(param, &error, i);
		else if (param->com[i] == '|') // доработать два пайпа подряд || после арг (сега)
			second_pars_pipe(param, &error, i);
		else if (param->com[i] == '>')
			second_pars_rdr_out(param, &error, i);
		else if (param->com[i] == '<')
			second_pars_rdr_in(param, &error, i);
		i++;
	}
	//FIXME отдельный парсер по элементам
//	param->com -= (i = drop_space(&param->com));
//	i = drop_space(&param->com);
//	if (*param->com == ';' && *(param->com + 1) == ';')
//		error = "\033[01;34m\MiniHell: syntax error near unexpected token `;;'\n";
//	else if (*param->com == ';')
//		error = "\033[01;34m\MiniHell: syntax error near unexpected token `;'\n";
//	else if (*param->com == '|' && *(param->com + 1) == '|') // FIXME добавить еще условие для разделения аргументов тремя пайпами
//		error = "\033[01;34m\MiniHell: syntax error near unexpected token `||'\n";
//	else if (*param->com == '|')
//		error = "\033[01;34m\MiniHell: syntax error near unexpected token `|'\n";
//	else if (*param->com == '.' && ++i)
//	{
//		param->com++;
//		i += drop_space(&param->com);
//		if (!*param->com)
//			error = "\033[01;34m\MiniHell: .: filename argument required\n.: usage: . filename [arguments]\n";
//		else if ((param->com -= i))
//			i = drop_space(&param->com);
//	}
//	while (!error && *param->com)
//	{
//		if (*param->com == ')')
//			error = "\033[01;34m\MiniHell: syntax error near unexpected token `)'\n";
//		else if (*param->com == ';' && *(param->com + 1) == ';')
//			error = "\033[01;34m\MiniHell: syntax error near unexpected token `;;'\n";
//		else if (*param->com == '|')
//		{
//			if (' ')
//				i += drop_space(&param->com);
//			if (*param->com == '|' && *(param->com + 1) == '|')
//				error = "\033[01;34m\MiniHell: syntax error near unexpected token `||'\n";
//			else if (*param->com == '|')
//
//		}
//		param->com++;
//		i++;
//	}
////	else if (param->com[i] == ';')
////		error = "\033[01;34m\MiniHell: \n";
//	param->com -= i;
	return (error ? (int)(write(1, error, ft_strlen(error))) : 0);
}
