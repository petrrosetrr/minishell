//
// Created by Daisey Patrica on 4/10/21.
//

#include "../includes/minishell.h"

static int pre_pars(t_param *param)
{
	int i;
	char **temp;

	i = 0;
	while (param->com[i] == ' ')
		i++;
	if (!param->com[i])
		return (1);
	i = -1;
	if (!param->last)
	{
		param->all_com = (char**)malloc(sizeof(char*) * 2);
		param->all_com[0] = ft_strdup(param->com);
		param->all_com[1] = NULL;
		param->cur = ++param->last;
	}
	else
	{
		temp = param->all_com;
		param->last++;
		param->all_com = (char**)malloc(sizeof(char*) * (param->last + 1));
		param->all_com[param->last] = NULL;
		while (temp[++i])
			param->all_com[i] = temp[i];
//		if (param->last == ++param->cur)
		param->all_com[i] = ft_strdup(param->com);
//		else
//			param->all_com[i] = ft_strdup(param->all_com[--param->cur]);
		param->cur = param->last;
		free(temp);
	}
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

static int 	termcap_2(t_param *param, struct termios *term)
{
	char			str[9999];
	int				len;
	int				i;
	int				n;

	char *kek = "\033[01;31m\👹Mini🔥Hell👺☞\033[01;32m\ ";
//	char *kek;
//	kek = ft_strdup("\033[01;31m\👹Mini🔥Hell👺☞\033[01;32m\ ");
	n = 0;
	str[0] = '\0';
	while (n != EXIT) // вынести за условие
	{
		if (n && n != CTRL_C && param->com && param->com[0])
		{
//			write(1, "1\n", 2);
			term_on_off(term, 0);
//			if (pre_pars(param))
//				;
			if (!pre_pars(param) && parser(param))
				n = 0; // n = 0 и term_on_off
			term_on_off(term, 1);
			if (!n)
				continue ;
		}
		write(1, kek, 40);
		tputs(save_cursor, 1, ft_putchar);
		overfree(&param->com, &param->com_tmp, NULL);
//		if (param->com)
//			free(param->com);
//		param->com = NULL;
//		if (param->com_tmp)
//			free(param->com_tmp);
//		param->com_tmp = NULL;
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

	term_on_off(&term, 1);
//	tcgetattr(0, &term);
//	term.c_lflag &= ~(ECHO); // -ехо
//	term.c_lflag &= ~(ICANON); // -посимвольно
//	term.c_lflag &= ~(ISIG); // -сигналы / отключить перед парсингом!
//	tcsetattr(0, TCSANOW, &term);
	tgetent(0, "xterm-256color"); // добавить адаптивный терминал
	termcap_2(param, &term);
//	tcgetattr(0, &term);
//	term.c_lflag |= ~(ECHO);
//	term.c_lflag |= ~(ICANON);
//	term.c_lflag |= ~(ISIG);
//	tcsetattr(0, TCSANOW, &term);
	term_on_off(&term, 0);
	freesher(param);
	exit_builtin(NULL);
	return (0);
}