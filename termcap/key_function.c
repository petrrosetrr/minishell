
#include "../includes/minishell.h"

static int	backspace(t_param *param, int i, int ws_col)
{
	int col;

	if (i / ws_col > 0 && !(i - (ws_col * (i / ws_col))))
	{
		col = ws_col;
		tputs(cursor_up, 1, ft_putchar);
		while (col--)
			tputs(cursor_right, 1, ft_putchar);
		write(1, " ", 1);
		tputs(cursor_left, 1, ft_putchar);
		tputs(cursor_right, 1, ft_putchar);
	}
	else
	{
		tputs(delete_character, 1, ft_putchar);
		tputs(cursor_left, 1, ft_putchar);
		tputs(delete_character, 1, ft_putchar);
	}
	if (param->com && param->com[0])
	{
		param->com = delete_last_char(param->com);
		if (param->last == param->cur)
			param->com_tmp = delete_last_char(param->com_tmp);
	}
	return (1);
}

static int	up_down_more(int i, int ws_col, int up)
{
	int col;

	i = i - (ws_col * (i / ws_col));
	while (i--)
	{
		tputs(cursor_left, 1, ft_putchar);
		tputs(delete_character, 1, ft_putchar);
	}
	tputs(delete_character, 1, ft_putchar);
	tputs(cursor_up, 1, ft_putchar);
	while (--up)
	{
		col = ws_col;
		while (col--)
			tputs(delete_character, 1, ft_putchar);
		tputs(cursor_up, 1, ft_putchar);
	}
	i = 16;
	while (i--)
		tputs(cursor_right, 1, ft_putchar);
	tputs(save_cursor, 1, ft_putchar);
	return (ws_col);
}

static int	up_down(t_param *param, int i, int ws_col, int f)
{
	int up;

	up = i / ws_col;
	if (up)
		i = up_down_more(i, ws_col, up);
	else
		tputs(restore_cursor, 1, ft_putchar);
	if (!f)
	{
		overfree(&param->com, NULL, NULL);
		param->com = ft_strdup(param->all_com[--param->cur]);
		up = ft_strlen(param->com);
		write(1, param->com, up);
	}
	else
		dop_up_down(param);
	while (i--)
		tputs(delete_character, 1, ft_putchar);
	return (16 + (f && param->cur == param->last && !param->com_tmp ? 0 : up));
}

static void	st_put(char *str, t_param *param, int i, int ws_col)
{
	char *temp;

	if (i / ws_col > 0 && !(i - (ws_col * (i / ws_col))))
	{
		write(1, " ", 1);
		tputs(delete_character, 1, ft_putchar);
		tputs(cursor_left, 1, ft_putchar);
		tputs(delete_character, 1, ft_putchar);
	}
	temp = param->com;
	if (!param->com)
	{
		param->com = ft_strdup(str);
		param->com_tmp = ft_strdup(param->com);
	}
	else
	{
		param->com = ft_strjoin(param->com, str);
		if (param->last == param->cur)
		{
			free(param->com_tmp);
			param->com_tmp = ft_strdup(param->com);
		}
		free(temp);
	}
}

int			key_func(char *str, t_param *param, int len, int *i)
{
	struct winsize	win;

	ioctl(1, TIOCGWINSZ, &win);
	str[len] = '\0';
	if (!ft_strncmp(str, "\n", 2) && write(1, "\n", 1))
		return (1);
	else if (!ft_strncmp(str, "\4", 1) && write(1, "\n", 1))
		return (EXIT);
	else if (!ft_strncmp(str, "\3", 1) && write(1, "\n", 1))
		return (CTRL_C);
	else if (!ft_strncmp(str, "\x1b[A", 3) && param->cur)
		*i = up_down(param, *i, win.ws_col, 0);
	else if (!ft_strncmp(str, "\x1b[B", 3) && param->cur < param->last)
		*i = up_down(param, *i, win.ws_col, 1);
	else if (!ft_strncmp(str, "\x1b[D", 3) || !ft_strncmp(str, "\x1b[C", 3) ||\
	!ft_strncmp(str, "\t", 2) || !ft_strncmp(str, "\x1b[A", 3) ||
	!ft_strncmp(str, "\x1b[B", 3))
		return (0);
	else if (!ft_strncmp(str, "\177", 2) && *i > 16)
		*i -= backspace(param, *i, win.ws_col);
	else if (ft_strncmp(str, "\177", 2) && write(1, str, len))
		st_put(str, param, (*i += len), win.ws_col);
	return (0);
}
