/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/03 16:13:46 by lubaujar          #+#    #+#             */
/*   Updated: 2015/11/03 16:13:47 by lubaujar         ###   ########.fr       */
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

t_node			*dlst_new(char *data)
{
	t_node	*new;

	new = (t_node *)malloc(sizeof(t_node));
	if (new)
	{
		new->s = ft_strdup(data);
		new->next = NULL;
		new->prev = NULL;
	}
	return (new);
}

t_dlist			*dlst_add_back(t_dlist *lst, t_node *node)
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

t_dlist			*dlst_del_one(t_dlist *lst, char *arg2del)
{
	t_node	*tmp;
	int		found;

	tmp = lst->head;
	found = 0;
	if (lst)
	{
		while (tmp && !found)
		{
			if (ft_strncmp(tmp->s, arg2del, ft_strlen(arg2del)) == 0)
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
	lst->lenght--;
	return (1);
}
