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

int		check_keys_arrows(t_all *all, char buff[3])
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
		//printf("-> %d\n", all_is_spaces(all->cmd_termcaps->head));
		if (!all->cmd_termcaps->head || all_is_spaces(all->cmd_termcaps->head))
			return (0);
		return (3);
	}
	if (K_DELETE || K_DELETE2)
	{
		return (4);
	}
	return (0);
}

void	horizontal_moves(t_all *all, char buff[3])
{
	if (all->current && !all->history_moves)
	{
		all->history_moves = 1;
		realloc_termcaps_cmd(all, all->current);
		all->cursor_pos = (int)all->cmd_termcaps->lenght;
		all->stop = 1;
		//ft_strdel(&all->current);
	}
	if (K_LEFT && all->cmd_termcaps->lenght > 0 && all->cursor_pos > 0)
	{
		//printf("%zu\n", all->cmd_termcaps->lenght);
		//printf("curosr: %d\n", all->cursor_pos);
		all->cursor_pos--;
		tputs_termcap("le");
	}
	if (K_RIGHT && all->cmd_termcaps->lenght > 0
		&&  (size_t)all->cursor_pos < all->cmd_termcaps->lenght)
	{
		all->cursor_pos++;
		tputs_termcap("nd");
	}
	all->stop = 0;
}

void	make_moves(t_all *all, char buff[3])
{
	int			deltab = 0;
	//write(1, "here\n", 5);
	//printf("|%c|\n", all->cmd_termcaps->tail->c);
	if (K_RIGHT || K_LEFT)
		horizontal_moves(all, buff);
	if (K_UP || K_DOWN)
		goto_latest_commands(all, buff);
	if (K_TAB)
	{
		if (!all->cmd_termcaps->head)
		{
			write(1, "\t", 1);
			//dlst_add_back_2(all->cmd_termcaps, dlst_cmd_new('\t', all->cmd_termcaps->lenght += 1));
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
			//printf("%d\n", deltab);
			//display_dlst2(all->cmd_termcaps);
			if (all->cmd_termcaps->tail->c == '\t')
			{		/* no working */
				while (deltab < 6)
				{
					tputs_termcap("le");
					tputs_termcap("dc");
					deltab++;
				}
				dlst_del_one2(all->cmd_termcaps, all->cmd_termcaps->tail->c);
			}
			else
			{
				/* no working */
				
				write(1, "here\n", 5);
				if ((size_t)all->cursor_pos < all->cmd_termcaps->lenght)
				{
					write(1, "here\n", 5);
					dlst_del_one2(all->cmd_termcaps, 
						goto_elem(all->cmd_termcaps->head, all->cursor_pos));
				}
				else
				{
					tputs_termcap("le");
					tputs_termcap("dc");
					dlst_del_one2(all->cmd_termcaps, all->cmd_termcaps->tail->c);
				}
			}
		}
		tputs_termcap("ed");
		all->stop = 0;
	}
}