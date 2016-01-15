/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 18:26:08 by lubaujar          #+#    #+#             */
/*   Updated: 2016/01/07 18:26:10 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

// int		define_current_line(t_all *all, int pos)
// {
// 	int 	curr;

// 	curr = 1;
// 	// printf("[curr] pos: %d\n", pos + 3);
// 	// printf("winLen: %d\n", all->ws.ws_col);
// 	// printf("cursPos: %d\n", all->cursor_pos);
// 	while (pos + 2 > (all->ws.ws_col * curr))
// 		curr++;
// 	// if (all->nl == 1)
// 	// {
// 	// 	if (all->cursor_pos == all->ws.ws_col)
// 	// 		all->curr_line++, all->nl = 0;
// 	// }
// 	// if (curr > 1)
// 	// 	write(1, "2 lines\n", 7);
// 	return (curr);
// }

void	shift_last_char(t_all *all, int curr_line)
{
	char	save_char;
	int		ct;

	ct = all->cursor_pos + 2;
	while (ct < (all->ws.ws_col * curr_line))
		ct++;
	save_char = all->cmd[ct - 3];
	tputs_termcap("do");
	write(1, &save_char, 1);
}

void	shift(t_all *all)
{
	int		save = all->curr_line;
	int		ct;

	ct = 0;
	create_cmd(all);
	if ((int)ft_strlen(all->cmd) + 2 == all->ws.ws_col * all->nb_lines)
	{		/* if char -> EOL */
		tputs_termcap("sc");
		if (all->nb_lines - all->curr_line == 0)
		{		/* if 1st Line */
		//	tputs_termcap("sc");
			tputs_termcap("do");
			write(1, &all->cmd[ft_strlen(all->cmd) - 1], 1);
			// tputs_termcap("rc");
			// tputs_termcap("up");
		}
		else
		{
		//	tputs_termcap("sc");
			while (all->nb_lines - save >= 0)
				shift_last_char(all, save++);
			//tputs_termcap("rc");
			//tputs_termcap("up");
		}
		tputs_termcap("rc");
		tputs_termcap("up");
	}
	else if (all->cursor_pos + 2 == (all->ws.ws_col * all->curr_line))
 	{	/* if cursor -> EOL */
 		while (all->nb_lines - save > 0)
 		{
 			tputs_termcap("do");
			write(1, &all->cmd[all->cursor_pos - 1], 1);
			tputs_termcap("le");
			save++;
			ct++;
		}
		while (ct-- > 1)
			tputs_termcap("up");
		all->curr_line++;
	}
	else if (all->curr_line < all->nb_lines && all->nb_lines - all->curr_line != 0)
	{		/* shift last char -> 1st char */
		int		ct = all->curr_line;
		tputs_termcap("sc");
		while (all->nb_lines - ct > 0)
			shift_last_char(all, ct++);
		tputs_termcap("rc");
	}
}