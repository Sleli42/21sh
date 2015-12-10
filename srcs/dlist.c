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
		new->head_node = NULL;
		new->tail_node = NULL;
	}
	return (new);
}

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

t_dlist			*dlst_add_back(t_dlist *lst, t_node *node)
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

t_dlist			*dlst_del_one(t_dlist *lst, char *arg2del)
{
	t_node	*tmp;
	int		found;

	tmp = lst->head_node;
	found = 0;
	if (lst)
	{
		while (tmp && !found)
		{
			if (ft_strncmp(tmp->s, arg2del, ft_strlen(arg2del)) == 0)
			{
				if (!tmp->next && !tmp->prev)
				{
					ft_strdel(&lst->head_node->s);
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
		lst->tail_node = elem->prev;
		lst->tail_node->next = NULL;
		ft_strdel(&elem->s);
	}
	else if (!elem->prev && elem->next)
	{
		lst->head_node = elem->next;
		lst->head_node->prev = NULL;
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

void			del_dlist(t_dlist *lst)
{
	t_node	*next_elem;
	t_node	*tmp;

	tmp = lst->head_node;
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
			if (tmp == lst->tail_node)
				return ;
		}
	}
}
