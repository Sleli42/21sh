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

static int	count_char_to_shift(t_all *all)
{
	int		first_pos;
	int		ret;

	//printf("currLine : %d\n", all->curr_line);
	first_pos = (all->curr_line == 1) ? 0 : 
		(all->ws.ws_col * all->curr_line) + 1;
	ret = 0;
	//printf("pos curs : %d\n", all->cursor_pos);
	while (first_pos++ <= all->cursor_pos)
		ret++;
//	printf("ret: %d\n", ret);
	return (ret);
}

void	goto_up_line(t_all *all)
{
	int		ct;

	ct = 0;
	if (K_CTRL_UP && all->curr_line > 1)
	{
		//write(1, "here\n", 5);
		tputs_termcap("up");
		all->curr_line -= 1;
		ct = count_char_to_shift(all);
		// printf("pos curs : %d\n", all->cursor_pos);
		//printf("currLine : %d\n", all->curr_line);
		//printf("cursor: %d\n", all->cursor_pos);
		all->cursor_pos = (all->curr_line == 1) ? 
			(0 + ct) : ((all->ws.ws_col * all->curr_line) + ct);
		//printf("cursor: %d\n", all->cursor_pos);
	}
}

void	goto_down_line(t_all *all)
{
	int		ct;

	ct = 0;
	if (K_CTRL_DOWN && all->curr_line < all->nb_lines)
	{
		ct = count_char_to_shift(all);
		// ct = (all->ws.ws_col * all->curr_line) + 1;
		// all->cursor_pos *= 2;
		// printf("pos curs : %d\n", all->cursor_pos);
		// printf("currLine : %d\n", all->curr_line);

	//	printf("pos2go : %d\n", (all->curr_line * all->ws.ws_col));
		// printf("nb_move: %d\n", all->cursor_pos - ct);
		tputs_termcap("do");
	//	printf("cursor: %d\n", all->cursor_pos);
		all->cursor_pos = (all->ws.ws_col * all->curr_line) + 1 + ct;
	//	printf("cursor: %d\n", all->cursor_pos);
		all->curr_line += 1;
	//	printf("ct: %d\n", ct);
		while (ct-- >= 0)
		 	tputs_termcap("nd");
		// if (all->curr_line == all->nb_lines
		// 	&& all->cursor_pos > (int)all->cmd_termcaps->lenght)
		// 	all->cursor_pos =  (int)all->cmd_termcaps->lenght;
		// else
		// 	all->cursor_pos *= 2;
	}
}



/*	=============================================================

   123456789 . . .
0123456789 . . .
$: ......9..|	0
  <------> FirstPos + decalage
  					+ 6 + 3 (prompt) 
.........21..|	1
.........33..|	2					cursPos : 7 -> 19 -> 31;
.......		|	3					TermPos : 9 -> 21 -> 33;
			|	4					1st ?   : 21;
			|	5						==> : 9 * 2 = 18;
			|	6						==> : 18 + 3 = 21;
			|	7					----------------------
			|	8						==> : termPos * 2 = res;
			|	9						==> : res + lenPrompt = res2find;
									----------------------
										==> : cursPos 



================================================================= */