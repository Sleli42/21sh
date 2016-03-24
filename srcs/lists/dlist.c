/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/03 16:13:46 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/21 16:05:01 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

t_node		*dlst_node_new(char *data, size_t index)
{
	t_node	*new;

	new = (t_node *)malloc(sizeof(t_node));
	if (new)
	{
		new->s = ft_strdup(data);
		new->index = index;
		new->next = NULL;
		new->prev = NULL;
	}
	return (new);
}

t_dlist		*dlst_add_back(t_dlist *lst, t_node *node)
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

t_dlist		*dlst_del_one(t_dlist *lst, char *arg2del)
{
	t_node	*tmp;
	int		found;

	tmp = lst->head;
	found = 0;
	if (lst)
	{
		while (tmp && !found)
		{
			if (!ft_strncmp(tmp->s, arg2del, ft_strlen(arg2del)))
			{
				if (!tmp->next && !tmp->prev)
				{
					ft_strdel(&lst->head->s);
					free(lst);
				}
				else
					found = update_list(lst, tmp);
				lst->lenght--;
				free(tmp);
			}
			tmp = tmp->next;
		}
	}
	return (lst);
}

void		del_dlist(t_dlist *lst)
{
	t_node	*next_elem;
	t_node	*tmp;

	tmp = lst->head;
	next_elem = NULL;
	if (tmp)
	{
		while (tmp)
		{
			next_elem = tmp->next;
			if (tmp->s)
				ft_strdel(&tmp->s);
			if (tmp)
				free(tmp);
			tmp = next_elem;
			if (tmp == lst->tail)
				return ;
		}
	}
}
