/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/05 10:04:19 by lubaujar          #+#    #+#             */
/*   Updated: 2016/01/05 10:04:22 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	copy_buffer(t_all *all)
{
	//write(1, "here\n", 5);
	all->save_cursor_pos = all->cursor_pos;
	if (!all->already_in_copy)
	{
		all->already_in_copy = 1;
		//tputs_termcap("mr");
	}
	else
	{
		tputs_termcap("me");
		//write(1, "here\n", 5);
		// create_cmd(all);
		// while (all->cursor_pos > 0)
		// {
		// 	tputs_termcap("le");
		// 	all->cursor_pos--;
		// }
		// tputs_termcap("ce");
		// ft_putstr(all->cmd);
		// while (all->cursor_pos < all->save_cursor_pos)
		// {
		// 	tputs_termcap("nd");
		// 	all->cursor_pos++;
		// }
		// tputs_termcap("me");
	}
	// all->copy = NULL;
	// if (all->cursor_pos < (int)all->cmd_termcaps->lenght)
}

void	cut_buffer(t_all *all)
{
	int		ct;
	char	*ret;

	ct = -1;
	ret = NULL;
	if (all->cursor_pos < (int)all->cmd_termcaps->lenght)
	{
		create_cmd(all);
		ret = ft_strnew(all->cursor_pos - 1);
		while (++ct < all->cursor_pos - 1)
			ret[ct] = all->cmd[ct];
		ret[ct] = 0;
		realloc_termcaps_cmd(all, ret);
		ft_strdel(&all->cmd);
		ft_strdel(&ret);
		tputs_termcap("dm");
		tputs_termcap("ce");
		tputs_termcap("ed");
	}
}

void	paste_buffer(t_all *all)
{
	(void)all;
	printf("read stdin 2 paste buff\n");
}