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

void		goto_up_line(t_all *all)
{
	int		ct;

	ct = 0;
	ft_putstr("OUAIS OUAIS OUAIS GROS\n");
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
}

void		goto_down_line(t_all *all)
{
	int		ct;

	ct = 0;
	if (all->current_key == K_CTRL_DOWN && all->curr_line < all->nb_lines)
	{
		ct = (all->curr_line == 1) ? count_char_to_shift(all, 0)
			: count_char_to_shift(all, (all->curr_line - 1) * LINE_LEN);
		CURSOR = (LINE_LEN * (all->curr_line)) + ct;
		all->curr_line += 1;
		tputs_termcap("do");
		if (CURSOR - PROMPT_LEN > (int)ft_strlen(all->cmd))
		{
			ct = (LINE_LEN * (all->curr_line - 1) - PROMPT_LEN);
			while (ct++ < (int)ft_strlen(all->cmd))
				tputs_termcap("nd");
		}
		else
		{
			while (ct-- > 0)
				tputs_termcap("nd");
		}
	}
}
