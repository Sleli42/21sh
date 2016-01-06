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

void	standard_mode(char char2print)
{
	tputs_termcap("dc");
	tputs_termcap("me");
	tputs_termcap("im");
	ft_putchar(char2print);
	tputs_termcap("ei");
	tputs_termcap("le");
}

void	reverse_mode(char char2print)
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
	t_cmd	*nav;

	i = all->cursor_pos;
	nav = goto_cursor_pos(all->cmd_termcaps->head, all->save_cursor_pos);
	while (i-- > all->save_cursor_pos)
		tputs_termcap("le");
	while (i++ < all->cursor_pos - 1)
	{
		standard_mode(nav->c);
		nav = nav->next;
		tputs_termcap("nd");
	}
}

/* DEL LEFT !!!!! */

void	copy_right(t_all *all)
{
	t_cmd	*nav;
	int		i;

	i = 0;
	nav = goto_cursor_pos(all->cmd_termcaps->head, all->save_cursor_pos);
	del_highlighted_right(all);
	all->copy = ft_strnew(all->cpy_move_right + 1);
	while (nav && all->cpy_move_right > 0)
	{
		all->cpy_move_right--;
		all->copy[i++] = nav->c;
		nav = nav->next;
	}
	all->copy[i] = 0;
}

void	copy_left(t_all *all)
{
	t_cmd	*nav;
	int		i;

	nav = goto_cursor_pos(all->cmd_termcaps->head,
		all->save_cursor_pos - all->cpy_move_left);
	if (all->save_cursor_pos - all->cpy_move_left != 1)
		nav = nav->next;
	all->copy = ft_strnew(all->cpy_move_left + 1);
	i = 0;
	while (nav && i < all->cpy_move_left)
	{
		all->copy[i++] = nav->c;
		nav = nav->next;
	}
	all->copy[i] = 0;
}