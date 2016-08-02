/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/03 17:57:35 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/21 16:11:42 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

int		define_line(t_all *all)
{
	all->curr_line = 1;
	while (CURSOR >= (LINE_LEN * all->curr_line))
		all->curr_line++;
	if ((LINE_LEN * (all->curr_line - 1)) - 1 == CURSOR)
		all->curr_line -= 1;
	return (all->curr_line);
}

void	del_char_multi_lines(t_all *all)
{
	int	ct;
	int	save;

	ct = define_line(all);
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

void	del_char_k_delete(t_all *all)
{
	if (all->cmd_termcaps->lenght > 0 && CURSOR >= PROMPT_LEN)
	{
		tputs_termcap("dm");
		if ((size_t)CURSOR - PROMPT_LEN <= all->cmd_termcaps->lenght + 1)
			dlst_del_one2(all->cmd_termcaps, CURSOR - (PROMPT_LEN - 1));
		tputs_termcap("dc");
		if (all->nb_lines > 1)
			del_char_multi_lines(all);
		tputs_termcap("ed");
	}
}

void	del_char_k_backspace(t_all *all)
{
	if (all->cmd_termcaps->lenght > 0 && CURSOR >= PROMPT_LEN)
	{
		tputs_termcap("dm");
		if (all->already_in_search && all->cmd_termcaps->lenght >= 1)
		{
			dlst_del_one2(all->cmd_termcaps, all->cmd_termcaps->lenght);
			update_search_line(all);
		}
		else if (!all->already_in_search &&\
			(size_t)CURSOR - PROMPT_LEN <= all->cmd_termcaps->lenght + 1)
			dlst_del_one2(all->cmd_termcaps, CURSOR - PROMPT_LEN);
		tputs_termcap("le");
		tputs_termcap("dc");
		CURSOR--;
		if (all->nb_lines > 1)
			del_char_multi_lines(all);
		tputs_termcap("ed");
	}
}

void	del_char(t_all *all)
{
	all->already_open = 0;
	if (all->current_key == K_BACKSPACE)
		del_char_k_backspace(all);
	else if (all->current_key == K_DELETE)
		del_char_k_delete(all);
}
