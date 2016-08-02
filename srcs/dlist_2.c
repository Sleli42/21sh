/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/03 16:13:46 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/21 16:04:55 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

t_dlist2	*dlst_insert_cmd(t_all *all, t_dlist2 *lst, t_cmd *node, int pos)
{
	t_cmd	*tmp;
	int		ct;

	tmp = lst->head;
	ct = 0;
	while (tmp && ++ct <= pos)
	{
		if (pos == ct || !tmp->next)
		{
			if (dlst_insert_cmd_extended(all, lst, tmp, node))
				return (lst);
			else
			{
				node->prev = tmp->prev;
				node->next = tmp;
				tmp->prev->next = node;
				tmp->prev = node;
				lst->lenght++;
			}
		}
		else
			tmp = tmp->next;
	}
	return (lst);
}

t_dlist2	*dlist_add_front_2(t_dlist2 *lst, t_cmd *node)
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

t_dlist2	*dlst_add_back_2(t_dlist2 *lst, t_cmd *node)
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

static int	dlst_del_one2_ex(t_cmd **tmp, t_dlist2 **lst, int *found)
{
	if (!(*tmp)->next && !(*tmp)->prev)
	{
		(*tmp)->c = 0;
		free((*tmp));
		(*lst)->lenght--;
		(*lst)->tail = NULL;
		(*lst)->head = (*tmp);
		return (1);
	}
	else
		(*found) = update_list2((*lst), (*tmp));
	(*lst)->lenght--;
	free((*tmp));
	return (0);
}

t_dlist2	*dlst_del_one2(t_dlist2 *lst, int pos)
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
			if (ct++ == pos)
			{
				if (dlst_del_one2_ex(&tmp, &lst, &found))
					return (lst);
			}
			tmp = tmp->next;
		}
	}
	return (lst);
}
