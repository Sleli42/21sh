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
	//printf("%d\n", all->cursor_pos);
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
		}
		(all->current_key == K_BACKSPACE)
			? tputs_termcap("le") : NULL;
		tputs_termcap("dc");
		if (all->current_key == K_BACKSPACE)
			all->cursor_pos--;
		tputs_termcap("ed");
	}
}