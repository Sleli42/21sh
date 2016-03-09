/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 14:33:12 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/09 14:33:13 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

/* ---------------------------------------------------------------------
*** ============================================================ HISTORY
*/
	/*
	*** ======================= history.c
	*/
	void		del_histo_lines(t_all *all, int nblines2del);
	void		history_down(t_all *all);
	void		history_up(t_all *all);
	void		goto_latest_commands(t_all *all);
	/*
	*** ======================= history_tools.c
	*/
	char		**parse_history(void);
	void		add_to_history(t_all *all);
	void		display_index_cmd(t_all *all);
	int			check_history_file(char **histo);
	int			count_lines_2del(t_all *all);

#endif