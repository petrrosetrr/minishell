#include "./includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
	char			str[9999];
	int				len;
	int				i;
//	int				bit;
	int				down;
	int				col;
	struct termios	term;
	struct winsize	win;

	down = 0;
	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHO); // -ехо
	term.c_lflag &= ~(ICANON); // -посимвольно
//	term.c_lflag &= ~(ISIG); // -сигналы отключить перед парсингом!
	tcsetattr(0, TCSANOW, &term);
//	term.c_cc[VMIN] = 200;
	tgetent(0, "xterm-256color");
	char *kek = "\033[01;31m\👹Mini🔥Hell👺☞\033[01;32m\ ";
//	FIXME траблы с esc
	while (write(1, kek, 40))
	{
		i = 0;
		tputs(save_cursor, 1, ft_putchar);
		while ((len = read(0, str, 9999)))
		{
//			ioctl(0, FIONREAD, &bit);
			ioctl(1, TIOCGWINSZ, &win);
			str[len] = '\0';
			if (!(ft_strncmp(str, "\x1b[A", 3)))
			{
				tputs(restore_cursor, 1, ft_putchar);
				write(1, "up", 2);
				while (i--)
					tputs(delete_character, 1, ft_putchar);
				i = 2;
			}
			else if (!(ft_strncmp(str, "\x1b[B", 3)))
			{
				tputs(restore_cursor, 1, ft_putchar);
				write(1, "down", 4);
				while (i--)
					tputs(delete_character, 1, ft_putchar);
				i = 4;
			}
//			else if (!(ft_strncmp(str, "\x1b[D", 3)))
//				continue ;
//			else if (!(ft_strncmp(str, "\x1b[C", 3)))
//				continue ;
			else if (!(ft_strncmp(str, "\t", 2)))
				continue ;
			else if (!(ft_strncmp(str, "\177", 2)) && i)
			{
				if (down && ((i - (((win.ws_col - 1) * down) - 16)) == 0))
				{
					col = win.ws_col - 2;
					tputs(cursor_up, 1, ft_putchar);
					while (col--)
						tputs(cursor_right, 1, ft_putchar);
					tputs(delete_character, 1, ft_putchar);
					down--;
				}
				else
				{
					tputs(cursor_left, 1, ft_putchar);
					tputs(delete_character, 1, ft_putchar);
				}
				i--;
/*				if (i == (win.ws_col - 16))
				{
					col = win.ws_col - 2;
					tputs(cursor_up, 1, ft_putchar);
					while (col--)
						tputs(cursor_right, 1, ft_putchar);
//					tputs(cursor_left, 1, ft_putchar);
					tputs(delete_character, 1, ft_putchar);
					i--;
				}
				else
				{
					tputs(cursor_left, 1, ft_putchar);
					tputs(delete_character, 1, ft_putchar);
					i--;
				}*/
			}
			else if (ft_strncmp(str, "\177", 2))
			{
				if ((!down && i < (win.ws_col - 17)) ||\
				(down && ((i - (((win.ws_col - 1) * down) - 17)) < win.ws_col)))
				{
					write(1, str, len);
					i += len;
				}
				if ((!down && i >= (win.ws_col - 17)) ||\
				(down && ((i - (((win.ws_col - 1) * down) - 17)) >= win.ws_col)))
				{
					down++;
					tputs(cursor_down, 1, ft_putchar);
				}
/*				else
				{
					down++;
					tputs(cursor_down, 1, ft_putchar);
					write(1, str, len);
					i += len;
				}*/
//				if (!(ft_strncmp(str, "\t", 2)))
//					i += 6;
			}
			if (!(ft_strncmp(str, "\n", 2)))
			{
//				tputs(cursor_down, 1, ft_putchar);
//				printf("%d\n", win.ws_col);
				break ;
			}
		}
	}
	return (0);
}
