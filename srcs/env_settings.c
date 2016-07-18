/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_settings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/14 17:32:23 by skhatir           #+#    #+#             */
/*   Updated: 2016/06/14 17:48:49 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

int					add_spe_env(char **params, t_env_info *inf)
{
	int				i;

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
		if (!ft_strncmp("PATH=", inf->env_spe[i], 5))
			inf->bin_path = inf->env_spe[i];
		i++;
	}
	inf->env_spe[i] = NULL;
	return ((inf->exec = 0));
}

void				set_env_exec(t_env_info *inf, t_all *all)
{
	if (inf->unless > 0)
		all->env_exec = ft_tabjoin(all->dupenv, inf->env_spe);
	else
		all->env_exec = inf->env_spe;
}

void				env_set(t_all *all, char *cmd)
{
	char			*tmp;
	char			*var;
	char			**foo;

	foo = NULL;
	if (!(foo = check_format((cmd + 8))))
		return ;
	tmp = NULL;
	tmp = ft_strjoin(*foo, "=");
	var = ft_strjoin(tmp, foo[1]);
	if (var_already_exist(all, var))
		update_env(all, var);
	else
		dlst_add_back((t_dlist *)all->env, (t_node *)\
										dlst_node_new(var, all->env->lenght));
	del_array(&foo);
	(all->dupenv) ? del_array(&all->dupenv) : NULL;
	all->dupenv = realloc_env_array(all->env);
}

void				env_unset(t_all *all, char *cmd)
{
	char			**tmp;
	int				ct;

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
