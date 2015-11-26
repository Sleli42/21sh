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

t_cmd			*create_cmd_dlst(void)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (new != NULL)
	{
		new->c = 0;
		new->pos = 0;
		new->lenght = 0;
		new->next = NULL;
		new->prev = NULL;
	}
}

t_cmd			*dlst_cmd_new(char c)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (new)
	{
		new->c = c;
		new->pos++;
		new->next = NULL;
		new->prev = NULL;
	}
}

t_cmd			*dlst_add_back_2(t_cmd *lst, t_cmd *node)
{
	if (lst && node)
	{
		if (lst == NULL)
			lst = node;
		else
		{
			while (lst->next)
				lst = lst->next;
			lst = node;
		}
	}
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