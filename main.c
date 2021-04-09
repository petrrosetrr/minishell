#include "./includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
	char			str[9999];
	int				len;
	int				i;
	int				up;
//	int				bit;
	int				col;
	struct termios	term;
	struct winsize	win;

	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHO); // -ехо
	term.c_lflag &= ~(ICANON); // -посимвольно
//	term.c_lflag &= ~(ISIG); // -сигналы / отключить перед парсингом!
	tcsetattr(0, TCSANOW, &term);
//	term.c_cc[VMIN] = 200;
	tgetent(0, "xterm-256color");
	char *kek = "\033[01;31m\👹Mini🔥Hell👺☞\033[01;32m\ ";
//	FIXME траблы с esc
	while (write(1, kek, 40))
	{
		i = 16;
		tputs(save_cursor, 1, ft_putchar);
		while ((len = read(0, str, 9999)))
		{
//			ioctl(0, FIONREAD, &bit);
			ioctl(1, TIOCGWINSZ, &win);
			str[len] = '\0';
			if (!(ft_strncmp(str, "\x1b[A", 3)))
			{
				up = i / win.ws_col;
				if (up)
				{
					i = i - (win.ws_col * (i / win.ws_col));
					while (i--)
					{
						tputs(cursor_left, 1, ft_putchar);
						tputs(delete_character, 1, ft_putchar);
					}
					tputs(delete_character, 1, ft_putchar);
					tputs(cursor_up, 1, ft_putchar);
					while (--up)
					{
						col = win.ws_col;
						while (col--)
							tputs(delete_character, 1, ft_putchar);
						tputs(cursor_up, 1, ft_putchar);
					}
					i = 16;
					while (i--)
						tputs(cursor_right, 1, ft_putchar);
					tputs(save_cursor, 1, ft_putchar);
					i = win.ws_col;
				}
				else
					tputs(restore_cursor, 1, ft_putchar);
				write(1, "up", 2);
				while (i--)
					tputs(delete_character, 1, ft_putchar);
				i = 16 + 2;
			}
			else if (!(ft_strncmp(str, "\x1b[B", 3)))
			{
				up = i / win.ws_col;
				if (up)
				{
					i = i - (win.ws_col * (i / win.ws_col));
					while (i--)
					{
						tputs(cursor_left, 1, ft_putchar);
						tputs(delete_character, 1, ft_putchar);
					}
					tputs(delete_character, 1, ft_putchar);
					tputs(cursor_up, 1, ft_putchar);
					while (--up)
					{
						col = win.ws_col;
						while (col--)
							tputs(delete_character, 1, ft_putchar);
						tputs(cursor_up, 1, ft_putchar);
					}
					i = 16;
					while (i--)
						tputs(cursor_right, 1, ft_putchar);
					tputs(save_cursor, 1, ft_putchar);
					i = win.ws_col;
				}
				else
					tputs(restore_cursor, 1, ft_putchar);
				write(1, "down", 4);
				while (i--)
					tputs(delete_character, 1, ft_putchar);
				i = 16 + 4;
			}
			else if (!(ft_strncmp(str, "\x1b[D", 3)))
				continue ;
			else if (!(ft_strncmp(str, "\x1b[C", 3)))
				continue ;
			else if (!(ft_strncmp(str, "\t", 2)))
				continue ;
//				tputs(delete_character, 1, ft_putchar);
			else if (!(ft_strncmp(str, "\177", 2)) && i > 16)
			{
				if (i / win.ws_col > 0 && !(i - (win.ws_col * (i / win.ws_col))))
				{
					col = win.ws_col;
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
				i--;
			}
			else if (ft_strncmp(str, "\177", 2))
			{
				write(1, str, len);
				i += len;
				if (i / win.ws_col > 0 && !(i - (win.ws_col * (i / win.ws_col))))
				{
					write(1, " ", 1);
					tputs(delete_character, 1, ft_putchar);
					tputs(cursor_left, 1, ft_putchar);
					tputs(delete_character, 1, ft_putchar);
				}
			}
			if (!(ft_strncmp(str, "\n", 2)))
				break ;
		}
	}
	return (0);
}
