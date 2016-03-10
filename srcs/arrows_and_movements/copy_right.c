/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_right.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 18:32:51 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/10 18:32:52 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void		del_highlighted_right(t_all *all)
{
	int		i;
	int		save;
	t_cmd	*nav;

	i = (CURSOR - PROMPT_LEN) + 1;
	save = CURSOR - PROMPT_LEN;
	nav = goto_cursor_pos(all->cmd_termcaps->head, \
						all->save_cursor_pos);
	while (i-- > all->save_cursor_pos)
		tputs_termcap("le");
	while (i++ < save)
	{
		standard_mode(nav->c);
		nav = nav->next;
		if (i == (LINE_LEN * (all->curr_line - 1)) - PROMPT_LEN)
			tputs_termcap("do");
		else
			tputs_termcap("nd");
	}
}

void		copy_right(t_all *all)
{
	t_cmd	*nav;
	int		i;

	i = 0;
	del_highlighted_right(all);
	nav = goto_cursor_pos(all->cmd_termcaps->head, \
								all->save_cursor_pos);
	all->copy = ft_strnew(all->cpy_move_right + 1);
	while (nav && all->cpy_move_right > 0)
	{
		all->cpy_move_right--;
		all->copy[i++] = nav->c;
		nav = nav->next;
	}
	all->copy[i] = 0;
}
