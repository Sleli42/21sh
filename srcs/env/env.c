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

void	multi_env_set(t_all *all, char **array)
{
	int		ct;

	ct = 0;
	while (array[ct])
	{
		if (good_env_formatting(array[ct]))
		{
			// printf("s: %s\n", array[ct]);
			if (var_already_exist(all, array[ct]))
				update_env(all, array[ct]);
			else
				dlst_add_back((t_dlist *)all->env, (t_node *)
					dlst_node_new(array[ct], all->env->lenght));
		}
		ct++;
	}
}

void	env_set(t_all *all, char *cmd)
{
	char		**tmp;

	tmp = ft_strsplit(cmd + 8, ' ');
	if (ft_tablen(tmp) > 1)
		multi_env_set(all, tmp);
	else
	{
		if (var_already_exist(all, cmd + 8))
			update_env(all, cmd + 8);
		else
			dlst_add_back((t_dlist *)all->env, (t_node *)
				dlst_node_new(cmd + 8, all->env->lenght));
	}
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
	ft_putstr("HERE alrod que je ne suis pas du tout sensé aller ici \n\n");
	if (var_already_exist(all, cmd))
		update_env(all, cmd);
	else
		dlst_add_back((t_dlist *)all->env, (t_node *)
			dlst_node_new(cmd, all->env->lenght));
	all->dupenv = realloc_env_array(all->env);
}
