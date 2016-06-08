/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_movements.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 12:24:29 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/21 16:11:05 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

static int	count_char_to_shift(t_all *all, int start_pos)
{
	int		ret;

	ret = 0;
	while (start_pos++ < CURSOR)
		ret++;
	return (ret);
}

// int			count_char_skip(t_all *all, int start, int end)
// {

// }

void		goto_up_line(t_all *all)
{
	int		ct;

	ct = 0;
	if (all->current_key == K_CTRL_UP && all->curr_line > 1)
	{
		ct = count_char_to_shift(all, ((all->curr_line - 1) * LINE_LEN));
		all->curr_line -= 1;
		CURSOR = (all->curr_line == 1) ? (ct)
			: ((LINE_LEN * (all->curr_line - 1)) + ct);
		tputs_termcap("up");
		if (CURSOR < PROMPT_LEN)
		{
			while (CURSOR++ < PROMPT_LEN - 1)
				tputs_termcap("nd");
			tputs_termcap("nd");
		}
	}
	else
		tputs_termcap("bl");
}

void		goto_down_line(t_all *all)
{
	int		ct;

	ct = 0;
	// printf("CURSOR = %d\n", CURSOR);
	if (all->current_key == K_CTRL_DOWN && all->curr_line < all->nb_lines)
	{
		ct = (all->curr_line == 1) ? count_char_to_shift(all, 0)
			: count_char_to_shift(all, ((all->curr_line - 1) * LINE_LEN));
		// printf("countchar shift: %d\n", ct);
		// ct = count_char_skip(all, 0, ??);
		// printf("countchar skip: %d\n", ct);
		CURSOR = (LINE_LEN * (all->curr_line)) + ct;
		all->curr_line += 1;
		tputs_termcap("do");
		// printf("line * len = %d\n", LINE_LEN * all->curr_line);
		// // printf("CURSOR: %d\n", CURSOR);
		// if (all->curr_line == all->nb_lines)
		// {
		// 	if ()
		// }
		if (CURSOR - PROMPT_LEN > (int)ft_strlen(all->cmd))
		{
			// ft_putstr("YIIIIH\n");
			ct = (LINE_LEN * (all->curr_line - 1));
			while (ct++ < (int)ft_strlen(all->cmd))
				tputs_termcap("nd");
		}
		else
		{
			// printf("curline: %d\n", all->curr_line);
			// printf("nbLines: %d\n", all->nb_lines);
			// ct -= PROMPT_LEN;
			// printf("\nct: %d\n", ct);
			// ft_putstr("HEEEEEEEEEERE\n\n\n");
			while (ct-- > 0)
				tputs_termcap("nd");
		}
	}
	else
		tputs_termcap("bl");
}
