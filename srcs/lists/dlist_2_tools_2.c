/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_2_tools_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 15:55:21 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/21 16:04:45 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

int			dlst_insert_cmd_extended(t_all *all, t_dlist2 *lst, \
										t_cmd *tmp, t_cmd *node)
{
	if (tmp->next == NULL)
	{
		lst = dlst_add_back_2(lst, node);
		all->globing.esc_mem ? NULL
			: swap_elems_cmd(lst->tail, lst->tail->prev);
		return (1);
	}
	else if (tmp->prev == NULL)
	{
		lst = dlist_add_front_2(lst, node);
		return (1);
	}
	return (0);
}

void		del_dlist2(t_dlist2 *lst)
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
