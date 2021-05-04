/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpatrica <dpatrica@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 07:09:55 by dpatrica          #+#    #+#             */
/*   Updated: 2021/05/04 07:09:58 by dpatrica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	pre_pars(t_param *param)
{
	int		i;

	i = 0;
	while (param->com[i] == ' ')
		i++;
	if (!param->com[i])
		return (1);
	if (!param->last)
		add_first_arr(param);
	else
		add_last_arr(param);
	return (0);
}

static void	term_on_off(struct termios *term, int flag)
{
	if (!flag)
	{
		tcgetattr(0, term);
		term->c_lflag |= ECHO;
		term->c_lflag |= ICANON;
		term->c_lflag |= ISIG;
		tcsetattr(0, TCSANOW, term);
	}
	else
	{
		tcgetattr(0, term);
		term->c_lflag &= ~(ECHO);
		term->c_lflag &= ~(ICANON);
		term->c_lflag &= ~(ISIG);
		tcsetattr(0, TCSANOW, term);
	}
}

static int	pars_and_go(t_param *param, struct termios *term, int n)
{
	term_on_off(term, 0);
	if (!pre_pars(param) && parser(param))
		n = 0;
	term_on_off(term, 1);
	return (n);
}

static int	termcap_2(t_param *param, struct termios *term)
{
	char			str[9999];
	int				len;
	int				i;
	int				n;

	n = 0;
	str[0] = '\0';
	while (n != EXIT)
	{
		if (n && n != CTRL_C && param->com && param->com[0])
		{
			n = pars_and_go(param, term, n);
			if (!n)
				continue ;
		}
		write(1, "\033[01;31m👹Mini🔥Hell👺☞\033[01;32m ", 40);
		tputs(save_cursor, 1, ft_putchar);
		overfree(&param->com, &param->com_tmp, NULL);
		i = 16;
		while ((len = read(0, str, 9999)))
			if ((n = key_func(str, param, len, &i)))
				break ;
	}
	return (0);
}

int			termcap(t_param *param)
{
	struct termios	term;
	char			*terminal;

	terminal = env_get(param->env_list, "TERM");
	if (!*terminal)
	{
		free(terminal);
		terminal = NULL;
	}
	term_on_off(&term, 1);
	tgetent(0, terminal ? terminal : "xterm-256color");
	termcap_2(param, &term);
	term_on_off(&term, 0);
	free(terminal);
	freesher(param);
	exit_builtin(NULL);
	return (0);
}
