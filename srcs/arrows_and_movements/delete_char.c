/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/03 17:57:35 by lubaujar          #+#    #+#             */
/*   Updated: 2016/01/03 17:57:36 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	del_char_multi_lines(t_all *all)
{
	int	ct;
	int	save;

	ct = all->curr_line;
	save = CURSOR;
	create_cmd(all);
	if ((int)ft_strlen(all->cmd) < ((all->nb_lines - 1) * LINE_LEN) \
															- PROMPT_LEN)
		all->nb_lines--;
	tputs_termcap("sc");
	while (ct < all->nb_lines)
	{
		shift_first_char(all, ct);
		ct++;
	}
	CURSOR = save;
	tputs_termcap("rc");
}

void	del_char(t_all *all)
{
	all->already_open = 0;
	if (all->already_in_history)
		realloc_termcaps_cmd(all, all->cmd);
	tputs_termcap("dm");
	if (all->cmd_termcaps->lenght > 0 && CURSOR >= PROMPT_LEN)
	{
		if ((size_t)CURSOR - PROMPT_LEN <= all->cmd_termcaps->lenght + 1)
		{
			(all->current_key != K_BACKSPACE)
			? dlst_del_one2(all->cmd_termcaps, CURSOR - (PROMPT_LEN - 1))
				: dlst_del_one2(all->cmd_termcaps, CURSOR - PROMPT_LEN);
		}
		(all->current_key == K_BACKSPACE)
			? tputs_termcap("le") : NULL;
		tputs_termcap("dc");
		if (all->current_key == K_BACKSPACE)
			CURSOR--;
		if (all->nb_lines > 1)
			del_char_multi_lines(all);
	}
	tputs_termcap("ed");
}
