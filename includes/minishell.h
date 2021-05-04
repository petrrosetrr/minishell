/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 23:51:15 by jalease           #+#    #+#             */
/*   Updated: 2021/04/30 23:51:16 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define EXIT 2
# define CTRL_C 3

# define HARD_RDR 1
# define EZ_RDR 2

# define RDR_OUT 1
# define RDR_IN 2
# define PIPE 3

# define ENOCOMMAND 404

# define INVALID_ID 795

# define R_REWRITE 0
# define R_APPEND 1
# define IN 0
# define OUT 1
# define ERR 2

# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <termios.h>
# include <termcap.h>
# include <term.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <fcntl.h>
# include <dirent.h>
# include <limits.h>
# include <errno.h>

int						g_status;

typedef struct			s_keyval
{
	char				*key;
	char				*value;
	struct s_keyval		*next;
}						t_keyval;

typedef struct			s_rdr
{
	int					type;
	char				*f_name;
	struct s_rdr		*next;
}						t_rdr;

typedef struct			s_pars_list
{
	char				**args;
	t_rdr				*rdr_out;
	t_rdr				*rdr_in;
	struct s_pars_list	*next_pipe;
	int					*fds_pipe;
	int					fd_in;
}						t_pars_list;

typedef struct			s_param
{
	char				*com;
	char				*com_tmp;
	char				**all_com;
	int					cur;
	int					last;
	t_pars_list			*tmp_list;
	t_keyval			*env_list;
}						t_param;

typedef struct dirent	t_dir;

int						termcap(t_param *param);
int						key_func(char *str, t_param *param, int len, int *i);
char					*delete_last_char(char *com);
int						parser(t_param *param);
int						pre_parser(t_param *param);
void					freesher(t_param *param);
t_pars_list				*init_pars_list(void);
t_rdr					*init_rdr(void);
int						add_first_array(t_pars_list *pars_list);
int						add_array(char ***array, int i);
int						join_symbol(char **str, char symbol);
int						pars_backslash(t_param *param, char **str, int *i);
int						pars_quo_one(t_param *param, char **str, int *i);
int						pars_quo_two(t_param *param, char **str, int *i);
t_pars_list				*pars_pipe(t_param *param, t_pars_list *pars_list,
									int *i, int *arg);
int						pars_end_com(t_param *param, t_pars_list **pars_list,
									int *i, int *arg);
void					free_pars_list(t_pars_list **pars_list);
int						pars_rdr(t_param *param, t_rdr **rdr_out,
									t_rdr **rdr_in, int *i);
int						pars_env(t_param *param, char **str, int *i);
int						second_pars_rdr_out(t_param *param, char **error,
									int i);
int						second_pars_rdr_in(t_param *param, char **error, int i);
t_rdr					*free_null_elem(t_rdr *rdr);
int						dop_up_down(t_param *param);
void					add_first_arr(t_param *param);
void					add_last_arr(t_param *param);
void					dop_pre_pars_pipe(t_param *param, char **error, int i);

t_keyval				*handler_init(char **env);
void					handler(t_pars_list *command_list, t_keyval **env);

void					sig_handler(int signal);
int						is_builtin(char *command);
void					wait_n_close(t_pars_list *command_list);
int						c_list_len(t_pars_list *command_list);

int						redir_out(t_pars_list *command_list);
int						redir_in(t_pars_list *command_list);

void					env_set(t_keyval **env_head, char *key,
								char *value, int plus);
void					env_delete(t_keyval **env_head, char *key);
void					env_builtin(t_keyval *env_head);

void					env_free_one(t_keyval *env_item);
size_t					env_length(t_keyval *env_head);
t_keyval				*env_lst_new(char *key, char *value);
t_keyval				*env_contains(t_keyval *env_head, char *key);
void					env_lst_addback(t_keyval **env_head, t_keyval *new);

void					env_inc_sh(t_keyval **env_head);
char					*env_get(t_keyval *env_head, char *key);
t_keyval				**env_to_array(t_keyval *env_head);
t_keyval				*env_to_list(char **env);
t_keyval				*env_split(char *env_str);

void					export_print(t_keyval **env);
int						export_print_error(char *key, int error_code);
int						export_valid(char *key);
int						export_set(t_keyval **env_head, char *env_str);
void					export_builtin(t_keyval **env_head, char **args);
t_keyval				**export_sort(t_keyval *env_head);

int						unset_print_error(char *key, int error_code);
int						unset_valid(char *key);
void					unset_builtin(t_keyval **env_head, char **args);

void					env_builtin(t_keyval *env_head);

size_t					ft_arrlen(char **arr);
int						isdigitstr(char *str);
char					*ft_strndup(const char *s1, size_t length);
int						ft_strcmp(char *s1, char *s2);
void					free_2d(char **arr);
void					*fixed_free(void *content);

void					exec_errors(int ecode, char *path);
char					*exec_strjoin(char *s1, char *s2, char *s3);
char					*exec_check_path(char **dir, char *command);
char					**exec_split_path(t_keyval *env_head);
char					**exec_join_env(t_keyval *env_head);
void					exec_fork(char *path, char **args, char **env,
								int *fds);
void					exec(t_pars_list *command, t_keyval *env, int *fds);

void					cd_builtin(t_keyval **env_head, char **args);
void					export_builtin(t_keyval **env_head, char **args);
void					unset_builtin(t_keyval **env_head, char **args);
void					echo_builtin(char **args);
void					exit_builtin(char **args);
void					pwd_builtin(void);

#endif
