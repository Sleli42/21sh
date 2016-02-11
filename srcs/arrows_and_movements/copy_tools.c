/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/05 17:17:19 by lubaujar          #+#    #+#             */
/*   Updated: 2016/01/05 17:17:20 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void		standard_mode(char char2print)
{
	tputs_termcap("dc");
	tputs_termcap("me");
	tputs_termcap("im");
	ft_putchar(char2print);
	tputs_termcap("ei");
	tputs_termcap("le");
}

void		reverse_mode(char char2print)
{
	tputs_termcap("dc");
	tputs_termcap("mr");
	tputs_termcap("im");
	ft_putchar(char2print);
	tputs_termcap("ei");
	tputs_termcap("me");
	tputs_termcap("le");
}

static void	del_highlighted_right(t_all *all)
{
	int		i;
	int		save;
	t_cmd	*nav;

	i = (CURSOR - PROMPT_LEN) + 1;
	save = all->cursor_pos - PROMPT_LEN;
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

static void	del_highlighted_left(t_all *all)
{
	int		i;
	t_cmd	*nav;

	i = (all->cursor_pos - PROMPT_LEN);
	nav = goto_cursor_pos(all->cmd_termcaps->head, \
							(all->cursor_pos - PROMPT_LEN) + 1);
	while (nav && i++ < all->save_cursor_pos)
	{
		standard_mode(nav->c);
		nav = nav->next;
		if (i == (LINE_LEN * (all->curr_line)) - PROMPT_LEN)
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
	nav = goto_cursor_pos(all->cmd_termcaps->head,
		(all->cursor_pos - PROMPT_LEN) + 1);
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
