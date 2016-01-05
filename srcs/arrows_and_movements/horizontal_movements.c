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

static void	ft_putgoodchar(t_dlist2 *cmd_termcaps, int pos)
{
	int		ct;
	t_cmd	*nav;
	
	ct = 1;
	nav = cmd_termcaps->head;
	while (ct < pos)
	{
		nav = nav->next;
		ct++;
	}
	//printf("c: %c\n", nav->c);
	tputs_termcap("mr");
	tputs_termcap("im");
	ft_putchar(nav->c);
	tputs_termcap("ei");
	// tputs_termcap("le");
	tputs_termcap("me");
}

void	horizontal_moves(t_all *all)
{
	if (all->current_key == K_LEFT && all->cmd_termcaps->lenght > 0 && all->cursor_pos > 1)
	{
		//write(1, "here\n", 5);
		// tputs_termcap("sr");
		all->cursor_pos--;
		tputs_termcap("le");
	}
	if (all->current_key == K_RIGHT && all->cmd_termcaps->lenght > 0
		&&  (size_t)all->cursor_pos < all->cmd_termcaps->lenght + 1)
	{
		// tputs_termcap("sf");
		all->cursor_pos++;
		tputs_termcap("nd");
	}
	if (all->already_in_copy
		&& (size_t)all->cursor_pos < all->cmd_termcaps->lenght + 1)
	{
		// write(1, "here\n", 5);
		tputs_termcap("dc");
		ft_putgoodchar(all->cmd_termcaps, all->cursor_pos);
		if (all->current_key == K_LEFT)
			tputs_termcap("le");
		if (all->current_key == K_RIGHT)
			tputs_termcap("nd");
	}
}