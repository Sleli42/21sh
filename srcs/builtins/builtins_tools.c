/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/04 10:21:09 by lubaujar          #+#    #+#             */
/*   Updated: 2016/01/04 10:21:10 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	update_oldpwd(t_all *all)
{
	t_node	*nav;

	nav = all->env->head;
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