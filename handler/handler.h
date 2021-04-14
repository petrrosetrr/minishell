/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 06:21:22 by jalease           #+#    #+#             */
/*   Updated: 2021/04/14 06:21:26 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLER_H
#define HANDLER_H
# include "builtins/builtins.h"
# include "exec/exec.h"
# include "utils/utils.h"

t_keyval *handler_init(char **env);

#endif
