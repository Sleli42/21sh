/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/04 10:17:41 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/21 16:06:19 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

char	*find_env_arg(t_all *all, char *arg2find)
{
	t_node		*nav;

	nav = all->env->head;
	if (nav)
	{
		while (nav)
		{
			if (!ft_strncmp(nav->s, arg2find, ft_strlen(arg2find)))
				return (nav->s);
			nav = nav->next;
		}
	}
	return (ft_strjoin(arg2find, " "));
}

char	**ft_dupenv(char **env)
{
	char	**dup;
	int		i;

	i = -1;
	if (!(dup = (char **)malloc(sizeof(char *) * ft_tablen(env) + 1)))
		return (NULL);
	while (++i < (int)ft_tablen(env))
		dup[i] = ft_strdup(env[i]);
	dup[++i] = NULL;
	return (dup);
}

int		count_var_len(char *var)
{
	int		ret;

	ret = 0;
	if (var)
	{
		while (var && *var != '=')
		{
			ret++;
			var++;
		}
	}
	return (ret);
}

int		cmp_env_var(t_all *all, char *s)
{
	int		ct;

	ct = 0;
	if (s)
	{
		while (all->dupenv && all->dupenv[ct])
		{
			if (!ft_strncmp(all->dupenv[ct], s, ft_strlen(s)))
				return (1);
			ct++;
		}
	}
	return (0);
}

int		var_already_exist(t_all *all, char *var)
{
	char	*tmp_var;
	int		count;

	count = count_var_len(var);
	tmp_var = ft_strnew(count + 1);
	count = 0;
	while (var)
	{
		if (var[count] == '=')
			break ;
		tmp_var[count] = var[count];
		count++;
	}
	tmp_var[count] = 0;
	all->tmp_var_env = tmp_var;
	return (cmp_env_var(all, tmp_var));
}
