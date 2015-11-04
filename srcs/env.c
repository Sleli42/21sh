/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/26 02:18:58 by lubaujar          #+#    #+#             */
/*   Updated: 2015/08/27 07:36:48 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	env_display(t_all *all)
{
	t_node	*nav;

	nav = all->env->head;
	if (nav)
	{
		while (nav)
		{
			ft_putendl(nav->s);
			nav = nav->next;
		}
	}
}

// void	env_set(t_all *all)
// {
// 	dlst_add_back(all->env, dlst_new(all->cmd + 8));
// }

// void	env_unset(t_all *all)
// {
// 	dlst_del_one(all->env, (all->cmd + 10));
// }
