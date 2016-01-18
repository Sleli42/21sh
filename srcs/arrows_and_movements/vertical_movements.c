/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_movements.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 12:24:29 by lubaujar          #+#    #+#             */
/*   Updated: 2016/01/18 12:24:30 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	goto_up_line(t_all *all)
{
	if (K_CTRL_UP && all->curr_line > 1)
	{
		//write(1, "here\n", 5);
		tputs_termcap("up");
		all->cursor_pos /= 2;
		all->curr_line -= 1;
	}
}

void	goto_down_line(t_all *all)
{
	int		ct;

	ct = 0;
	if (K_CTRL_DOWN && all->curr_line < all->nb_lines)
	{
		ct = (all->ws.ws_col * all->curr_line) + 1;
		all->cursor_pos *= 2;
		tputs_termcap("do");
		all->curr_line += 1;
		while (ct++ < all->cursor_pos + 2)
		 	tputs_termcap("nd");
		// if (all->curr_line == all->nb_lines
		// 	&& all->cursor_pos > (int)all->cmd_termcaps->lenght)
		// 	all->cursor_pos =  (int)all->cmd_termcaps->lenght;
		// else
		// 	all->cursor_pos *= 2;
	}
}



/*	=============================================================

0123456789...
$: .........|	0
............|	1
........	|	2
			|	3
			|	4
			|	5
			|	6
			|	7
			|	8
			|	9





================================================================= */