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

t_clist		*create_clst(void)
{
	t_clist	*new;

	if (!(new = (t_clist *)malloc(sizeof(t_clist))))
		return (NULL);
	else
	{
		new->lenght = 0;
		new->head = NULL;
		new->tail = NULL;
	}
	return (new);
}

t_select	*clst_create_elem(char *s)
{
	t_select	*new;

	if (!(new = (t_select *)malloc(sizeof(t_select))))
		return (NULL);
	new->arg = ft_strdup(s);
	new->onArg = 0;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_clist		*clst_add_elem_back(t_clist *lst, t_select *node)
{
	if (lst && node)
	{
		if (lst->tail == NULL)
		{
			lst->head = node;
			lst->tail = node;
		}
		else
		{
			lst->tail->next = node;
			node->prev = lst->tail;
			lst->tail = node;
		}
		lst->lenght++;
	}
	return (lst);
}

int			len_clst(t_select *lst)
{
	t_select	*nav;
	int			ret;

	nav = lst;
	ret = 0;
	if (nav)
	{
		while (nav)
		{
			ret++;
			nav = nav->next;
		}
	}
	return (ret);
}

void		del_clist(t_clist **lst)
{
	t_select	*next_elem;
	t_select	*nav;

	nav = (*lst)->head;
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