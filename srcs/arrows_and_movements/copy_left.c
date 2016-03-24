/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_left.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 18:32:45 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/21 16:12:04 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

void		del_highlighted_left(t_all *all)
{
	int		i;
	t_cmd	*nav;

	i = (CURSOR - PROMPT_LEN);
	nav = goto_cursor_pos(all->cmd_termcaps->head, CURSOR - PROMPT_LEN + 1);
	while (nav && i++ < all->save_cursor_pos)
	{
		standard_mode(nav->c);
		nav = nav->next;
		if (i == (LINE_LEN * all->curr_line) - PROMPT_LEN)
		{
			all->curr_line += 1;
			tputs_termcap("do");
		}
		else
			tputs_termcap("nd");
	}
}

void		copy_left(t_all *all)
{
	t_cmd	*nav;
	int		i;

	i = 0;
	del_highlighted_left(all);
	nav = goto_cursor_pos(all->cmd_termcaps->head, CURSOR - PROMPT_LEN + 1);
	all->copy = ft_strnew(all->cpy_move_left + 1);
	if (CURSOR != PROMPT_LEN)
		nav = nav->next;
	else
	{
		all->cpy_move_left += 1;
		CURSOR -= 1;
	}
	while (nav && i < all->cpy_move_left)
	{
		all->copy[i++] = nav->c;
		nav = nav->next;
		CURSOR++;
	}
	CURSOR += 1;
	all->copy[i] = 0;
}
