#include "./includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
	char			str[999];
	int				len;
	struct termios	term;
	int				i;

	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
//	term.c_lflag &= ~(ISIG); //отключить перед парсингом!
	tcsetattr(0, TCSANOW, &term);
//	term.c_cc[VMIN] = 200;
	tgetent(0, "xterm-256color");
	char *kek = "\033[01;31m\👹Mini🔥Hell👺☞\033[01;32m\ ";
//	FIXME траблы с esc
	while (write(1, kek, 40))
	{
		i = 0;
		tputs(save_cursor, 1, ft_putchar);
		while ((len = read(0, str, 999)))
		{
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
			else if (!(ft_strncmp(str, "\x1b[D", 3)))
				continue ;
			else if (!(ft_strncmp(str, "\x1b[C", 3)))
				continue ;
			else if (!(ft_strncmp(str, "\177", 2)) && i)
			{
//				tputs(restore_cursor, 1, ft_putchar);
				tputs(cursor_left, 1, ft_putchar);
				tputs(delete_character, 1, ft_putchar);
				i--;
			}
			else if (ft_strncmp(str, "\177", 2))
			{
				write(1, str, len);
				i += len;
				if (!(ft_strncmp(str, "\t", 2)))
					i += 6;
			}
			if (!(ft_strncmp(str, "\n", 2)))
				break ;
		}
	}
	return (0);
}
