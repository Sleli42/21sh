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

	nav = all->env->head;
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


int		find_maxlen_elem(t_clist *lst)
{
	t_select	*nav = lst->head;
	int			ret = 0;

	ret = ft_strlen(nav->arg);
	while (nav->next)
	{
		//ret = ft_strlen(nav->arg);
		if (ft_strlen(nav->arg) > (size_t)ret)
			ret = ft_strlen(nav->arg);
		nav = nav->next;
	}
	return (ret);
}

char	goto_elem(t_cmd *cmd, int pos)
{
	t_cmd	*tmp = cmd;
	int		ct = 1;

	while (ct++ < pos)
		tmp = tmp->next;
	//printf("-> |%c|\n", tmp->c);
	return (tmp->c);
}







