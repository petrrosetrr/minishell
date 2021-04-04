#include "./includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
	char			str[999];
	int				len;
	struct termios	term;

	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &term);
//	term.c_cc[VMIN] = 200;
	tgetent(0, "xterm-256color");
	char *kek = key_down;
	while ((len = read(0, str, 999)))
	{
		str[len] = '\0';
//		len = read(0, str, 1000);
//		printf("%d\n", len);
//		printf("%s\n", str);
//		if (len != 1)
//			str[len] = '\0';
//		write(1, str, len);
		if (!(ft_strncmp(str, "\x1b[A", 7)))
			write(1, "up\n", 3);
		else if (!(ft_strncmp(str, "\x1b[B", 7)))
			write(1, "down\n", 5);
		else
			write(1, str, len);
//		if (!(ft_strncmp(str, "\n", 3)))
//			write(1, str, len);
//			write(1, str, len);
//			break ;
	}
	write(1, "\n", 1);
	return (0);
}
