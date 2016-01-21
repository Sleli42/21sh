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

static int	count_char_to_shift(t_all *all, int start_pos)
{
	int		ret;

	ret = 0;
	while (start_pos++ < all->cursor_pos)
		ret++;
	ret += (all->curr_line == 1) ? 2 : 0;
	return (ret);
}

void	goto_up_line(t_all *all)
{
	int		ct;

	ct = 0;
	if (all->current_key == K_CTRL_UP && all->curr_line > 1)
	{
		ct = count_char_to_shift(all, (all->curr_line - 1) * all->ws.ws_col - 2);
		all->curr_line -= 1;
		all->cursor_pos = (all->curr_line == 1) ? (ct - 2)
			: ((all->ws.ws_col * (all->curr_line - 1)) - 2 + ct);
		if (all->cursor_pos < 0)
		{
			while (all->cursor_pos++ < 0)
				tputs_termcap("nd");
			tputs_termcap("nd");
		}
		tputs_termcap("up");
	}
}

void	goto_down_line(t_all *all)
{
	int		ct;

	ct = 0;
	if (all->current_key == K_CTRL_DOWN && all->curr_line < all->nb_lines)
	{
		ct = (all->curr_line == 1) ? count_char_to_shift(all, 0)
			: count_char_to_shift(all, (all->curr_line - 1) * all->ws.ws_col - 2);
		all->cursor_pos = (all->ws.ws_col * (all->curr_line)) - 2 + ct;
		all->curr_line += 1;
		tputs_termcap("do");
		if (all->cursor_pos > (int)ft_strlen(all->cmd))
		{
			all->cursor_pos = (all->ws.ws_col * (all->curr_line - 1) - 3);
			while (all->cursor_pos++ < (int)ft_strlen(all->cmd))
				tputs_termcap("nd");
		}
		else
		{
			while (ct-- > 0)
		 		tputs_termcap("nd");
		}
	}
}

/*	=============================================================

   123456789 . . .
0123456789 . . .
$: ......9..|	0
  <------> startPos + decalage
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