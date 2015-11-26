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

void	env_display(t_all *all, char *cmd)
{
	t_node	*nav;

	(void)cmd;
	nav = all->env->head_node;
	if (nav)
	{
		while (nav)
		{
			ft_putendl(nav->s);
			nav = nav->next;
		}
	}
}

void	env_set(t_all *all, char *cmd)
{
	dlst_add_back((t_dlist *)all->env, (t_node *)dlst_node_new(cmd + 8));
}

void	env_unset(t_all *all, char *cmd)
{
	dlst_del_one(all->env, (cmd + 10));
}
