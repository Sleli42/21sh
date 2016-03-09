/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 14:34:00 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/09 14:34:01 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMCAPS_H
# define TERMCAPS_H

typedef struct termios	t_termios;

/* ----------------------------------------------------------------------
*** ============================================================ TERMCAPS
*/
	/*
	*** ======================= termcaps_init.c
	*/
	void		init_term(void);
	void		init_windows_size(t_all *all);
	int			init_tty(void);
	/*
	*** ======================= termcaps_tools.c
	*/
	t_all		*f_cpy(t_all *all);
	int			lu_putchar(int c);
	void		tputs_termcap(char *tc);
	void		restore_term(t_termios restore);
	void 		reset_term(void);

#endif