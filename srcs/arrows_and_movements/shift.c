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

void	shift_last_char(t_all *all)
{
	char	save_char;
	int		ct;

	ct = all->cursor_pos + 2;
	while (ct < (all->ws.ws_col * all->curr_line))
		ct++;
	//printf("ct = %d\n", ct);
	//printf("char - 1 find: |%c|\n", all->cmd[ct - 3]);
	// printf("char find: |%c|\n", all->cmd[ct]);
	// printf("char + 1 find: |%c|\n", all->cmd[ct + 1]);
	save_char = all->cmd[ct - 3];
	tputs_termcap("do");
	write(1, &save_char, 1);
}

void	shift(t_all *all)
{
//	all->curr_line = define_current_line(all, all->cursor_pos);
	create_cmd(all);
	//printf("nb_lines: %d\n", all->nb_lines);
	// if (all->nl)
	// {
	// 	tputs_termcap("do");
 // 		//printf("curs[]: |%c|\n", all->cmd[all->cursor_pos - 1]);
	// 	write(1, &all->cmd[all->cursor_pos - 1], 1);
	// 	tputs_termcap("le");
	// 	all->nl = 0;
	// }
	if ((int)ft_strlen(all->cmd) + 2 == all->ws.ws_col * all->nb_lines)
	{		/* if char -> EOL */
		if (all->nb_lines - all->curr_line == 0)
		{		/* if 1st Line */
			tputs_termcap("sc");
			tputs_termcap("do");
			write(1, &all->cmd[ft_strlen(all->cmd) - 1], 1);
			tputs_termcap("rc");
			tputs_termcap("up");
		}
		/* A FAIRE 
		else	{
			...
		}
		*/
	}
	else if (all->cursor_pos + 2 == (all->ws.ws_col * all->curr_line))
 	{	/* if cursor -> EOL */
 		//write(1, "here\n", 5);
 		tputs_termcap("do");
 		//printf("curs[]: |%c|\n", all->cmd[all->cursor_pos - 1]);
		write(1, &all->cmd[all->cursor_pos - 1], 1);
		tputs_termcap("le");
		all->curr_line++;
		//printf("curr_lien : %d\n", all->curr_line);
		//printf("cursor: %d\n", all->cursor_pos);
		// printf("cursor + 2: %d\n", all->cursor_pos + 2);
		// printf("currLine: %d\n", all->curr_line);
 		// printf("curs[]: |%c|\n", all->cmd[all->cursor_pos]);
	 	// printf("curs[ - 1]: |%c|\n", all->cmd[all->cursor_pos - 1]);
	 	// printf("curs[ - 1]: |%c|\n", all->cmd[all->cursor_pos - 3]);
 		//write(1, &all->cmd[all->cursor_pos - 1], 1);
 		//write(1, "|\n", 2);
 		//tputs_termcap("nd");
 	// 	tputs_termcap("do");
 	// 	//printf("curs[]: |%c|\n", all->cmd[all->cursor_pos - 1]);
		// write(1, &all->cmd[all->cursor_pos - 1], 1);
		// tputs_termcap("le");
		// all->cursor_pos += 1;
	}
	else if (all->curr_line < all->nb_lines && all->nb_lines - all->curr_line != 0)
	{		/* shift last char -> 1st char */
		int		ct = all->curr_line;
		//write(1, "here2\n", 5);
		tputs_termcap("sc");
		while (all->nb_lines - ct > 0)
		{
			shift_last_char(all);
			ct++;
		}
		tputs_termcap("rc");
	}
}

// void	shift(t_all *all)
// {
// 	int		ct;
// 	int		save;
// 	int		save_line;
	
// 	all->curr_line = define_current_line(all, all->cursor_pos);
// 	ct = 0;
// 	save = all->cursor_pos;
// 	create_cmd(all);
// 	if ((int)ft_strlen(all->cmd) == (all->ws.ws_col * all->nb_lines) - 3)
// 	{	/*		si char == EOL		*/
// 		//printf("all->nb_lines - all->curr_line: %d\n", all->nb_lines - all->curr_line);
// 		if (all->nb_lines - all->curr_line == 0)
// 		{	/*		si 1st line		*/
// 			//printf("all->nb_lines - all->curr_line: %d\n", all->nb_lines - all->curr_line);
// 			tputs_termcap("sc");
// 			tputs_termcap("do");
// 			write(1, &all->cmd[ft_strlen(all->cmd) - 1], 1);
// 			tputs_termcap("rc");
// 			tputs_termcap("up");
// 		}
// 		else
// 		{	/*		si line > 1		*/
// 			ct = all->cursor_pos + 2;
// 			save_line = 0;
// 			tputs_termcap("sc");
// 			while (ct++ < (int)ft_strlen(all->cmd))
// 			{
// 				if (ct == all->curr_line * all->ws.ws_col)
// 				{
// 					//save_line++;
// 					all->curr_line++;
// 					tputs_termcap("do");
// 				}
// 				//tputs_termcap("nd");
// 			}
// 			write(1, &all->cmd[ft_strlen(all->cmd) - 1], 1);
// 			tputs_termcap("rc");
// 			tputs_termcap("up");
// 		}
// 		all->nb_lines++;
// 	}
// 	else if (all->cursor_pos + 2 == (all->ws.ws_col * all->curr_line))
// 	{	/*		si cursor == EOL		*/
// 		//write(1, "here\n", 5);
// 		// printf("pos : %d\n", all->cursor_pos);
// 		// printf("len : %d\n", all->ws.ws_col);
// 		// printf("currLine : %d\n", all->curr_line);
// 		tputs_termcap("do");
// 		write(1, &all->cmd[all->cursor_pos - 1], 1);
// 		tputs_termcap("le");
// 		save++;
// 	}
// 	else if (all->curr_line < all->nb_lines && all->nb_lines - all->curr_line != 0)
// 	{	/* 		shift last char to 1st char 		*/
// 		// write(1, "here\n", 5);
// 		tputs_termcap("sc");
// 		while (all->nb_lines - all->curr_line > 0)
// 		{
// 			shift_last_char(all);
// 			all->curr_line++;
// 		}
// 		tputs_termcap("rc");
// 	}
// 	else
// 	{
// 		return ;
// 	}
// 	all->cursor_pos = save;
// }