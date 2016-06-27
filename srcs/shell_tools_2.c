/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_tools_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/27 15:18:47 by lubaujar          #+#    #+#             */
/*   Updated: 2016/06/27 15:18:48 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

void	control_d(t_all *all)
{
	create_cmd(all);
	if ((int)all->cmd_termcaps->lenght > 0 \
		&& CURSOR - PROMPT_LEN < (int)all->cmd_termcaps->lenght)
		del_char(all);
	else if (CURSOR - PROMPT_LEN >= (int)all->cmd_termcaps->lenght
		&& (int)all->cmd_termcaps->lenght > 0)
		search_autocomplete(all);
	else if ((int)all->cmd_termcaps->lenght == 0)
	{
		ft_putstr("\n$: exit\n");
		exit(0);
	}
}

void		insert_char_extend(t_all *all)
{
	int		ct;

	ct = 0;
	if (ft_strlen(all->buff) > 1)
	{
		while (all->buff[ct])
		{
			update_cmd_line_insert(all, all->buff[ct]);
			ct++;
		}
	}
	else
		update_cmd_line_insert(all, *all->buff);
	if (all->nb_lines >= 1)
	{
		if (ft_strlen(all->buff) > 1)
			new_shift(all);
		else
			shift(all);
	}
}

void		insert_char(t_all *all)
{
	all->already_open = 0;
	if (*all->buff == '$')
		all->lv += 1;
	tputs_termcap("im");
	if ((CURSOR - PROMPT_LEN) < (int)all->cmd_termcaps->lenght \
		&& *all->buff != '\n')
	{
		if (*all->buff != '\n')
			all->globing.cr_split ? (all->globing.cr_split = 0) : \
												ft_putstr(all->buff);
		insert_char_extend(all);
	}
	else
	{
		if (all->cursor_pos == all->ws.ws_col * all->curr_line)
			all->curr_line++;
		if (*all->buff != '\n')
			write_buffer(all);
	}
	tputs_termcap("ei");
}
