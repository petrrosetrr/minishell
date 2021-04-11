/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 18:50:22 by jalease           #+#    #+#             */
/*   Updated: 2021/04/09 18:50:25 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"



t_list	*lst_new(void *value)
{
	t_list *new;

	if ((new = malloc(sizeof  t_list)) == NULL)
		return (NULL);
	new->content = value;
	new->next = NULL;
	return new;
}

void lst_addfront(t_list **lst_head, t_list *new)
{
	if (lst_head == NULL || new == NULL)
		return ;
	new->next = *lst_head;
	*lst_head = new;
}

void lst_addback(t_list **lst_head, t_list *new)
{
	t_list *tmp;

	if (lst_head == NULL || new == NULL)
		return ;
	new->next = NULL;
	if (*lst_head != NULL)
	{
		tmp = *lst_head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*lst_head = new;
}

void lst_delone(t_list **lst_head, t_list *del, void (*f_del)(void*))
{
	//TODO: Переписать
}
