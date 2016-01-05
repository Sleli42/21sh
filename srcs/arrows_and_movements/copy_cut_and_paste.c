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
	if (!all->already_in_cpy)
	{
		all->save_cursor_pos = all->cursor_pos;
		all->already_in_cpy = 1;
		all->cpy_move_right = 0;
		all->cpy_move_left = 0;
	}
	else
	{
		tputs_termcap("me");
		all->already_in_cpy = 0;
		if (all->cpy_move_right > 0)
			copy_right(all);
		else if (all->cpy_move_left > 0)
			copy_left(all);
	}
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
	if (all->copy)
	{
		ft_putstr(all->copy);
		create_cmd(all);
		all->cmd = ft_strjoin(all->cmd, all->copy);
		realloc_termcaps_cmd(all, all->cmd);
	}
}