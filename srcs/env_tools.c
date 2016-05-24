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
	if (nav && arg2find)
	{
		while (nav)
		{
			if (ft_strncmp(nav->s, arg2find, ft_strlen(arg2find)) == 0)
				return (nav->s);
			nav = nav->next;
		}
	}
	return ("\0");
}

char	**ft_dupenv(t_dlist *env)
{
	t_node		*tmp;
	char		**dup;
	int			i;

	tmp = env->head;
	dup = NULL;
	i = 0;
	if (tmp)
	{
		if (!(dup = (char **)malloc(sizeof(char *) * (int)env->lenght + 1)))
			return (NULL);
		while (tmp)
		{
			dup[i] = ft_strdup(tmp->s);
			tmp = tmp->next;
			i++;
		}
		dup[i] = NULL;
		return (dup);
	}
	return (NULL);
}

int		count_var_len(char *var)
{
	int		ret;
	int		ct;

	ret = 0;
	ct = 0;
	if (var)
	{
		while (var && var[ct] != '=')
		{
			ret++;
			ct++;
		}
	}
	return (ret);
}

int		check_match_env(t_all *all, char *s)
{
	t_node	*nav;

	nav = all->env->head;
	if (nav && s && *s)
	{
		while (nav)
		{
			if (!ft_strncmp(nav->s, s, ft_strlen(s)))
				return (1);
			nav = nav->next;
		}
	}
	return (0);
}

int		var_already_exist(t_all *all, char *var)
{
	char	*tmp_var;
	int		count;

	tmp_var = NULL;
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
	return (check_match_env(all, tmp_var));
}
