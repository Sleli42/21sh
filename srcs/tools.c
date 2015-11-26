/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/03 16:43:24 by lubaujar          #+#    #+#             */
/*   Updated: 2015/11/03 16:43:29 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

char	*find_env_arg(t_all *all, char *arg2find)
{
	t_node		*nav;

	nav = all->env->head_node;
	if (nav)
	{
		while (nav)
		{
			if (ft_strncmp(nav->s, arg2find, ft_strlen(arg2find)) == 0)
				return (nav->s);
			nav = nav->next;
		}
	}
	return (NULL);
}

void	update_oldpwd(t_all *all)
{
	t_node	*nav;

	nav = all->env->head_node;
	if (nav)
	{
		while (nav)
		{
			if (ft_strncmp(nav->s, "OLDPWD", 6) == 0)
			{
				ft_strdel(&nav->s);
				nav->s = ft_strjoin("OLDPWD=", all->oldpwd);
				return ;
			}
			nav = nav->next;
		}
	}
}