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

void	cut_right(t_all *all)
{
	while (all->cursor_pos > all->save_cursor_pos)
	{
		dlst_del_one2(all->cmd_termcaps, all->cursor_pos - PROMPT_LEN);
		all->cursor_pos--;
		tputs_termcap("le");
		tputs_termcap("dc");
		if (all->nb_lines > 1)
			del_char_multi_lines(all);
	}
}

void	cut_left(t_all *all)
{
	int 	count;
	int		stop;

	count = 0;
	stop = 0;
	if (all->cursor_pos == 1)
		stop += 1;
	while (all->cursor_pos < all->save_cursor_pos)
	{
		all->cursor_pos++;
		count++;
		tputs_termcap("nd");
	}
	while (count > 0)
	{
		dlst_del_one2(all->cmd_termcaps, (all->cursor_pos - PROMPT_LEN) + 1);
		tputs_termcap("dc");
		tputs_termcap("le");
		count--;
		all->cursor_pos--;
		if (all->nb_lines > 1)
			del_char_multi_lines(all);
	}
	if (stop)
	{
		dlst_del_one2(all->cmd_termcaps, 1);
		tputs_termcap("dc");
	}
}