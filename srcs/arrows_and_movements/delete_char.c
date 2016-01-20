/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/03 17:57:35 by lubaujar          #+#    #+#             */
/*   Updated: 2016/01/03 17:57:36 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	del_char(t_all *all)
{
	if (all->already_in_history)
		realloc_termcaps_cmd(all, all->cmd);
	tputs_termcap("dm");
	if (all->cmd_termcaps->lenght > 0 && all->cursor_pos > 1)
	{
		if ((size_t)all->cursor_pos <= all->cmd_termcaps->lenght + 1)
		{
			(all->current_key != K_BACKSPACE)
			 ? dlst_del_one2(all->cmd_termcaps, all->cursor_pos)
				: dlst_del_one2(all->cmd_termcaps, all->cursor_pos - 1);
			if (all->nb_lines > 1)
			{
				int	ct = all->curr_line;
				tputs_termcap("sc");
				while (all->nb_lines - ct > 0)
				{
					// write(1, "turn\n", 5);
					create_cmd(all);
					if ((int)ft_strlen(all->cmd) < ((all->nb_lines - 1) * all->ws.ws_col) - 3)
						all->nb_lines--;
					shift_first_char(all, ct++);
				}
				tputs_termcap("rc");
			}
		}
		(all->current_key == K_BACKSPACE)
			? tputs_termcap("le") : NULL;
		tputs_termcap("dc");
		if (all->current_key == K_BACKSPACE)
			all->cursor_pos--;
	}
	tputs_termcap("ed");
}


/* ===================================================


	a faire: shift multiligne
	. . .

===================================================== */