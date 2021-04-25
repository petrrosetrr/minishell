/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 02:56:42 by jalease           #+#    #+#             */
/*   Updated: 2021/04/22 02:56:44 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_DEFINES_H
# define MINISHELL_DEFINES_H
# define R_REWRITE 0
# define R_APPEND 1
# define IN 0
# define OUT 1
# define ERR 2

typedef struct		s_keyval
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
	int 				*fds_pipe;
	int					fd_in;
}						t_pars_list;

#endif
