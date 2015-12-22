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
	//printf("ct: %d\n", ct);
	while (s[ct++])
	{
		write(1, &s[ct], 1);
		dlst_add_back_2(all->cmd_termcaps, dlst_cmd_new(s[ct]));
	}
}

// void	add_to_cmd(t_all *all, char *s)
// {
// 	int		ct;

// 	ct = 0;
// 	//printf("allnbchar: %d\n", all->nb_char_write);
// 	// if (all->current)
// 	// 	mprintf("current: %s\n", all->current);
// 	if (!all->nb_char_write && all->current)
// 		all->nb_char_write = ft_strlen(all->current) - 1;
// 	new_line_autocomplet(all);
// 	while (s[ct])
// 	{
// 		write(1, &s[ct], 1);
// 		dlst_add_back_2(all->cmd_termcaps, dlst_cmd_new(s[ct++]));	
// 	}
// }

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

int		all_is_spaces(t_cmd *cmd)
{
	t_cmd *tmp;

	tmp = cmd;
	if (tmp)
	{
		while (tmp)
		{
			if (tmp->c == ' ' || tmp->c == '\t')
				tmp = tmp->next;
			else
				return (0);
		}
	}
	return (1);
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

int		check_history_file(char **histo)
{
	int		ret;

	ret = ft_tablen(histo);
	if (ret == 0)
		return (1);
	return (ret + 1);
}







