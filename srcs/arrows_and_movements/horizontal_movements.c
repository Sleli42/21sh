/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_movements.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/03 18:00:16 by lubaujar          #+#    #+#             */
/*   Updated: 2016/01/03 18:00:18 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	opt_right_move(t_all *all)
{
	t_cmd	*nav;
	t_cmd	*save_pos;

	nav = goto_cursor_pos(all->cmd_termcaps->head, all->cursor_pos - 1);
	save_pos = nav;
	if (check_if_spaces_after(all->cmd_termcaps, all->cursor_pos - 1))
	{
		while (nav && nav->next)
		{
			if (nav->prev != save_pos && nav->c == ' ' && nav->next->c != ' ')
			{
				if (save_pos != all->cmd_termcaps->head)
				{
					tputs_termcap("le");
					all->cursor_pos--;
					nav = nav->prev;
				}
				break ;
			}
			tputs_termcap("nd");
			all->cursor_pos++;
			nav = nav->next;
		}
	}
	else
		goto_end(all);
}

void	opt_left_move(t_all *all)
{
	t_cmd	*nav;

	nav = goto_cursor_pos(all->cmd_termcaps->head, all->cursor_pos - 1);
	if (check_if_spaces_before(all->cmd_termcaps, all->cursor_pos - 1))
	{
		while (nav)
		{
			if (nav->c == ' ' && nav->prev->c != ' ')
			{
				tputs_termcap("le");
				all->cursor_pos--;
				nav = nav->prev;
				break ;
			}
			tputs_termcap("le");
			all->cursor_pos--;
			nav = nav->prev;
		}
	}
	else
		goto_begin(all);
}

static	void	reprint_char(t_all *all, t_cmd *nav)
{
	// printf("move right: %d\n", all->cpy_move_right);
	if (all->current_key == K_LEFT && all->cpy_move_right >= 0
		&& all->cursor_pos > all->save_cursor_pos)
	{
		//printf("move right: %d\n", all->cpy_move_right);
		//printf("char2change: |%c|\n", nav->c);
		standard_mode(nav->c);
		all->cpy_move_right--;
	}
	else if (all->current_key == K_RIGHT && all->cpy_move_left >= 0
		&& all->cursor_pos < all->save_cursor_pos)
	{
		standard_mode(nav->c);
		all->cpy_move_left--;
	}
	else
		reverse_mode(nav->c);
}

void	horizontal_moves(t_all *all)
{
	//all->curr_line = define_current_line(all, all->cursor_pos);
	if (all->already_in_select
		&& (size_t)all->cursor_pos < all->cmd_termcaps->lenght + 1)
		reprint_char(all, goto_cursor_pos(all->cmd_termcaps->head, all->cursor_pos));
	if (all->current_key == K_LEFT && all->cmd_termcaps->lenght > 0 && all->cursor_pos > 1)
	{
		// tputs_termcap("sr");
		// if (all->curr_line == 2)
		// {
		// 	// if (all->cursor_pos == all->ws.ws_col)
		// 	// 	all->curr_line++, all->nl = 0;
		// 	printf("currLine: %d\n", all->curr_line);
		// 	printf("res : %d\n", (all->curr_line - 1) * all->ws.ws_col);
		// 	printf("allCurs: %d\n", all->cursor_pos + 1);
		// }
		//tputs_termcap("le");
		 // printf("cursor2save: %d\n", all->cursor_pos);
		 // printf("curr_line: %d\n", all->curr_line);
		if (all->curr_line > 1 && all->cursor_pos + 2 == all->ws.ws_col * (all->curr_line - 1))
		{
			// printf("allCurs: %d\n", all->cursor_pos);
			//all->cursor_pos--;
			tputs_termcap("up");
			all->curr_line--;
		//	printf("lenLine: %d\n", all->ws.ws_col);
		//	printf("currLine: %d\n", all->curr_line);
			all->cursor_pos = (all->curr_line > 1) ? 
				(all->ws.ws_col * (all->curr_line - 1)) + 1 : 1;
		//	printf("allCurs: %d\n", all->cursor_pos);
			while (all->cursor_pos < all->ws.ws_col * all->curr_line)
			{
				all->cursor_pos++;
				tputs_termcap("nd");
			}
			all->cursor_pos -= 2;
		}
		else
			tputs_termcap("le");
		all->cursor_pos--;
		all->cpy_move_left += 
			(all->already_in_select && all->cpy_move_right == 0) ? 1 : 0;
	}
	if (all->current_key == K_RIGHT && all->cmd_termcaps->lenght > 0
		&&  (size_t)all->cursor_pos < all->cmd_termcaps->lenght + 1)
	{
		// tputs_termcap("sf");
		// printf("currLine: %d\n", all->curr_line);
		// printf("res : %d\n", all->curr_line * all->ws.ws_col);
		//printf("allCurs: %d\n", all->cursor_pos);
		if (all->cursor_pos + 3 == (all->ws.ws_col * all->curr_line))
		{
		//	write(1, "here\n", 5);
			tputs_termcap("do");
			all->curr_line++;
			//tputs_termcap("le");
		}
		else
			tputs_termcap("nd");
		all->cursor_pos++;
	//	printf("allCurs: %d\n", all->cursor_pos);
		all->cpy_move_right += 
			(all->already_in_select && all->cpy_move_left == 0) ? 1 : 0;
	}
}