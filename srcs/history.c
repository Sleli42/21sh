/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 01:12:03 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/21 16:06:51 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

void	history_up(t_all *all)
{
	if (all->current_key == K_UP && all->index_history > 1)
	{
		if (CURSOR > PROMPT_LEN)
		{
			del_histo_lines(all, all->lines2del);
			CURSOR = PROMPT_LEN;
		}
		all->index_history--;
		display_index_cmd(all);
	}
	else if (all->current_key == K_UP && !CMD_NULL)
		return ;
}

void	extended_history_down(t_all *all)
{
	t_cmd	*p;

	all->cmd_termcaps ? del_dlist2(all->cmd_termcaps) : NULL;
	all->cmd_termcaps = all->pcmd_t ? all->pcmd_t : NULL;
	if (!(all->cmd_termcaps))
	{
		tputs_termcap("rc");
		tputs_termcap("le");
		tputs_termcap("le");
		tputs_termcap("le");
		return (loop(all));
	}
	else if (!CMD_NULL)
	{
		p = all->cmd_termcaps->head;
		while (p && p->c)
		{
			ft_putchar(p->c);
			CURSOR++;
			p = p->next;
		}
	}
}

void	history_down(t_all *all)
{
	if (all->current_key == K_DOWN \
			&& all->index_history <= all->pos_history - 1)
	{
		all->index_history++;
		if (CURSOR > PROMPT_LEN || all->index_history == all->pos_history)
		{
			del_histo_lines(all, all->lines2del);
			CURSOR = PROMPT_LEN;
		}
		if (all->index_history == all->pos_history)
		{
			extended_history_down(all);
			return ;
		}
		display_index_cmd(all);
	}
}

void	del_histo_lines(t_all *all, int nblines2del)
{
	int		save;

	save = 1;
	while (save++ < nblines2del)
	{
		tputs_termcap("ce");
		tputs_termcap("cb");
		tputs_termcap("up");
	}
	if (all->lines2del > 1 && (all->curr_row * LINE_LEN) + \
		(int)ft_strlen(all->cmd) > ((all->max_rows - 1) * LINE_LEN))
	{
		if (CURSOR > PROMPT_LEN)
		{
			while (CURSOR-- > PROMPT_LEN)
				tputs_termcap("le");
		}
		display_prompt(all);
		tputs_termcap("sc");
	}
	tputs_termcap("rc");
	tputs_termcap("ce");
}

void	goto_latest_commands(t_all *all)
{
	if (all->pcmd_t == all->cmd_termcaps \
		&& all->current_key == K_DOWN && all->index_history == all->pos_history)
		return ;
	get_cursor_row(all);
	all->lines2del = count_lines_2del(all);
	if (CURSOR == PROMPT_LEN)
		tputs_termcap("sc");
	if (all->current_key == K_UP)
		history_up(all);
	if (all->current_key == K_DOWN)
		history_down(all);
}
