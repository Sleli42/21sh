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

	nav = goto_cursor_pos(all->cmd_termcaps->head, all->cursor_pos - (PROMPT_LEN - 1));
	save_pos = nav;
	printf("NAV FOUND: [ %c ]\n", nav->c);
	printf("NAV prev FOUND: [ %c ]\n", nav->prev->c);
	// printf("NAV next FOUND: [ %c ]\n", nav->next->c);
	if (check_if_spaces_after(all->cmd_termcaps, all->cursor_pos - PROMPT_LEN))
	{
		// write(1, "ok\n", 3);
		while (nav && nav->next)
		{
			if (nav->c == ' ' && nav->prev->c != ' ')
			{
				if (save_pos != all->cmd_termcaps->head)
				{
					tputs_termcap("le");
					all->cursor_pos--;
					nav = nav->prev;
				}
				break ;
			}
			if (all->cursor_pos == (all->curr_line * all->ws.ws_col))
			{
				tputs_termcap("do");
				all->curr_line++;
			}
			else
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

	nav = goto_cursor_pos(all->cmd_termcaps->head, all->cursor_pos - PROMPT_LEN);
	if (check_if_spaces_before(all->cmd_termcaps, all->cursor_pos - PROMPT_LEN))
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
			if (all->cursor_pos < ((all->curr_line - 1) * all->ws.ws_col)
				&& all->curr_line > 1)
			{
				// tputs_termcap("ku");
				all->curr_line--;
				//while ()
			}
			// if (all->cursor_pos == (all->curr_line - 1) * all->ws.ws_col)
			tputs_termcap("le");
			all->cursor_pos--;
			nav = nav->prev;
		}
	}
	else
		goto_begin(all);
}

void	reprint_char(t_all *all, t_cmd *nav)
{
	if (all->current_key == K_LEFT && all->cpy_move_right >= 0
		&& all->cursor_pos > all->save_cursor_pos)
	{
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
	// tputs_termcap("mi");
	// printf("cursor: %d\n", all->cursor_pos);m
	if (all->current_key == K_LEFT && all->cursor_pos > PROMPT_LEN)
	{
		if (all->curr_line > 1
			&& all->cursor_pos == ((all->curr_line - 1) * all->ws.ws_col))
		{
			// write(1, "stop\n", 5);
			all->curr_line--;
			tputs_termcap("up");
			// printf("cuurLine: %d\n", all->curr_line);
			// printf("all->cursor_pos: %d\n", all->cursor_pos);
			all->cursor_pos = (all->curr_line > 1)
				? (all->curr_line - 1) * all->ws.ws_col : 1;
			while (all->cursor_pos < (all->curr_line * all->ws.ws_col))
			{
				tputs_termcap("nd");
				all->cursor_pos++;
			}
	//		printf("all->cursor_pos: %d\n", all->cursor_pos);
		}
		else
			tputs_termcap("le");
		all->cursor_pos--;
	}
	if (all->current_key == K_RIGHT
		&& (all->cursor_pos - PROMPT_LEN) < (int)all->cmd_termcaps->lenght)
	{
		if (all->cursor_pos == (all->ws.ws_col * all->curr_line) - 1)
		{
	//		write(1, "here\n", 5);
			tputs_termcap("do");
			all->curr_line++;
		}
		else
			tputs_termcap("nd");
		all->cursor_pos++;
	}
}

/*
void	horizontal_moves(t_all *all)
{
	if (all->already_in_select
		&& (size_t)all->cursor_pos < all->cmd_termcaps->lenght + 1)
		reprint_char(all, goto_cursor_pos(all->cmd_termcaps->head, all->cursor_pos));
	if (all->current_key == K_LEFT && all->cmd_termcaps->lenght > 0 && all->cursor_pos > LEN_PROMPT)
	{
		if (all->curr_line > 1 && all->cursor_pos + 2 == all->ws.ws_col * (all->curr_line - 1))
		{
			tputs_termcap("up");
			all->curr_line--;
			all->cursor_pos = (all->curr_line > 1) ? 
				(all->ws.ws_col * (all->curr_line - 1)) + 1 : 1;
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
		if (all->cursor_pos + 3 == (all->ws.ws_col * all->curr_line))
		{
			tputs_termcap("do");
			all->curr_line += 1;
		}
		else
			tputs_termcap("nd");
		all->cursor_pos++;
		all->cpy_move_right += 
			(all->already_in_select && all->cpy_move_left == 0) ? 1 : 0;
	}
}
*/