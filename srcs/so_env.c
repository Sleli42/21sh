/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 14:39:15 by lubaujar          #+#    #+#             */
/*   Updated: 2016/06/28 14:39:16 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

void	set_env_exec(t_env_info *inf, t_all *all)
{
	if (inf->unless > 0)
		all->env_exec = ft_tabjoin(all->dupenv, inf->env_spe);
	else
		all->env_exec = inf->env_spe;
}

int		add_spe_env(char **params, t_env_info *inf)
{
	int 			i;

	i = 0;
	inf->env_spe = NULL;
	if ((inf->env_spe = \
		(char **)malloc(sizeof(char *) * (ft_tablen(params) + 1))) == NULL)
		return (-1);
	while (params[i])
	{
		if (!ft_strchr(params[i], '='))
		{
			inf->env_spe[i] = NULL;
			inf->bin = params[i];
			return ((inf->exec = 1));
		}
		inf->env_spe[i] = ft_strdup(params[i]);
		i++;
	}
	inf->env_spe[i] = NULL;
	return ((inf->exec = 0));
}

int		check_params(char **params, t_env_info *inf)
{
	int				i;

	i = 0;
	inf->unless = 1;
	if (!ft_strcmp(params[i], "-i"))
	{
		inf->unless = -1;
		params++;
		if (!params[i])
			return (0);
	}
	if ((i = add_spe_env(params, inf)) == -1)
	{
		ft_putendl("malloc error");
		return (1);
	}
	return (0);
}

int		env_bin(t_all *all, t_env_info *inf)
{
	if (inf->unless == -1)
	{
		all->env_exec = inf->env_spe;
		ft_printtab(all->env_exec);
		exec_right_binary(all, ft_strsplit(inf->bin, ' '));
		return (1);
	}
	if (inf->env_spe)
		set_env_exec(inf, all);
	exec_right_binary(all, ft_strsplit(inf->bin, ' '));
	return (1);
}

void	update_env_info(t_all *all, t_env_info inf)
{
	int				i;

	i = 0;
	while (inf.env_spe[i])
	{
		if (var_already_exist(all, inf.env_spe[i]))
			update_env(all, inf.env_spe[i]);
		else
			dlst_add_back((t_dlist *)all->env, (t_node *)\
							dlst_node_new(inf.env_spe[i], all->env->lenght));
		i++;
	}
}
