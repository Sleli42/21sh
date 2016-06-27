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

void				set_env_exec(t_env_info *inf, t_all *all)
{
	if (inf->unless > 0)
		all->env_exec = ft_tabjoin(all->dupenv, inf->env_spe);
	else
	{
		printf("IN NO ENV\n");
		all->env_exec = inf->env_spe;
	}
}

int					add_spe_env(char **params, t_env_info *inf)
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

int					check_params(char **params, t_env_info *inf)
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

int					env_bin(t_all *all, t_env_info *inf)
{
	if (inf->unless == -1)
	{
		printf("--->94?\n");
		all->env_exec = inf->env_spe;
		ft_printtab(all->env_exec);
		// exit(0);
		exec_right_binary(all, ft_strsplit(inf->bin, ' '));
		return (1);
	}
	if (inf->env_spe)
		set_env_exec(inf, all);
	exec_right_binary(all, ft_strsplit(inf->bin, ' '));
	return (1);
}

void				update_env_info(t_all *all, t_env_info inf)
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

int					env_exec(t_all *all, char **params)
{
	t_env_info		inf;

	init_inf(&inf);
	if (check_params(params, &inf))
		return (1);
	if (inf.exec)
		return (env_bin(all, &inf));
	if (inf.unless != -1 && inf.env_spe)
	{
		set_env_exec(&inf, all);
		return (0);
	}
	if (inf.unless == -1 && inf.env_spe)
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
	ft_printtab(all->env_exec ? all->env_exec : all->dupenv);
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

char	**check_format(char *cmd)
{
	char		**ret;

	if (!cmd || !*cmd)
		return NULL;
	ret = NULL;
	if (!(ret = ft_strsplit(cmd, ' ')))
		return (NULL);
	if (ft_tablen(ret) != 2)
	{
		del_array(&ret);
		ft_putendl("Bad format: set env [var] [content]");
		return (NULL);
	}
	else
		return (ret);
}

void	env_set(t_all *all, char *cmd)
{
	char		*tmp;
	char		*var;
	char		**foo;

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

	(void)all;
	tmp2 = ft_strnew(count_var_len(cmd) + 1);
	tmp = ft_epur_str(ft_strchr(cmd, '=') + 1);
	ft_memcpy(tmp2, cmd, count_var_len(cmd) + 1);
	ft_strdel(&cmd);
	cmd = ft_strjoin(tmp2, tmp);
	ft_strdel(&tmp);
	ft_strdel(&tmp2);
}

