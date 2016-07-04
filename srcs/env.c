/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/26 02:18:58 by lubaujar          #+#    #+#             */
/*   Updated: 2016/06/14 17:48:14 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

int					check_params(char **params, t_env_info *inf)
{
	int				i;

	i = 0;
	inf->unless = 1;
	while (params[i][0] == '-')
	{
		if (!ft_strcmp(params[i], "-i"))
		{
			inf->unless = -1;
			params++;
			if (!params[i])
				return (0);
		}
		else
		{
			ft_putendl("env illegal option. usage: env [-i] [utility [args]]");
			return (1);
		}
	}
	if ((i = add_spe_env(params, inf)) == -1)
	{
		ft_putendl("malloc error");
		return (1);
	}
	return (0);
}

int					env_bin(t_all *all, t_env_info *inf)
{
	if (inf->unless == -1)
	{
		all->env_exec = inf->env_spe;
		exec_right_binary(all, ft_strsplit(inf->bin, ' '));
		return (1);
	}
	if (inf->env_spe)
		set_env_exec(inf, all);
	exec_right_binary(all, ft_strsplit(inf->bin, ' '));
	return (1);
}

int					env_exec(t_all *all, char **params)
{
	t_env_info		inf;

	init_inf(&inf);
	if (check_params(params, &inf))
		return (1);
	all->path_mod = inf.bin_path;
	if (inf.exec)
		return (env_bin(all, &inf));
	if (inf.unless != -1 && inf.env_spe)
	{
		set_env_exec(&inf, all);
		return (0);
	}
	if (inf.unless == -1)
	{
		ft_printtab(inf.env_spe);
		return (1);
	}
	return (0);
}

void				env_display(t_all *all, char *cmd)
{
	char			**tmp;

	if (ft_tablen((tmp = ft_strsplit(cmd, ' '))) > 1)
		if (!check_env_error(tmp) || env_exec(all, &tmp[1]))
			return (del_array(&tmp));
	ft_printtab(all->env_exec);
	tmp && *tmp ? del_array(&tmp) : NULL;
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

void				env_modify(t_all *all, char *cmd)
{
	char			*tmp;
	char			*tmp2;

	(void)all;
	tmp2 = ft_strnew(count_var_len(cmd) + 1);
	tmp = ft_epur_str(ft_strchr(cmd, '=') + 1);
	ft_memcpy(tmp2, cmd, count_var_len(cmd) + 1);
	ft_strdel(&cmd);
	cmd = ft_strjoin(tmp2, tmp);
	ft_strdel(&tmp);
	ft_strdel(&tmp2);
}
