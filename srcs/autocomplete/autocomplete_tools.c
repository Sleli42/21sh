/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 00:55:58 by lubaujar          #+#    #+#             */
/*   Updated: 2016/02/01 00:55:59 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int		find_maxlen_elem(t_clist *lst)
{
	t_select	*nav = lst->head;
	int			ret = 0;

	ret = ft_strlen(nav->arg);
	while (nav->next)
	{
		if (ft_strlen(nav->arg) > (size_t)ret)
			ret = ft_strlen(nav->arg);
		nav = nav->next;
	}
	return (ret);
}

int		define_nb_files_by_row(t_all *all, t_clist *lst)
{
	int		ret;

	init_windows_size(all);
	all->maxlen_arg = find_maxlen_elem(lst);
	ret = 0;
	while (LINE_LEN > (all->maxlen_arg + 2))
	{
		LINE_LEN -= (all->maxlen_arg + 2);
		ret++;
	}
	return (ret);
}

int		no_spaces(t_cmd *lst)
{
	t_cmd	*tmp = lst;

	if (tmp->c == '.' && tmp->next->c == '/')
		return (0);
	while (tmp)
	{
		if (tmp->c == ' ')
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

void	cut_cmd_equ(t_all *all)
{
	int		ct;
	int		tmp;

	ct = 0;
	tmp = (CURSOR - PROMPT_LEN) - 1;
	if (!(all->equ2find = (char *)malloc(sizeof(char *))))
		error("MALLOC");
	if (all->already_open && all->cmd[tmp] != '/')
		while (all->cmd[tmp] && all->cmd[tmp] != '/')
			tmp--;
	else
		while (all->cmd[tmp] && all->cmd[tmp] != ' ')
			tmp--;
	tmp += 1;
	while (all->cmd[tmp] && all->cmd[tmp] != ' ')
		all->equ2find[ct++] = all->cmd[tmp++];
	all->equ2find[ct] = '\0';
}