/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 18:26:08 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/21 16:11:11 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

void	shift_first_char(t_all *all, int curr_line)
{
	while (CURSOR++ < (curr_line * LINE_LEN))
		tputs_termcap("nd");
	write(1, &all->cmd[(curr_line * LINE_LEN) - 4], 1);
	tputs_termcap("do");
	tputs_termcap("dc");
}

void	shift_last_char(t_all *all, int curr_line)
{
	int		ct;

	ct = CURSOR - PROMPT_LEN;
	while (ct < (LINE_LEN * curr_line) - PROMPT_LEN)
		ct++;
	tputs_termcap("do");
	write(1, &all->cmd[ct], 1);
}

void	eof(t_all *all)
{
	int		save;

	save = all->curr_line;
	tputs_termcap("sc");
	all->up_count = 0;
	if (all->nb_lines - all->curr_line == 0)
	{
		tputs_termcap("do");
		write(1, &all->cmd[ft_strlen(all->cmd) - 1], 1);
	}
	else
		while (all->nb_lines - save >= 0)
			shift_last_char(all, save++);
	tputs_termcap("rc");
	if (all->curr_row == all->max_rows || \
		(((all->curr_row * LINE_LEN) + (int)ft_strlen(all->cmd)) \
		> ((all->max_rows - 1) * LINE_LEN)))
		tputs_termcap("up");
}

void	eol(t_all *all)
{
	int		save;
	int		ct;

	save = all->curr_line;
	ct = 0;
	while (all->nb_lines - save > 0)
	{
		tputs_termcap("do");
		write(1, &all->cmd[CURSOR - PROMPT_LEN], 1);
		tputs_termcap("le");
		save++;
		ct++;
	}
	while (ct-- > 1)
		tputs_termcap("up");
	all->curr_line++;
}

void	shift(t_all *all)
{
	int		ct;

	// printf("currLine: %d\n", all->curr_line);
	create_cmd(all);
	get_cursor_row(all);
	ct = 0;
	if (PROMPT_LEN + ((int)ft_strlen(all->cmd) - 1) == END_OF_FILE)
		eof(all);
	else if (CURSOR == END_OF_LINE)
		eol(all);
	else if (all->curr_line < all->nb_lines && \
				all->nb_lines - all->curr_line > 0)
	{
		ct = all->curr_line;
		tputs_termcap("sc");
		while (all->nb_lines - ct > 0)
			shift_last_char(all, ct++);
		tputs_termcap("rc");
	}
}
