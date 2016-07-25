/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   goto_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/08 15:33:44 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/21 16:11:35 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

void	goto_right(t_all *all)
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

void	goto_left(t_all *all)
{
	// printf("CURSOR: %d\n", CURSOR);
	// printf("PROMPT_LEN: %d\n", PROMPT_LEN);
	if (all->curr_line > 1
			&& CURSOR == ((all->curr_line - 1) * LINE_LEN))
	{
		// printf("CURSOR 1: %d\n", CURSOR);
		goto_up(all);
	}
	else if (CURSOR == ((all->curr_line) * LINE_LEN) - 1
			&& all->already_in_select)
	{
		// printf("CURSOR 2: %d\n", CURSOR);
		reprint_char(all, goto_cursor_pos(all->cmd_termcaps->head, \
												CURSOR - PROMPT_LEN));
	}
	else
	{
		// printf("CURSOR 3: %d\n", CURSOR);
	// printf("PROMPT_LEN: %d\n", PROMPT_LEN);
		tputs_termcap("le");
		// printf("CURSOR: %d\n", CURSOR);
	}
	CURSOR--;
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

void	goto_begin(t_all *all)
{
	if (CURSOR == PROMPT_LEN)
		tputs_termcap("bl");
	else
	{
		while (CURSOR > PROMPT_LEN)
		{
			if (all->curr_line > 1
				&& CURSOR == ((all->curr_line - 1) * LINE_LEN))
				goto_up(all);
			else
				tputs_termcap("le");
			CURSOR--;
		}
	}
}

void	goto_end(t_all *all)
{
	if (CURSOR == (int)all->cmd_termcaps->lenght + PROMPT_LEN)
		tputs_termcap("bl");
	else
	{
		while (all->cmd[CURSOR - PROMPT_LEN])
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
}
