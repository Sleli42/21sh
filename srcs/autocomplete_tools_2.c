/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete_tools_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/27 11:30:27 by lubaujar          #+#    #+#             */
/*   Updated: 2016/06/27 11:30:29 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

int		find_maxlen_elem(t_clist *lst)
{
	t_select	*nav;
	int			ret;

	nav = lst->head;
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
	t_cmd	*tmp;

	tmp = lst;
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

void	add_spaces(t_all *all, int tmp_len, int ct)
{
	if (tmp_len < all->maxlen_arg \
				&& ct != all->files_by_row - 1)
	{
		write(1, " ", 1);
		while (tmp_len++ < all->maxlen_arg)
			write(1, " ", 1);
	}
}
