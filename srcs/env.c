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
	char	**tmp;
	int		skip;

	tmp = ft_strsplit(cmd, ' ');
	skip = (len_array(tmp) > 1 && !ft_strcmp(tmp[1], "-i")) ? 7 : 4;
	if (!check_env_error(tmp) || (!cmd[skip] && skip == 7) || cmd[skip] < 0)
		return ;
	if (cmd && len_array(tmp) > 1)
		exec_right_binary(all, ft_strsplit(cmd + skip, ' '));
	else
	{
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
	del_array(&tmp);
}

void	multi_env_set(t_all *all, char **array)
{
	int		ct;

	ct = 0;
	while (array[ct])
	{
		if (good_env_formatting(array[ct]))
		{
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
	del_array(&tmp);
	(all->dupenv) ? del_array(&all->dupenv) : NULL;
	all->dupenv = realloc_env_array(all->env);
}

void	env_unset(t_all *all, char *cmd)
{
	char		**tmp;
	int			ct;

	tmp = ft_strsplit(cmd + 10, ' ');
	ct = 0;
	if (ft_tablen(tmp) > 1)
	{
		while (tmp[ct])
		{
			if (var_already_exist(all, tmp[ct]))
				dlst_del_one(all->env, tmp[ct]);
			ct++;
		}
	}
	else
		dlst_del_one(all->env, (cmd + 10));
	del_array(&tmp);
	(all->dupenv) ? del_array(&all->dupenv) : NULL;
	all->dupenv = realloc_env_array(all->env);
}

void	env_modify(t_all *all, char *cmd)
{
	char	*tmp;
	char	*tmp2;

	tmp2 = ft_strnew(count_var_len(cmd) + 1);
	tmp = ft_epur_str(ft_strchr(cmd, '=') + 1);
	ft_memcpy(tmp2, cmd, count_var_len(cmd) + 1);
	ft_strdel(&cmd);
	cmd = ft_strjoin(tmp2, tmp);
	ft_strdel(&tmp);
	ft_strdel(&tmp2);
	if (var_already_exist(all, cmd))
		update_env(all, cmd);
	else
		dlst_add_back((t_dlist *)all->env, (t_node *)
			dlst_node_new(cmd, all->env->lenght));
	all->dupenv = realloc_env_array(all->env);
}
