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
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <errno.h>
# include "../../libft/libft.h"
# include "../utils/utils.h"
# include "../handler.h"
# include "env/env.h"

void				cd_builtin(t_keyval **env_head, char **args);
void				export_builtin(t_keyval **env_head, char **args);
void				unset_builtin(t_keyval **env_head, char **args);
void				echo_builtin(char **args);
void				exit_builtin(char **args);
void				pwd_builtin(void);

#endif
