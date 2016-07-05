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
	// printf("\n\n\ncursor: %d\n", CURSOR);
	// printf("currLine * lineLen: %d\n", all->curr_line * LINE_LEN);
	// printf("lineLen * currline -1: %d\n", (LINE_LEN * (all->curr_line - 1)) - 1);
	if ((LINE_LEN * (all->curr_line - 1)) - 1 == CURSOR)
		all->curr_line -= 1;
	return (all->curr_line);
}

void	del_char_multi_lines(t_all *all)
{
	int	ct;
	int	save;

	// ft_putstr("i'm HERE\n");
	// printf("currLine: %d\n", all->curr_line);
	// printf("(currLine -1) * lineLen: %d\n", LINE_LEN * (all->curr_line - 1));
	// printf("Cursor: %d\n", CURSOR);
	// if ((LINE_LEN * (all->curr_line - 1)) - 1 == CURSOR)
	// {
	// 	all->curr_line = 1;
	// 	define_current_line(all);
	// }
	// all->curr_line = 1;
	// define_current_line(all);
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
	if (all->cmd_termcaps->lenght > 0 && CURSOR > PROMPT_LEN)
	{
		tputs_termcap("dm");
		if ((size_t)CURSOR - PROMPT_LEN <= all->cmd_termcaps->lenght + 1)
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
	/*
	// printf("Cursor: %d\n", CURSOR);
	if (all->cmd_termcaps->lenght > 0 && CURSOR > PROMPT_LEN)
	{
		tputs_termcap("dm");
		if ((size_t)CURSOR - PROMPT_LEN <= all->cmd_termcaps->lenght + 1)
		{
			(all->current_key != K_BACKSPACE)
			? dlst_del_one2(all->cmd_termcaps, CURSOR - (PROMPT_LEN - 1))
				: dlst_del_one2(all->cmd_termcaps, CURSOR - PROMPT_LEN);
		}
		(all->current_key == K_BACKSPACE && CURSOR > PROMPT_LEN)
			? tputs_termcap("le") : NULL;
		tputs_termcap("dc");
		if (all->current_key == K_BACKSPACE)
			CURSOR--;
		if (all->nb_lines > 1)
			del_char_multi_lines(all);
		tputs_termcap("ed");
	}
	*/
}
