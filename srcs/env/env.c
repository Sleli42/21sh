/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/26 02:18:58 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/21 16:06:08 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

void	env_display(t_all *all, char *cmd)
{
	t_node	*nav;

	(void)cmd;
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

void	env_set(t_all *all, char *cmd)
{
	if (var_already_exist(all, cmd + 8))
		update_env(all, cmd + 8);
	else
		dlst_add_back((t_dlist *)all->env, (t_node *)dlst_node_new(cmd + 8,
			all->env->lenght));
	(all->dupenv) ? del_array(&all->dupenv) : NULL;
	all->dupenv = realloc_env_array(all->env);
}

void	env_unset(t_all *all, char *cmd)
{
	dlst_del_one(all->env, (cmd + 10));
	(all->dupenv) ? del_array(&all->dupenv) : NULL;
	all->dupenv = realloc_env_array(all->env);
}

void	env_modify(t_all *all, char *cmd)
{
	if (var_already_exist(all, cmd))
		update_env(all, cmd);
	else
		dlst_add_back((t_dlist *)all->env, (t_node *)
			dlst_node_new(cmd, all->env->lenght));
	all->dupenv = realloc_env_array(all->env);
}
