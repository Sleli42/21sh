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

void	add_missing_char_to_cmd(t_all *all, char *s)
{
	t_cmd	*nav;
	int		ct;

	nav = all->cmd_termcaps->tail;
	ct = ft_strlen(s) - 1;
	while (nav->c != s[ct])
		ct--;
	while (s[ct++])
	{
		write(1, &s[ct], 1);
		dlst_add_back_2(all->cmd_termcaps, dlst_cmd_new(s[ct], all->cmd_termcaps->lenght));
	}
}

int		find_maxlen_elem(t_clist *lst)
{
	t_select	*nav = lst->head;
	int			ret = 0;

	while (nav && nav->next)
	{
		if (ft_strlen(nav->arg) > ft_strlen(nav->next->arg))
			ret = ft_strlen(nav->arg);
		nav = nav->next;
	}
	return (ret);
}