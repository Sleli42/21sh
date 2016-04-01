/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/04 10:21:09 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/21 16:09:08 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

static t_node	*add_pwd(void)
{
	t_node		*pwd;

	if ((pwd = (t_node *)malloc(sizeof(t_node))) != NULL)
	{
		pwd->s = ft_strdup("PWD=/");
		pwd->index = 255;
		pwd->next = NULL;
		pwd->prev = NULL;
		return (pwd);
	}
	ft_putendl("add_pwd failed");
	return (NULL);
}

void			update_pwd(t_all *all)
{
	t_node		*nav;
	char		buf[512];

	nav = all->env->head;
	if (nav)
	{
		while (nav)
		{
			if (ft_strncmp(nav->s, "PWD", 3) == 0)
			{
				ft_strdel(&nav->s);
				nav->s = ft_strjoin("PWD=", getcwd(buf, 512));
				return ;
			}
			if (!nav->next)
			{
				if (!(nav->next = add_pwd()))
					break ;
				nav->next->prev = nav;
				nav->next->index = nav->index + 1;
			}
			nav = nav->next;
		}
	}
}

static t_node	*add_oldpwd(void)
{
	t_node		*opwd;

	if ((opwd = (t_node *)malloc(sizeof(t_node))) != NULL)
	{
		opwd->s = ft_strdup("OLDPWD=/");
		opwd->index = 255;
		opwd->next = NULL;
		opwd->prev = NULL;
		return (opwd);
	}
	ft_putendl("add_oldpwd failed");
	return (NULL);
}

void			update_oldpwd(t_all *all)
{
	t_node		*nav;

	nav = all->env->head;
	ft_putstr("HERE\n");
	if (nav)
	{
		while (nav)
		{
			if (ft_strncmp(nav->s, "OLDPWD", 6) == 0)
			{
				ft_strdel(&nav->s);
				nav->s = ft_strjoin("OLDPWD=", all->oldpwd);
				update_pwd(all);
				return ;
			}
			if (!nav->next)
			{
				if (!(nav->next = add_oldpwd()))
					break ;
				nav->next->prev = nav;
				nav->next->index = nav->index + 1;
			}
			nav = nav->next;
		}
	}
	ft_putstr("HERE\n");
}
