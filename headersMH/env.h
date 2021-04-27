/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 00:47:18 by jalease           #+#    #+#             */
/*   Updated: 2021/04/22 00:47:20 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H
# include "../builtins.h"
# define INVALID_ID 795
# include "../../../defines.h"

void		env_set(t_keyval **env_head, char *key, char *value, int plus);
void		env_delete(t_keyval **env_head, char *key);
void		env_builtin(t_keyval *env_head);

void		env_free_one(t_keyval *env_item);
size_t		env_length(t_keyval *env_head);
t_keyval	*env_lst_new(char *key, char *value);
t_keyval	*env_contains(t_keyval *env_head, char *key);
void		env_lst_addback(t_keyval **env_head, t_keyval *new);

void		env_inc_sh(t_keyval **env_head);
char		*env_get(t_keyval *env_head, char *key);
t_keyval	**env_to_array(t_keyval *env_head);
t_keyval	*env_to_list(char **env);
t_keyval	*env_split(char *env_str);

void		export_print(t_keyval **env);
int			export_print_error(char *key, int error_code);
int			export_valid(char *key);
int			export_set(t_keyval **env_head, char *env_str);
void		export_builtin(t_keyval **env_head, char **args);
t_keyval	**export_sort(t_keyval *env_head);

int			unset_print_error(char *key, int error_code);
int			unset_valid(char *key);
void		unset_builtin(t_keyval **env_head, char **args);

void		env_builtin(t_keyval *env_head);

#endif
