//
// Created by neo on 02.05.2021.
//

#include "../includes/minishell.h"

static void rdr_out_1(t_param *param, char **error, int i)
{
	if (!param->com[i])
		*error = "\033[01;34m\MiniHell: syntax error near unexpected token `newline'\n";
	else if (param->com[i] == '|' && !param->com[i + 1])
		*error = "\033[01;34m\MiniHell: syntax error near unexpected token `newline'\n";
	else if (param->com[i] == '|' && param->com[i + 1] == '|' && param->com[i + 2] == '|')
		*error = "\033[01;34m\MiniHell: syntax error near unexpected token `||'\n";
	else if (param->com[i] == '|' && param->com[i + 1] == '|')
		*error = "\033[01;34m\MiniHell: syntax error near unexpected token `|'\n";
	else if ((param->com[i] == ';' && param->com[i + 1] == ';') ||\
	(param->com[i] == '|' && param->com[i + 1] == ';' && param->com[i + 2] == ';'))
		*error = "\033[01;34m\MiniHell: syntax error near unexpected token `;;'\n";
	else if ((param->com[i] == ';') || (param->com[i] == '|' && param->com[i + 1] == ';'))
		*error = "\033[01;34m\MiniHell: syntax error near unexpected token `;'\n";
}

static void rdr_out_2(t_param *param, char **error, int i)
{
	if (param->com[i] == '|')
		i++;
	if (param->com[i] == '>' && param->com[i + 1] == '>' && param->com[i + 2] == '>')
		*error = "\033[01;34m\MiniHell: syntax error near unexpected token `>>'\n";
	else if (param->com[i] == '>' && param->com[i + 1] == '>')
		*error = "\033[01;34m\MiniHell: syntax error near unexpected token `>'\n";
	else if (param->com[i] == '<' && param->com[i + 1] == '>')
		*error = "\033[01;34m\MiniHell: syntax error near unexpected token `<>'\n";
	else if (param->com[i] == '<' && param->com[i + 1] == '<' && param->com[i + 2] == '<')
		*error = "\033[01;34m\MiniHell: syntax error near unexpected token `<<<'\n";
	else if (param->com[i] == '<' && param->com[i + 1] == '<')
		*error = "\033[01;34m\MiniHell: syntax error near unexpected token `<<'\n";
	else if (param->com[i] == '<')
		*error = "\033[01;34m\MiniHell: syntax error near unexpected token `<'\n";
	else if (param->com[i - 1] == '|' && param->com[i] == '>')
		*error = "\033[01;34m\MiniHell: syntax error near unexpected token `>'\n";
}

static void rdr_out_3(t_param *param, char **error, int i)
{
	while (param->com[i] == ' ')
		i++;
	if (!param->com[i])
		*error = "\033[01;34m\MiniHell: syntax error near unexpected token `newline'\n";
	else if (param->com[i] == '|' && param->com[i + 1] == '|')
		*error = "\033[01;34m\MiniHell: syntax error near unexpected token `||'\n";
	else if (param->com[i] == '|')
		*error = "\033[01;34m\MiniHell: syntax error near unexpected token `|'\n";
	else if (param->com[i] == ';' && param->com[i + 1] == ';')
		*error = "\033[01;34m\MiniHell: syntax error near unexpected token `;;'\n";
	else if (param->com[i] == ';')
		*error = "\033[01;34m\MiniHell: syntax error near unexpected token `;'\n";
	else if (param->com[i] == '<' && param->com[i + 1] == '>')
		*error = "\033[01;34m\MiniHell: syntax error near unexpected token `<>'\n";
	else if (param->com[i] == '>' && param->com[i + 1] == '>')
		*error = "\033[01;34m\MiniHell: syntax error near unexpected token `>>'\n";
	else if (param->com[i] == '>')
		*error = "\033[01;34m\MiniHell: syntax error near unexpected token `>'\n";
	else if (param->com[i] == '<' && param->com[i + 1] == '<' && param->com[i + 2] == '<')
		*error = "\033[01;34m\MiniHell: syntax error near unexpected token `<<<'\n";
	else if (param->com[i] == '<' && param->com[i + 1] == '<')
		*error = "\033[01;34m\MiniHell: syntax error near unexpected token `<<'\n";
	else if (param->com[i] == '<')
		*error = "\033[01;34m\MiniHell: syntax error near unexpected token `<'\n";
}

int	second_pars_rdr_out(t_param *param, char **error, int i)
{
	i++;
	rdr_out_1(param, error, i);
	if (!*error && ((param->com[i] == '<' || param->com[i] == '>') ||\
	(param->com[i] == '|' && (param->com[i + 1] == '<' || param->com[i + 1] == '>'))))
		rdr_out_2(param, error, i);
	else if (!*error && (param->com[i] == ' ' || (param->com[i] == '|' && param->com[i + 1] == ' ' && ++i)))
		rdr_out_3(param, error, i);
	return (0);
}
