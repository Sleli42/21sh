/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 14:34:00 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/21 16:00:25 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMCAPS_H
# define TERMCAPS_H

# include "full_sh.h"

typedef struct termios	t_termios;

/*
*** =================================================================== TERMCAPS
*/

/*
*** ======================= termcaps_init.c
*/

void		init_term(t_all *all, char **env);
void		init_windows_size(t_all *all);
int			init_tty(void);

/*
*** ======================= termcaps_tools.c
*/

t_all		*f_cpy(t_all *all);
int			lu_putchar(int c);
void		tputs_termcap(char *tc);
void		restore_term(t_termios restore);
void		reset_term(t_all *all);

#endif
