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
	create_cmd(all);
	//ct = all->cursor_pos;
	//printf("pos: |%d|\n", ct);
	// if (all->curr_line >= 1)
	// {
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
	tputs_termcap("do");
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
	tputs_termcap("sc");
	// while (ct < all->nb_lines)
	// {
	// 	all->curr_line = define_current_line(all, all->cursor_pos);
		//printf("all->curr_line: %d\n", all->curr_line);
		// printf("cursor: %d\n", all->cursor_pos);
		//printf("charOnCursor: |%c|\n", all->cmd[all->cursor_pos]);
	if (all->curr_line < all->nb_lines && all->cursor_pos < (all->ws.ws_col * all->curr_line) - 2)
	{
		while (all->nb_lines - all->curr_line != 0)
		{
			shift_last_char(all);
			all->curr_line++;
		}
		//printf("cursor: %d\n", all->cursor_pos);
		//printf("charOnCursor: |%c|\n", all->cmd[all->cursor_pos]);
		tputs_termcap("rc");
		// printf("len*larg: %d\n", all->ws.ws_col * ct);
		// printf("lenStr: %zu\n", ft_strlen(all->cmd));
		if ((all->ws.ws_col * ct) - 2 == (int)ft_strlen(all->cmd))
		{
				// printf("find: |%c|\n", all->cmd[all->ws.ws_col * ct]);
			printf("NEW_LINE\n");
		}
	}
	else if (all->curr_line <= all->nb_lines)
		//|| (all->curr_line <= all->nb_lines && )
	{
		tputs_termcap("do");
		//save += 1;
		//printf("all->curr_line: %d\n", all->curr_line);
		//all->curr_line++;
		//printf("cursor: %d\n", all->cursor_pos);
		//printf("len line: %d\n", all->ws.ws_col);
	}
	all->cursor_pos = save;
	//tputs_termcap("nd");
}