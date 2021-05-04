/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_pars_rdr_in.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpatrica <dpatrica@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 07:11:37 by dpatrica          #+#    #+#             */
/*   Updated: 2021/05/04 07:11:42 by dpatrica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	rdr_in_1(t_param *param, char **error, int i)
{
	if (!param->com[i])
		*error = "\033[01;34mMiniHell: "
			"syntax error near unexpected token `newline'\n";
	else if (param->com[i] == '|' && !param->com[i + 1])
		*error = "\033[01;34mMiniHell: "
			"syntax error near unexpected token `newline'\n";
	else if (param->com[i] == '|' && param->com[i + 1] == '|' &&\
	param->com[i + 2] == '|')
		*error = "\033[01;34mMiniHell: "
			"syntax error near unexpected token `||'\n";
	else if (param->com[i] == '|' && param->com[i + 1] == '|')
		*error = "\033[01;34mMiniHell: "
			"syntax error near unexpected token `|'\n";
	else if ((param->com[i] == ';' && param->com[i + 1] == ';') ||\
	(param->com[i] == '|' && param->com[i + 1] == ';' &&\
	param->com[i + 2] == ';'))
		*error = "\033[01;34mMiniHell: "
			"syntax error near unexpected token `;;'\n";
	else if ((param->com[i] == ';') ||\
	(param->com[i] == '|' && param->com[i + 1] == ';'))
		*error = "\033[01;34mMiniHell: "
			"syntax error near unexpected token `;'\n";
}

static void	rdr_in_2(t_param *param, char **error, int i)
{
	if (param->com[i] == '|')
		i++;
	if (param->com[i] == '<' && param->com[i + 1] == '<' &&\
	param->com[i + 2] == '<')
		*error = "\033[01;34mMiniHell: "
			"syntax error near unexpected token `<<'\n";
	else if (param->com[i] == '<' && param->com[i + 1] == '<')
		*error = "\033[01;34mMiniHell: "
			"syntax error near unexpected token `<'\n";
	else if (param->com[i] == '<' && param->com[i + 1] == '>')
		*error = "\033[01;34mMiniHell: "
			"syntax error near unexpected token `<>'\n";
	else if (param->com[i] == '>' && param->com[i + 1] == '>' &&\
	param->com[i + 2] == '>')
		*error = "\033[01;34mMiniHell: "
			"syntax error near unexpected token `>>>'\n";
	else if (param->com[i] == '>' && param->com[i + 1] == '>')
		*error = "\033[01;34mMiniHell: "
			"syntax error near unexpected token `>>'\n";
	else if (param->com[i] == '>')
		*error = "\033[01;34mMiniHell: "
			"syntax error near unexpected token `>'\n";
	else if (param->com[i - 1] == '|' && param->com[i] == '<')
		*error = "\033[01;34mMiniHell: "
			"syntax error near unexpected token `<'\n";
}

static void	rdr_in_3(t_param *param, char **error, int i)
{
	if (!param->com[i])
		*error = "\033[01;34mMiniHell: "
			"syntax error near unexpected token `newline'\n";
	else if (param->com[i] == '|' && param->com[i + 1] == '|')
		*error = "\033[01;34mMiniHell: "
			"syntax error near unexpected token `||'\n";
	else if (param->com[i] == '|')
		*error = "\033[01;34mMiniHell: "
			"syntax error near unexpected token `|'\n";
	else if (param->com[i] == ';' && param->com[i + 1] == ';')
		*error = "\033[01;34mMiniHell: "
			"syntax error near unexpected token `;;'\n";
	else if (param->com[i] == ';')
		*error = "\033[01;34mMiniHell: "
			"syntax error near unexpected token `;'\n";
	else if (param->com[i] == '<' && param->com[i + 1] == '>')
		*error = "\033[01;34mMiniHell: "
			"syntax error near unexpected token `<>'\n";
	else if (param->com[i] == '<' && param->com[i + 1] == '<')
		*error = "\033[01;34mMiniHell: "
			"syntax error near unexpected token `<<'\n";
	else if (param->com[i] == '<')
		*error = "\033[01;34mMiniHell: "
			"syntax error near unexpected token `<'\n";
}

static void	rdr_in_4(t_param *param, char **error, int i)
{
	if (param->com[i] == '>' && param->com[i + 1] == '>' &&\
	param->com[i + 2] == '>')
		*error = "\033[01;34mMiniHell: "
			"syntax error near unexpected token `>>>'\n";
	else if (param->com[i] == '>' && param->com[i + 1] == '>')
		*error = "\033[01;34mMiniHell: "
			"syntax error near unexpected token `>>'\n";
	else if (param->com[i] == '>')
		*error = "\033[01;34mMiniHell: "
			"syntax error near unexpected token `>'\n";
}

int			second_pars_rdr_in(t_param *param, char **error, int i)
{
	i++;
	rdr_in_1(param, error, i);
	if (!*error && ((param->com[i] == '<' || param->com[i] == '>') ||\
	(param->com[i] == '|' && (param->com[i + 1] == '<' ||\
	param->com[i + 1] == '>'))))
		rdr_in_2(param, error, i);
	else if (!*error && (param->com[i] == ' ' ||\
	(param->com[i] == '|' && param->com[i + 1] == ' ' && ++i)))
	{
		while (param->com[i] == ' ')
			i++;
		rdr_in_3(param, error, i);
		if (!*error)
			rdr_in_4(param, error, i);
	}
	return (0);
}
