
#include "minishell.h"
int main(int argc, char **argv, char **env)
{
	t_keyval *env_list;
	(void) argc;
	(void) argv;

	// handler init
	env_list = handler_init(env);

	t_pars_list *head = malloc(sizeof(t_pars_list));
	head->args = ft_calloc(sizeof(char *), 3);
	head->args[0] = ft_strdup("cd");
	head->args[1] = ft_strdup("krkr");
	head->fds_pipe = NULL;
	head->fd_in = -1;
	head->rdr_out = NULL;
	head->rdr_in = NULL;
////	head->rdr_in = malloc(sizeof (t_rdr));
////	head->rdr_in->f_name = ft_strdup("ekkekekeke");
////	head->rdr_in->type = R_APPEND;
////	head->rdr_in->next = NULL;
//	head->next_pipe = NULL;

	head->next_pipe = malloc(sizeof(t_pars_list));
	head->next_pipe->args = ft_calloc(sizeof (char*), 3);
	head->next_pipe->args[0] = ft_strdup("cd");
	head->next_pipe->args[1] = ft_strdup("~");
	head->next_pipe->fd_in = -1;
	head->next_pipe->rdr_in = NULL;
	head->next_pipe->rdr_out = NULL;

	head->next_pipe->next_pipe = malloc(sizeof(t_pars_list));
	head->next_pipe->next_pipe->args = ft_calloc(sizeof (char*), 3);
	head->next_pipe->next_pipe->args[0] = ft_strdup("cd");
	head->next_pipe->next_pipe->args[1] = ft_strdup("-");
	head->next_pipe->next_pipe->fd_in = -1;
	head->next_pipe->next_pipe->rdr_in = NULL;
	head->next_pipe->next_pipe->rdr_out = NULL;

	head->next_pipe->next_pipe->next_pipe = malloc(sizeof(t_pars_list));
	head->next_pipe->next_pipe->next_pipe->args = ft_calloc(sizeof (char*), 3);
	head->next_pipe->next_pipe->next_pipe->args[0] = ft_strdup("pwd");
//	head->next_pipe->next_pipe->next_pipe->args[1] = ft_strdup("~");
	head->next_pipe->next_pipe->next_pipe->fd_in = -1;
	head->next_pipe->next_pipe->next_pipe->rdr_in = NULL;
	head->next_pipe->next_pipe->next_pipe->rdr_out = NULL;


	handler(head, &env_list);

	head->args = ft_calloc(sizeof(char *), 3);
	head->args[0] = ft_strdup("echo");
	head->args[1] = ft_strdup("kek");
	head->fd_in = -1;
	head->fds_pipe = NULL;
	head->rdr_out = NULL;
	head->rdr_in = NULL;
	head->next_pipe = NULL;
	handler(head, &env_list);

//	head->next_pipe = NULL;
//
////	env_builtin(env_list);
//	head->next_pipe = malloc(sizeof(t_pars_list));
//	head->next_pipe->args = ft_calloc(sizeof (char*), 2);
//	head->next_pipe->args[0] = ft_strdup("wc");
//	head->next_pipe->fd_in = -1;
//	head->next_pipe->rdr_in = NULL;
//	head->next_pipe->rdr_out = NULL;
}