/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 22:09:12 by jalease           #+#    #+#             */
/*   Updated: 2021/04/08 22:09:15 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
#include <sys/syslimits.h>
# include <stdlib.h>
# include <errno.h>
# include "../utils/utils.h"
# define IN 0
# define OUT 1
# define ERR 2
# define INVALID_ID 1

typedef struct		s_keyval
{
	char			*key;
	char			*value;
	struct s_keyval *next;
}					t_keyval;

typedef struct		s_shell {
	t_keyval		*env;
}					t_shell;

t_keyval			*env_to_list(char **env);
size_t				env_length(t_keyval *env_head);
t_keyval			**env_to_array(t_keyval *env_head);
t_keyval			*env_split(char *env_str);
t_keyval			*env_contains(t_keyval *env_head, char *key);
void				env_set(t_keyval *env_head, char *key, char *value, int plus);
void				env_delete(t_keyval **env_head, char *key);

int					cd_builtin(t_keyval **env_head,char **args);
int					echo_builtin(char **args);
int					env_builtin(t_keyval **env_head);
void				exit_builtin(char **args);
int					pwd_builtin(void);
int					export_builtin(t_keyval **env_head, char  **args);
int					unset_builtin(t_keyval **env_head, char **args);
#endif
