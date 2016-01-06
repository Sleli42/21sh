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

static	void	standard_mode(char char2print)
{
	tputs_termcap("dc");
	tputs_termcap("me");
	tputs_termcap("im");
	ft_putchar(char2print);
	tputs_termcap("ei");
	tputs_termcap("le");
}

static	void	reverse_mode(char char2print)
{
	tputs_termcap("dc");
	tputs_termcap("mr");
	tputs_termcap("im");
	ft_putchar(char2print);
	tputs_termcap("ei");
	tputs_termcap("me");
	tputs_termcap("le");
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
	if (all->already_in_cpy
		&& (size_t)all->cursor_pos < all->cmd_termcaps->lenght + 1)
	{
		// write(1, "here\n", 5);
		reprint_char(all, goto_cursor_pos(all->cmd_termcaps->head, all->cursor_pos));
		// if (all->current_key == K_RIGHT || all->current)
		// if (all->current_key == K_RIGHT)
		// 	tputs_termcap("nd");
	}
	if (all->current_key == K_LEFT && all->cmd_termcaps->lenght > 0 && all->cursor_pos > 1)
	{
		//write(1, "here\n", 5);
		// tputs_termcap("sr");
		all->cursor_pos--;
		tputs_termcap("le");
		all->cpy_move_left += (all->already_in_cpy) ? 1 : 0;
		// if (all->cursor_pos == 1 && all->already_in_cpy)
		// 	all->cpy_move_left += 1;
	}
	if (all->current_key == K_RIGHT && all->cmd_termcaps->lenght > 0
		&&  (size_t)all->cursor_pos < all->cmd_termcaps->lenght + 1)
	{
		// tputs_termcap("sf");
		all->cursor_pos++;
		tputs_termcap("nd");
		all->cpy_move_right += (all->already_in_cpy) ? 1 : 0;
	}
}