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
	(void)nb_lines;
	while (pos > all->ws.ws_col * curr)
		curr++;
	// printf("curr: %d\n", curr);
	return (curr);
}

void	shift_char(t_all *all)
{
	int		curr_line;
	
	curr_line = define_current_line(all, all->cursor_pos);
}