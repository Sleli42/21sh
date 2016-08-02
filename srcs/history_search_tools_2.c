/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_search_tools_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/27 03:33:12 by lubaujar          #+#    #+#             */
/*   Updated: 2016/07/27 03:33:13 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

void	refresh_line(t_all *all)
{
	int		save;

	get_cursor_row(all);
	all->lines2del = count_lines_2del(all);
	save = 1;
	tputs_termcap("up");
	tputs_termcap("do");
	if (save < all->lines2del)
	{
		while (save++ < all->lines2del)
		{
			tputs_termcap("ce");
			tputs_termcap("cb");
			tputs_termcap("up");
		}
	}
	else
	{
		tputs_termcap("cb");
		tputs_termcap("ce");
	}
}

char	*skip_index(char *s)
{
	if (!s)
		return (NULL);
	while (s && *s)
	{
		if (*s == ':')
		{
			s++;
			break ;
		}
		s++;
	}
	return (s);
}
