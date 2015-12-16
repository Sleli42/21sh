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
	if (K_DELETE)
	{
		return (4);
	}
	return (0);
}

void	make_moves(t_all *all, char buff[3])
{
	//printf("|%c|\n", all->cmd_termcaps->tail->c);
	if (K_UP || K_DOWN)
	{
		//display_dlst_history(all->cmd_history);
		goto_latest_commands(all, buff);
	}
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
	if (K_DELETE)
	{
		// printf("\nlenght list[fct]: %zu\n", all->cmd_termcaps->lenght);
		// printf("------>|%c|\n", all->cmd_termcaps->tail->c);
		//printf("%c && %c\n", all->cmd_termcaps->tail->c, buff[0]);
		if (all->cmd_termcaps->lenght == 1)
		{
			del_dlist2(all->cmd_termcaps);
			tputs_termcap("le");
			tputs_termcap("dc");
		}
		if (all->cmd_termcaps->lenght > 0)
		{
			dlst_del_one2(all->cmd_termcaps, all->cmd_termcaps->tail->c);
			tputs_termcap("le");
			tputs_termcap("dc");
		}
		all->stop = 0;
	}
	// if (K_LEFT)
	// {
		
	// }
}