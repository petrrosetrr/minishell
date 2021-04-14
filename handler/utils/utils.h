/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 18:37:34 by jalease           #+#    #+#             */
/*   Updated: 2021/04/09 18:37:36 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
#define UTILS_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "../../libft/libft.h"

//typedef struct		s_list
//{
//	void			*value;
//	struct s_list	*next;
//}					t_list;

size_t	ft_arrlen(char **arr);
int		isdigitstr(char *str);
char	*ft_strndup(const char *s1, size_t length);
int		ft_strcmp(char *s1, char *s2);
void	free_2d(char **arr);
void	*fixed_free(void *content);

//t_list	*lst_new(void *value);
//void	lst_addfront(t_list **lst_head, t_list *new);
//void	lst_addback(t_list **lst_head, t_list *new);
//void	lst_delone(t_list **lst_head, t_list *del, void (*f_del)(void*));
//t_list	*lst_new(void *value);
//char	*ft_strchr(const char *s, int c);
#endif
