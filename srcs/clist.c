/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_list.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/11 15:23:55 by lubaujar          #+#    #+#             */
/*   Updated: 2015/12/11 15:23:57 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

t_select	*clst_create_elem(char *s)
{
	t_select	*new;

	if (!(new = (t_select *)malloc(sizeof(t_select))))
		return (NULL);
	new->arg = ft_strdup(s);
	new->onArg = 0;
	new->next = NULL;
	return (new);
}

t_clist		*clst_add_elem_back(t_clist *lst, t_select *node)
{
	if (lst && node)
	{
		if (lst->tail_node == NULL)
		{
			lst->head_node = node;
			lst->tail_node = node;
		}
		else
		{
			lst->tail_node->next = node;
			node->prev = lst->tail_node;
			lst->tail_node = node;
		}
		lst->lenght++;
	}
	return (lst);
}

void		del_clist(t_clist **lst)
{
	t_clist		*next_elem;
	t_clist		*nav;

	nav = *lst;
	next_elem = NULL;
	if (nav)
	{
		while (nav)
		{
			next_elem = nav->next;
			ft_strdel(&nav->arg);
			free(nav);
			nav = next_elem;
		}
	}
}