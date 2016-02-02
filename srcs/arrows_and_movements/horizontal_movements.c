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
	create_cmd(all);
	if (check_if_spaces_after(all, (CURSOR - PROMPT_LEN) + 1))
	{
		CURSOR++;
		tputs_termcap("nd");
		if (all->cmd[CURSOR - PROMPT_LEN] == ' ')
		{
			while (all->cmd[CURSOR - PROMPT_LEN] == ' ')
			{
				if (CURSOR == (LINE_LEN * all->curr_line) - 1)
				{
					tputs_termcap("do");
					all->curr_line++;
				}
				else
					tputs_termcap("nd");
				CURSOR++;
			}
		}
		while (all->cmd[CURSOR - PROMPT_LEN] != ' ')
		{
			if (CURSOR == (LINE_LEN * all->curr_line) - 1)
			{
				tputs_termcap("do");
				all->curr_line++;
			}
			else
				tputs_termcap("nd");
			CURSOR++;
		}
	}
	else if (CURSOR + PROMPT_LEN < (int)ft_strlen(all->cmd))
		goto_end(all);
}

void	opt_left_move(t_all *all)
{
	create_cmd(all);
	if (check_if_spaces_before(all, (CURSOR - PROMPT_LEN) - 1))
	{
		CURSOR--;
		tputs_termcap("le");
		while (all->cmd[CURSOR - PROMPT_LEN] != ' ')
		{
			if (all->curr_line > 1
				&& CURSOR == ((all->curr_line - 1) * LINE_LEN))
				goto_up(all);
			else
				tputs_termcap("le");
			CURSOR--;
		}
		if (all->cmd[CURSOR - PROMPT_LEN - 1] == ' ')
		{
			while (all->cmd[CURSOR - PROMPT_LEN] == ' ')
			{
				if (all->cmd[(CURSOR - PROMPT_LEN) - 1] != ' ')
					break ;
				if (all->curr_line > 1
					&& CURSOR == ((all->curr_line - 1) * LINE_LEN))
					goto_up(all);
				else
					tputs_termcap("le");
				CURSOR--;
			}
		}
	}
	else
		goto_begin(all);
}

void	reprint_char(t_all *all, t_cmd *nav)
{
	// printf("nav->c: [ %c ]\n", nav->c);
	if (all->current_key == K_LEFT && all->cpy_move_right >= 0
		&& CURSOR > all->save_cursor_pos)
	{
		standard_mode(nav->c);
		all->cpy_move_right--;
	}
	else if (all->current_key == K_RIGHT && all->cpy_move_left >= 0
		&& CURSOR < all->save_cursor_pos)
	{
		standard_mode(nav->c);
		all->cpy_move_left--;
	}
	else
		reverse_mode(nav->c);
}

void	goto_up(t_all *all)
{
	all->curr_line--;
	tputs_termcap("up");
	CURSOR = (all->curr_line > 1)
	? (all->curr_line - 1) * LINE_LEN : 1;
	while (CURSOR < (all->curr_line * LINE_LEN))
	{
		tputs_termcap("nd");
		CURSOR++;
	}
}

void	horizontal_moves(t_all *all)
{
	all->already_open = 0;
	if (all->already_in_select
 		&& ((size_t)all->cursor_pos - PROMPT_LEN) < all->cmd_termcaps->lenght)
	{
		// ft_putstr("OK\n");
		reprint_char(all, goto_cursor_pos(all->cmd_termcaps->head,
			(all->cursor_pos - PROMPT_LEN) + 1));
	}
	if (all->current_key == K_LEFT && CURSOR > PROMPT_LEN)
	{
		if (all->curr_line > 1
			&& CURSOR == ((all->curr_line - 1) * LINE_LEN))
			goto_up(all);
		else
			tputs_termcap("le");
		CURSOR--;
		all->cpy_move_left += 
 			(all->already_in_select && all->cpy_move_right == 0) ? 1 : 0;
	}
	if (all->current_key == K_RIGHT
		&& (CURSOR - PROMPT_LEN) < (int)all->cmd_termcaps->lenght)
	{
		if (CURSOR == (LINE_LEN * all->curr_line) - 1)
		{
			tputs_termcap("do");
			all->curr_line++;
		}
		else
			tputs_termcap("nd");
		CURSOR++;
		all->cpy_move_right += 
 			(all->already_in_select && all->cpy_move_left == 0) ? 1 : 0;
	}
}