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

void		goto_up_line(t_all *all)
{
	int		tmp;
	int		min_value;

	tmp = CURSOR - LINE_LEN;
	min_value = PROMPT_LEN;
	if (all->current_key == K_CTRL_UP && all->curr_line > 1)
	{
		while (CURSOR > tmp && CURSOR > min_value)
		{
			if (CURSOR == (LINE_LEN * (all->curr_line - 1)))
				all->curr_line -= 1;
			tputs_termcap("le");
			CURSOR--;
		}
	}
}

void		goto_down_line(t_all *all)
{
	int		tmp;
	int		max_value;

	tmp = CURSOR + LINE_LEN;
	max_value = (int)ft_strlen(all->cmd) + PROMPT_LEN;
	if (all->current_key == K_CTRL_DOWN && all->curr_line < all->nb_lines)
	{
		while (CURSOR < tmp && CURSOR < max_value)
		{
			if (CURSOR == (LINE_LEN * all->curr_line))
			{
				tputs_termcap("do");
				all->curr_line += 1;
			}
			tputs_termcap("nd");
			CURSOR++;
		}
	}
}
