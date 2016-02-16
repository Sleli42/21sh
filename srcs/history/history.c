/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 01:12:03 by lubaujar          #+#    #+#             */
/*   Updated: 2016/02/01 10:26:25 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

/*
sc      Sauvegarder la position du curseur
rc      Restaurer la position enregistrée du curseur
cb      Effacer depuis le début de la ligne jusqu'au curseur
*/

void	history_up(t_all *all)
{
	if (all->current_key == K_UP && all->index_history > 1)
	{											/* IF IS NOT LATEST CMD K_UP */
		if (all->cursor_pos > PROMPT_LEN)
		{
			// del_histo_lines(all, count_lines_2del(all));
			// if (all->cursor_pos > LINE_LEN * all->curr_line)
			// 	printf("count nb line 2 del\n");
			// else
			// {
			// ft_putchar('*');
				tputs_termcap("rc");
				// printf("currRow: %d\n", all->curr_row);
				if (all->curr_row == all->max_rows || \
					(((all->curr_row * LINE_LEN) + (int)ft_strlen(all->cmd)) \
					> ((all->max_rows - 1) * LINE_LEN)))
				{
					ft_putstr("YES\n");
					int			i = 1;
					while (i++ < all->lines2del)
						tputs_termcap("up");
				}
				tputs_termcap("ce");
			// if (all->line2write >= all->max_rows)
			// 	ft_putchar('*');
			// }
			all->cursor_pos = PROMPT_LEN;
			// tputs_termcap("sc");
		}
		all->index_history--;
		display_index_cmd(all);
	}
	else if (all->current_key == K_UP && !CMD_NULL)
	{											/* IF IS LATEST CMD K_UP */
		display_index_cmd(all);
	}
}

void	history_down(t_all *all)
{
	if (all->current_key == K_DOWN && all->index_history <= all->pos_history - 1)
	{
		all->index_history++;
		if (all->cursor_pos > PROMPT_LEN || all->index_history == all->pos_history)
		{
			tputs_termcap("rc");
			tputs_termcap("ce");
			all->cursor_pos = PROMPT_LEN;
		}
		if (all->index_history == all->pos_history)
		{
			all->cmd_termcaps ? del_dlist2(all->cmd_termcaps) : NULL;
			all->cmd_termcaps = all->pcmd_t ? all->pcmd_t : NULL;
			if (!(all->cmd_termcaps))
			{
				tputs_termcap("rc");
				tputs_termcap("le");		/* skip prompt len		*/
				tputs_termcap("le");		/* if buffer ==	 NULL	*/
 				tputs_termcap("le");		/* before cmd history	*/
				return (loop(all));
			}
			else if (all->cmd_termcaps && all->cmd_termcaps->head && all->cmd_termcaps->head->c)
			{
				t_cmd *p = all->cmd_termcaps->head;
				//create_cmd(all)
				while (p && p->c)
				{
					ft_putchar(p->c);
					all->cursor_pos++;
					p = p->next;
				}
			}
			return ;
		}
		display_index_cmd(all);
	}
}

void	del_histo_lines(int nblines2del)
{
	int		save;

	save = 1;
	// get_cursor_row(all);
	// printf("curr row: %d\n", all->curr_row);
	while (save++ < nblines2del)
	{
		tputs_termcap("ce");
		tputs_termcap("cb");
		tputs_termcap("up");
	}
	// if (all->line2write >= all->max_rows)
	// {
	// 	// ft_putstr("\n\nYES\n\n");
	// 	while (--save > 0)
	// 		tputs_termcap("up");
	// }
}

void	goto_latest_commands(t_all *all)
{
	// size_t ct;
	// all->stop = 21;
	// if (all->stop == 21)
	// {
	// 	tputs_termcap("sc");
	// 	all->stop = 0;
	// }
	if (all->pcmd_t == all->cmd_termcaps && all->current_key == K_DOWN && all->index_history == all->pos_history)
		return ;
	get_cursor_row(all);
	all->lines2del = count_lines_2del(all);
	// del_histo_lines(count_lines_2del(all));
	// ct = all->cmd_termcaps->lenght > 1 ? all->cursor_pos : PROMPT_LEN;
	// if (CURSOR > LINE_LEN * all->curr_line)
	// del_histo_lines(all, count_lines_2del(all));
	// if (all->line2write >= all->max_rows)
	// printf("line 2 write %d\n", all->line2write);
	// printf(" max rows %d\n", all->max_rows);
	// else
	// {
	// 	if (ct > 0)
	// 	{
	// 		while (ct != PROMPT_LEN)
	// 		{
	// 			tputs_termcap("le");
	// 			ct--;
	// 		}
	// 		tputs_termcap("ce");
	// 		all->cursor_pos = PROMPT_LEN;
	// 	}
	// }
	if (all->cursor_pos == PROMPT_LEN)
	{
		// ft_putstr("YES\n");
		tputs_termcap("sc");
	}
	del_histo_lines(all->lines2del);
	if (all->current_key == K_UP)
		history_up(all);
	if (all->current_key == K_DOWN)
		history_down(all);
}
