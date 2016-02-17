/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 13:50:51 by lubaujar          #+#    #+#             */
/*   Updated: 2016/01/07 13:50:53 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	cut_delete_char(t_all *all, int count)
{
	while (count > 0)
	{
		dlst_del_one2(all->cmd_termcaps, (CURSOR - PROMPT_LEN) + 1);
		tputs_termcap("dc");
		tputs_termcap("le");
		count--;
		CURSOR--;
		if (all->nb_lines > 1)
			del_char_multi_lines(all);
	}
}

void	cut_right(t_all *all)
{
	while (CURSOR > all->save_cursor_pos)
	{
		dlst_del_one2(all->cmd_termcaps, CURSOR - PROMPT_LEN);
		CURSOR--;
		tputs_termcap("le");
		tputs_termcap("dc");
		if (all->nb_lines > 1)
			del_char_multi_lines(all);
	}
}

void	cut_left(t_all *all)
{
	int		count;

	count = 0;
	all->stop = 0;
	if (CURSOR == 1)
		all->stop += 1;
	while (CURSOR < all->save_cursor_pos)
	{
		CURSOR++;
		count++;
		tputs_termcap("nd");
	}
	cut_delete_char(all, count);
	if (all->stop)
	{
		dlst_del_one2(all->cmd_termcaps, 1);
		tputs_termcap("dc");
	}
}
