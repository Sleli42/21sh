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
	// printf("pos cursor: %d\n", pos + 3);
	// printf("nb lines: %d\n", nb_lines);
	// printf("len line: %d\n", all->ws.ws_col);
	// printf("pos/nbline: %d\n", (pos / nb_lines));
	// printf("col*curr: %d\n", (all->ws.ws_col * curr));
	while (pos > (all->ws.ws_col * curr) - 2)
		curr++;
	// printf("curr: %d\n", curr);
	return (curr);
}

void	shift_last_char(t_all *all)
{
	//int		ct;
	char	save_char;

	//printf("len line: %d\n", all->ws.ws_col);
	//ct = all->cursor_pos;
	//printf("pos: |%d|\n", ct);
	// if (all->curr_line >= 1)
	// {
//	printf("curr line: %d\n", all->curr_line);
		while (all->cursor_pos <= (all->ws.ws_col * all->curr_line) - 3)
			all->cursor_pos++;
		save_char = all->cmd[all->cursor_pos - 1];
		//printf("\nc find: |%c|\n", all->cmd[all->cursor_pos - 1]);
		// printf("pos: |%d|\n", ct);
	//}
	// else if (all->curr_line > 1)
	// {
	// 	ct = all->cursor_pos;
	// 	printf("tofind: |%c|\n", all->cmd[(all->ws.ws_col * all->curr_line) - 3]);
	// 	while (ct < (all->ws.ws_col * all->curr_line))
	// 		ct++;
	// 	save_char = all->cmd[ct];
	// 	printf("\nc find: |%c|\n", all->cmd[all->cursor_pos - 1]);
	// }
	//tputs_termcap("sc");
	//printf("cursor: %d && [ %c ] \n", all->cursor_pos, all->cmd[all->cursor_pos]);
	// 
	// {
	// 	//write(1, "|", 1);
	// 	while (all->cursor_pos++ <= all->ws.ws_col * all->curr_line)
	// 		tputs_termcap("nd");
	// 	tputs_termcap("cr");
	// 	//write(1, "|", 1);
	// 	// tputs_termcap("do");
	// 	// printf("cursor: %d && [ %c ] \n", all->cursor_pos, all->cmd[all->cursor_pos]);
	//  // 	printf("len line: %d\n", (int)ft_strlen(all->cmd));
	// }
	// {
		tputs_termcap("do");
	// 	// while (all->cursor_pos++ <= (int)ft_strlen(all->cmd))
	// 	// 	tputs_termcap("nd");
	// }
	//tputs_termcap("do");
	write(1, &save_char, 1);
	//tputs_termcap("rc");
	// while (all->cursor_pos <= all->ws.ws_col * all->curr_line)
//	all->cursor_pos += 4;
}

void	shift(t_all *all)
{
	//int		curr_line;
	int		ct;
	int	save;
	
	all->curr_line = define_current_line(all, all->cursor_pos);
	ct = all->nb_lines;
	// printf("nb_lines: %d\n", all->nb_lines);
	//all->curr_line = define_current_line(all, all->cursor_pos);
	// printf("cursor: %d\n", all->cursor_pos);
	// printf("ws_col: %d\n", all->ws.ws_col - 3);
	// printf("ws_col*all->curr_line: %d\n", all->ws.ws_col * all->curr_line - 3);
	save = all->cursor_pos;
	create_cmd(all);
	// while (ct < all->nb_lines)
	// {
	// 	all->curr_line = define_current_line(all, all->cursor_pos);
		//printf("all->curr_line: %d\n", all->curr_line);
		//printf("lenStr: %zu\n", ft_strlen(all->cmd));
	if ((all->curr_line <= all->nb_lines && all->cursor_pos <= (all->ws.ws_col * all->curr_line) - 3))
		// || (all->curr_line == all->nb_lines && (int)ft_strlen(all->cmd) == (all->ws.ws_col * all->nb_lines) - 3))
	{
		if ((int)ft_strlen(all->cmd) == (all->ws.ws_col * all->nb_lines) - 2
			&& all->nb_lines == 1)
		{
			tputs_termcap("sc");
			//write(1, "1", 1);
			//while (all->cursor_pos++ < (all->ws.ws_col * all->nb_lines) - 3)
			//	tputs_termcap("nd");
			//write(1, "2", 1);
			tputs_termcap("do");
			//write(1, "3", 1);
			//tputs_termcap("ll");
			write(1, &all->cmd[ft_strlen(all->cmd) - 1], 1);
			tputs_termcap("rc");
			tputs_termcap("up");
			all->nb_lines++;
			//write(1, "4", 1);
		}
		// {
		// 	// write(1, "HERE\n", 5);
		// 	//printf("cursor: %d\n", all->cursor_pos);
		// 	while (all->cursor_pos++ < (int)ft_strlen(all->cmd))
		// 	{
		// 		//printf("charOnCursor: |%c|\n", all->cmd[all->cursor_pos - 1]);
		// 	//	write(1, "ok\n", 3);
		// 		tputs_termcap("nd");
		// 	}
		// 	//tputs_termcap("hd");
		// 	write(1, &all->cmd[all->cursor_pos - 1], 1);
		// 	all->nb_lines++;
		// 	// while (all->cursor_pos-- >= save)
		// 	// {
		// 	// 	tputs_termcap("le");
		// 	// }
		// 	// tputs_termcap("ho");
		// //	write(1, "ok\n", 3);
		// 	// tputs_termcap("le");
		// 	// tputs_termcap("le");
		// 	// write(1, "ok\n", 3);
		// 	// all->cursor_pos = all->ws.ws_col + 1;
		// 	// //printf("cursor: %d\n", all->cursor_pos);
		// 	// while (all->cursor_pos-- >= save)
		// 	// 	tputs_termcap("le");
		// }
		else
		{
			tputs_termcap("sc");
			while (all->nb_lines - all->curr_line > 0)
			{
				shift_last_char(all);
				all->curr_line++;
			}
			tputs_termcap("rc");
		}
	}
		//write(1, "here\n", 5);
		//printf("cursor: %d\n", all->cursor_pos);
		//printf("charOnCursor: |%c|\n", all->cmd[all->cursor_pos]);
		//tputs_termcap("rc");
	// if ((all->ws.ws_col * ct) - 3 == (int)ft_strlen(all->cmd))
	// {
	// 	//tputs_termcap("do");
	// 	ft_putstr("TEEEEEEEEEEST\n");
	// 		//printf("cursor: %d && [ %c ] \n", all->cursor_pos, all->cmd[all->cursor_pos]);
	// 		// printf("find: |%c|\n", all->cmd[all->ws.ws_col * ct]);
	// 		//printf("NEW_LINE\n");
	// }
	// else if (all->curr_line < all->nb_lines)
	// 	//|| (all->curr_line <= all->nb_lines && )
	// {
	// 	tputs_termcap("do");
	// 	//save += 1;
	// 	//printf("all->curr_line: %d\n", all->curr_line);
	// 	//all->curr_line++;
	// 	//printf("cursor: %d\n", all->cursor_pos);
	// 	//printf("len line: %d\n", all->ws.ws_col);
	// }
	all->cursor_pos = save;
	//tputs_termcap("nd");
}