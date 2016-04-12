/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/04 10:17:41 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/21 16:06:19 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

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

int		symbol_in_cmd(char *s, int symbol)
{
	int	ct;

	ct = 0;
	if (s && s[ct] && symbol)
	{
		while (s && s[ct])
		{
			if (s[ct] == symbol)
				return (1);
			ct++;
		}
	}
	return (0);
}
