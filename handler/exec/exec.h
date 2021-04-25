/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 17:43:44 by jalease           #+#    #+#             */
/*   Updated: 2021/04/13 17:43:47 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# include <dirent.h>
# include "../handler.h"
# include "../../defines.h"

typedef struct dirent	t_dir;
void					exec_errors(int ecode, char *path);
char					*exec_strjoin(char *s1, char *s2, char *s3);
char					*exec_check_path(char **dir, char *command);
char					**exec_split_path(t_keyval *env_head);
char					**exec_join_env(t_keyval *env_head);
void					exec_fork(char *path, char **args, char **env,
						int *fds);
void					exec(t_pars_list *command, t_keyval *env, int *fds);
#endif
