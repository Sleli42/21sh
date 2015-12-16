/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 14:24:07 by lubaujar          #+#    #+#             */
/*   Updated: 2015/12/02 14:24:08 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int		check_keys_arrows(char buff[3])
{
	if (K_ENTER)
	{
		tputs_termcap("me");
		return (-1);
	}
	if (K_UP || K_DOWN)
	{
		return (1);
	}
	else if (K_RIGHT || K_LEFT)
	{
		return (2);
	}
	if (K_TAB)
	{
		return (3);
	}
	if (K_DELETE || K_DELETE2)
	{
		return (4);
	}
	return (0);
}

void	make_moves(t_all *all, char buff[3])
{
	//write(1, "here\n", 5);
	//printf("|%c|\n", all->cmd_termcaps->tail->c);
	if (K_UP || K_DOWN)
		goto_latest_commands(all, buff);
	if (K_TAB)
	{
		if (!all->cmd_termcaps->head)
		{
			write(1, "\t", 1);
			all->stop = 0;
		}
		else
			open_directory(all);
	}
	if (K_DELETE || K_DELETE2)
	{
		if (all->already_in_history)
			realloc_termcaps_cmd(all, all->cmd);
		tputs_termcap("me");
		tputs_termcap("dm");
	//	display_dlst2(all->cmd_termcaps);
		if (all->cmd_termcaps->lenght > 0)
		{
			dlst_del_one2(all->cmd_termcaps, all->cmd_termcaps->tail->c);
			tputs_termcap("le");
			tputs_termcap("dc");
		}
		tputs_termcap("ed");
		all->stop = 0;
	}
}