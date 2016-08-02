/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_movements.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/03 18:00:16 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/21 16:11:31 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

void	opt_right_move(t_all *all)
{
	int		stop;
	int		max;

	stop = count_2_next_spaces(all) + CURSOR;
	max = (int)ft_strlen(all->cmd) + PROMPT_LEN;
	while ((CURSOR < stop && CURSOR < max))
	{
		if (CURSOR == LINE_LEN * (all->curr_line))
		{
			tputs_termcap("do");
			all->curr_line += 1;
		}
		tputs_termcap("nd");
		CURSOR++;
	}
}

void	opt_left_move(t_all *all)
{
	int		stop;

	stop = CURSOR - count_2_prev_spaces(all);
	while (CURSOR > stop && CURSOR > PROMPT_LEN)
	{
		if (CURSOR == LINE_LEN * (all->curr_line - 1))
			all->curr_line -= 1;
		tputs_termcap("le");
		CURSOR--;
	}
}

void	reprint_char(t_all *all, t_cmd *nav)
{
	if (all->current_key == K_LEFT && all->cpy_move_right >= 0 \
					&& CURSOR - PROMPT_LEN > all->save_cursor_pos)
	{
		standard_mode(nav->c);
		all->cpy_move_right--;
	}
	else if (all->current_key == K_RIGHT && all->cpy_move_left >= 0 \
									&& CURSOR < all->save_cursor_pos)
	{
		standard_mode(nav->c);
		all->cpy_move_left--;
	}
	else
		reverse_mode(nav->c);
}

void	horizontal_moves(t_all *all)
{
	all->already_open = 0;
	if (all->already_in_search)
	{
		(all->prompt) ? ft_strdel(&all->prompt) : NULL;
		all->prompt = ft_strdup(all->histo_prompt);
	}
	if (all->already_in_select \
		&& ((size_t)all->cursor_pos - PROMPT_LEN) < all->cmd_termcaps->lenght)
	{
		reprint_char(all, goto_cursor_pos(all->cmd_termcaps->head, \
									(CURSOR - PROMPT_LEN) + 1));
	}
	if (all->current_key == K_LEFT && CURSOR > PROMPT_LEN)
	{
		goto_left(all);
		all->cpy_move_left += \
			(all->already_in_select && all->cpy_move_right == 0) ? 1 : 0;
	}
	if (all->current_key == K_RIGHT
		&& (CURSOR - PROMPT_LEN) < (int)all->cmd_termcaps->lenght)
	{
		goto_right(all);
		all->cpy_move_right += \
			(all->already_in_select && all->cpy_move_left == 0) ? 1 : 0;
	}
}
