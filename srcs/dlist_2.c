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

t_dlist2		*create_cmd_dlst(void)
{
	t_dlist2	*new;

	if (!(new = (t_dlist2 *)malloc(sizeof(t_dlist2))))
		return (NULL);
	else
	{
		new->lenght = 0;
		new->tail = NULL;
		new->head = NULL;
	}
	return (new);
}

t_cmd			*dlst_cmd_new(char c)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (new)
	{
		new->c = c;
		new->next = NULL;
		new->prev = NULL;
	}
	return (new);
}

void		swap_elems_cmd(t_cmd *a, t_cmd *b)
{
	char	tmp;

	tmp = a->c;
	a->c = b->c;
	b->c = tmp;
}

t_dlist2		*dlst_insert_cmd(t_dlist2 *lst, t_cmd *node, int pos)
{
	t_cmd	*tmp;
	int		ct;

	tmp = lst->head;
	ct = 1;
	//pos = (pos == 0) ? 1 : pos;
	//display_dlst(lst);
	//printf("cursor on node : %d\n", pos);
	while (tmp && ct <= pos)
	{
		if (pos == ct)
		{
			//printf("node: %c\n", tmp->c);
			if (tmp->next == NULL)
			{
				//printf("tail: %c && tmp: %c\n", lst->tail->c, tmp->c);
				lst = dlst_add_back_2(lst, node);
				swap_elems_cmd(lst->tail, lst->tail->prev);
				return (lst);

			}
			else if (tmp->prev == NULL)
			{
				//write(1, "begin\n", 6);
				lst = dlist_add_front_2(lst, node);
				return (lst);
			}
			else
			{
				if (node)
				{			/* probleme here */
					node->prev = tmp->prev;
					node->next = tmp;
					//printf("tmp->prev->next :%c\n", tmp->prev->next->c);
					tmp->prev->next = node;
					// printf("tmp->prev->next :%c\n", tmp->prev->next->c);
					// node->prev = tmp->prev;
					// node->next = tmp;
					tmp->prev = node;
					// printf("node->prev: %c\n", node->prev->c);
					// printf("node->next: %c\n", node->next->c);
					// printf("tmp: %c\n", tmp->c);
					// printf("tmp prev: %c\n", tmp->prev->c);
					// printf("tmp next: %c\n", tmp->next->c);
					// tmp->next->prev = node;
					// tmp->prev->next = node;
					// node->prev = tmp->prev;
					// tmp->prev = node;
					// node->next = tmp;
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
	//printf("--->|%c|\n", node->c);
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
	//printf("lenght list[add]: %zu\n", lst->lenght);
	return (lst);
}

int				len_lst_cmd(t_cmd *lst)
{
	t_cmd		*nav;
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

t_dlist2			*dlst_del_one2(t_dlist2 *lst, char arg2del)
{
	t_cmd	*tmp;
	int		found;

	tmp = lst->tail;
	found = 0;
	if (lst)
	{
		// display_dlst2(lst);
		while (tmp && !found)
		{
			if (tmp->c == arg2del)
			{
				//printf("arg found: |%c|\n", tmp->c);
				if (!tmp->next && !tmp->prev)
				{
					tmp->c = 0;
					free(tmp);
					lst->lenght--;
					lst->tail = NULL;
					return (lst);
					// return (lst);
				}
				else
					found = update_list2(lst, tmp);
				lst->lenght--;
				free(tmp);
			}
			tmp = tmp->prev;
		}
	}
	return (lst);
}

int			update_list2(t_dlist2 *lst, t_cmd *elem)
{
	if (!elem->next && elem->prev)
	{
		elem->c = 0;
		lst->tail = elem->prev;
		lst->tail->next = NULL;
	}
	else if (!elem->prev && elem->next)
	{
		elem->c = 0;
		lst->head = elem->next;
		lst->head->prev = NULL;;
	}
	else
	{
		elem->c = 0;
		elem->prev->next = elem->next;
		elem->next->prev = elem->prev;
	}
	return (1);
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