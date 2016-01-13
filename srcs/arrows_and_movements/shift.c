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

int		define_current_line(t_all *all, int pos)
{
	int 	curr;

	curr = 1;
	// printf("[curr] : %d\n", (all->ws.ws_col * curr));
	// printf("[curr] pos: %d\n", pos + 3);
	while (pos + 3 > (all->ws.ws_col * curr))
		curr++;
	return (curr);
}

void	shift_last_char(t_all *all)
{
	char	save_char;
	int		ct;

	ct = all->cursor_pos;
	while (ct <= (all->ws.ws_col * all->curr_line) - 3)
		ct++;
	//printf("char find: |%c|\n", all->cmd[ct - 1]);
	save_char = all->cmd[ct - 1];
	tputs_termcap("do");
	write(1, &save_char, 1);
}

void	shift(t_all *all)
{
	int		ct;
	int		save;
	int		save_line;
	
	all->curr_line = define_current_line(all, all->cursor_pos);
	ct = 0;
	save = all->cursor_pos;
	create_cmd(all);
	if ((int)ft_strlen(all->cmd) == (all->ws.ws_col * all->nb_lines) - 2)
	{
		//printf("all->nb_lines - all->curr_line: %d\n", all->nb_lines - all->curr_line);
		if (all->nb_lines - all->curr_line == 0)
		{
			//printf("all->nb_lines - all->curr_line: %d\n", all->nb_lines - all->curr_line);
			tputs_termcap("sc");
			tputs_termcap("do");
			write(1, &all->cmd[ft_strlen(all->cmd) - 1], 1);
			tputs_termcap("rc");
			tputs_termcap("up");
		}
		else
		{
			ct = all->cursor_pos;
			save_line = 0;
			tputs_termcap("sc");
			while (ct++ < (int)ft_strlen(all->cmd))
			{
				if (ct == all->curr_line * all->ws.ws_col - 3)
				{
					//save_line++;
					all->curr_line++;
					tputs_termcap("do");
				}
				//tputs_termcap("nd");
			}
			write(1, &all->cmd[ft_strlen(all->cmd) - 1], 1);
			tputs_termcap("rc");
			tputs_termcap("up");
		}
		all->nb_lines++;
	}
	else if (all->cursor_pos + 3 == (all->ws.ws_col * all->curr_line) - 1)
	{
		//write(1, "here\n", 5);
		tputs_termcap("do");
		write(1, &all->cmd[all->cursor_pos], 1);
		tputs_termcap("le");
		//printf("pos : %d\n", all->cursor_pos);
	}
	// else if (all->cursor_pos == all->curr_line * all->ws.ws_col - 3)
	// {
	// 	tputs_termcap("do");
	// 	save++;
	// 	all->curr_line++;
	// }
	else if (all->curr_line < all->nb_lines && all->nb_lines - all->curr_line != 0)
	{
		// write(1, "here\n", 5);
		tputs_termcap("sc");
		while (all->nb_lines - all->curr_line > 0)
		{
			shift_last_char(all);
			all->curr_line++;
		}
		tputs_termcap("rc");
	}
	else
	{
		return ;
	}
	all->cursor_pos = save;
}