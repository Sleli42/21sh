/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/03 18:21:43 by lubaujar          #+#    #+#             */
/*   Updated: 2016/01/03 18:21:45 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

t_dlist			*create_dlst(void)
{
	t_dlist	*new;

	new = (t_dlist*)malloc(sizeof(t_dlist));
	if (new != NULL)
	{
		new->lenght = 0;
		new->head = NULL;
		new->tail = NULL;
	}
	return (new);
}

int				len_lst_node(t_node *lst)
{
	t_node		*nav;
	int			ret;

	nav = lst;
	ret = 0;
	while (nav)
	{
		ret++;
		nav = nav->next;
	}
	return (ret);
}

int				update_list(t_dlist *lst, t_node *elem)
{
	if (!elem->next && elem->prev)
	{
		lst->tail = elem->prev;
		lst->tail->next = NULL;
		ft_strdel(&elem->s);
	}
	else if (!elem->prev && elem->next)
	{
		lst->head = elem->next;
		lst->head->prev = NULL;
		ft_strdel(&elem->s);
	}
	else
	{
		elem->prev->next = elem->next;
		elem->next->prev = elem->prev;
		ft_strdel(&elem->s);
	}
	return (1);
}