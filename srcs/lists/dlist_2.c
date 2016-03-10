/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/03 16:13:46 by lubaujar          #+#    #+#             */
/*   Updated: 2015/11/03 16:13:47 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

t_dlist2		*dlst_insert_cmd(t_dlist2 *lst, t_cmd *node, int pos)
{
	t_cmd	*tmp;
	int		ct;

	tmp = lst->head;
	ct = 1;
	while (tmp && ct <= pos)
	{
		if (pos == ct)
		{
			if (tmp->next == NULL)
			{
				lst = dlst_add_back_2(lst, node);
				swap_elems_cmd(lst->tail, lst->tail->prev);
				return (lst);
			}
			else if (tmp->prev == NULL)
			{
				lst = dlist_add_front_2(lst, node);
				return (lst);
			}
			else
			{
				if (node)
				{
					node->prev = tmp->prev;
					node->next = tmp;
					tmp->prev->next = node;
					tmp->prev = node;
					lst->lenght++;
				}
			}
		}
		else
			tmp = tmp->next;
		ct++;
	}
	return (lst);
}

t_dlist2		*dlist_add_front_2(t_dlist2 *lst, t_cmd *node)
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
			lst->head->prev = node;
			node->next = lst->head;
			lst->head = node;
		}
		lst->lenght++;
	}
	return (lst);
}

t_dlist2		*dlst_add_back_2(t_dlist2 *lst, t_cmd *node)
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

t_dlist2		*dlst_del_one2(t_dlist2 *lst, int pos)
{
	t_cmd	*tmp;
	int		found;
	int		ct;

	tmp = lst->head;
	found = 0;
	ct = 1;
	if (lst)
	{
		while (tmp && !found)
		{
			if (ct == pos)
			{
				if (!tmp->next && !tmp->prev)
				{
					tmp->c = 0;
					free(tmp);
					lst->lenght--;
					lst->tail = NULL;
					return (lst);
				}
				else
					found = update_list2(lst, tmp);
				lst->lenght--;
				free(tmp);
			}
			ct++;
			tmp = tmp->next;
		}
	}
	return (lst);
}

void			del_dlist2(t_dlist2 *lst)
{
	t_cmd	*next_elem;
	t_cmd	*tmp;

	tmp = lst->head;
	next_elem = NULL;
	if (tmp)
	{
		while (tmp)
		{
			next_elem = tmp->next;
			if (tmp->c)
				tmp->c = 0;
			if (tmp)
				free(tmp);
			tmp = next_elem;
			lst->lenght = 0;
			if (tmp == lst->tail)
				return ;
		}
	}
}
