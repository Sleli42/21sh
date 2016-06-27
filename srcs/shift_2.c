/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/27 12:25:58 by lubaujar          #+#    #+#             */
/*   Updated: 2016/06/27 12:25:59 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

void		replace_cursor(t_all *all, int save)
{
	CURSOR = (int)all->cmd_termcaps->lenght;
	while (CURSOR > save - PROMPT_LEN)
	{
		tputs_termcap("le");
		CURSOR--;
	}
	CURSOR += PROMPT_LEN;
	all->curr_line = 1;
	define_current_line(all);
}

void		new_shift(t_all *all)
{
	int		save;

	save = CURSOR;
	CURSOR -= LINE_LEN * (all->curr_line - 1);
	while (all->curr_line < all->nb_lines)
	{
		tputs_termcap("do");
		all->curr_line++;
	}
	while (all->curr_line > 1)
	{
		tputs_termcap("ce");
		tputs_termcap("cb");
		tputs_termcap("up");
		all->curr_line--;
	}
	while (CURSOR-- > PROMPT_LEN)
		tputs_termcap("le");
	display_prompt(all);
	create_cmd(all);
	ft_putstr(all->cmd);
	replace_cursor(all, save);
}
