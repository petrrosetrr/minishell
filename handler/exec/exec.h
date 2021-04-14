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
#define EXEC_H
# include "../builtins/builtins.h"
# include <dirent.h>
# include "../utils/utils.h"
# define NO_PATH 123
# define NO_EXECUTABLE 512
# define IS_A_DIR 3328

typedef struct dirent	s_dir;
int						exec(char **args, t_keyval *env_head);

#endif
