/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_cut_and_paste.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/05 10:04:19 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/21 16:12:09 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

void		copy_buffer(t_all *all)
{
	if (!all->already_in_select)
	{
		all->save_cursor_pos = CURSOR - PROMPT_LEN + 1;
		all->already_in_select = 1;
		all->cpy_move_right = 0;
		all->cpy_move_left = 0;
	}
	else
	{
		tputs_termcap("me");
		all->already_in_select = 0;
		if (all->cpy_move_right > 0)
			copy_right(all);
		else if (all->cpy_move_left > 0)
			copy_left(all);
	}
}

void		cut_buffer(t_all *all)
{
	if (!all->already_in_select)
	{
		all->save_cursor_pos = CURSOR;
		all->already_in_select = 1;
		all->cpy_move_right = 0;
		all->cpy_move_left = 0;
	}
	else
	{
		tputs_termcap("me");
		all->already_in_select = 0;
		if (all->cpy_move_right > 0)
			cut_right(all);
		else if (all->cpy_move_left > 0)
			cut_left(all);
	}
}

void		paste_copy_in_cmd(t_all *all)
{
	int		i;

	i = 0;
	if (CMD_NULL)
		all->cmd_termcaps = create_cmd_dlst();
	while (all->copy[i])
	{
		if (all->copy[i] != '\n')
			ft_putchar(all->copy[i]);
		if (CURSOR - PROMPT_LEN < (int)all->cmd_termcaps->lenght)
			update_cmd_line_insert(all, all->copy[i]);
		else
		{
			dlst_add_back_2(all->cmd_termcaps, dlst_cmd_new(all->copy[i]));
			CURSOR++;
		}
		if (all->nb_lines >= 1)
			shift(all);
		i++;
	}
}

void		paste_buffer(t_all *all)
{
	int		save;

	save = 0;
	if (all->copy)
	{
		all->already_in_paste = 1;
		save = (CURSOR - PROMPT_LEN) + 1;
		tputs_termcap("im");
		paste_copy_in_cmd(all);
		tputs_termcap("ei");
		create_cmd(all);
		realloc_termcaps_cmd(all, all->cmd);
		CURSOR = save + PROMPT_LEN + (ft_strlen(all->copy) - 1);
		define_current_line(all);
	}
}
