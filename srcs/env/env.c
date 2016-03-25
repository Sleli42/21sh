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

char	**realloc_env_array(t_dlist *env)
{
	t_node	*nav;
	char	**ret;
	int		ct;

	nav = env->head;
	ct = 0;
	if (!(ret = (char**)malloc(sizeof(char *) * env->lenght + 1)))
		error("MALLOC");
	if (nav && ret)
	{
		while (nav)
		{
			ret[ct] = ft_strdup(nav->s);
			nav = nav->next;
			ct++;
		}
		ret[ct] = NULL;
	}
	return (ret);
}

void	update_env(t_all *all, char *s)
{
	t_node	*nav;

	nav = all->env->head;
	if (nav)
	{
		while (nav)
		{
			if (!ft_strncmp(nav->s, all->tmp_var_env, \
				ft_strlen(all->tmp_var_env)))
			{
				ft_strdel(&nav->s);
				nav->s = ft_strdup(s);
				return ;
			}
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
}
