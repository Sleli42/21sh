/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 18:26:08 by lubaujar          #+#    #+#             */
/*   Updated: 2016/01/07 18:26:10 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int		define_current_line(t_all *all, int pos)
{
	int 	curr;

	curr = 1;
	// printf("pos cursor: %d\n", pos + 3);
	// printf("nb lines: %d\n", nb_lines);
	// printf("len line: %d\n", all->ws.ws_col);
	// printf("pos/nbline: %d\n", (pos / nb_lines));
	// printf("col*curr: %d\n", (all->ws.ws_col * curr));
	while (pos > all->ws.ws_col * curr)
		curr++;
	// printf("curr: %d\n", curr);
	return (curr);
}

void	shift_last_char(t_all *all, int curr_line)
{
	int		save_pos;
	int		ct;
	char	save_char;

	save_pos = all->cursor_pos + 1;
	ct = 0;
	//printf("len line: %d\n", all->ws.ws_col);
	if (curr_line == 1)
	{
		create_cmd(all);
		while (ct < all->ws.ws_col - 3)
			ct++;
		save_char = all->cmd[ct];
		// printf("\nc find: |%c|\n", all->cmd[ct]);
		// printf("pos: |%d|\n", ct);
	}
}

void	shift(t_all *all)
{
	int		curr_line;
	
	curr_line = define_current_line(all, all->cursor_pos);
	if (curr_line < all->nb_lines && all->cursor_pos <= all->ws.ws_col)
		shift_last_char(all, curr_line);
}