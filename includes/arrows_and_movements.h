/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrows_and_movements.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 15:42:18 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/21 15:59:17 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARROWS_AND_MOVEMENTS_H
# define ARROWS_AND_MOVEMENTS_H

# include "full_sh.h"

# define END_OF_FILE	(LINE_LEN * all->nb_lines)
# define END_OF_LINE	(LINE_LEN * all->curr_line)

typedef struct s_all	t_all;
typedef struct s_cmd	t_cmd;

/*
*** ======================================================= ARROWS_AND_MOVEMENTS
*/

/*
*** ======================= parse_keys.c
*/

int			getkey(char *s);
int			down_line(t_all *all);
int			check_keys_arrows(t_all *all, char *buff);
void		parse_keys(t_all *all);

/*
*** ======================= delete_char.c
*/

void		del_char_multi_lines(t_all *all);
void		del_char_k_delete(t_all *all);
void		del_char_k_backspace(t_all *all);
void		del_char(t_all *all);

/*
*** ======================= horizontal_movements.c
*/

void		horizontal_moves(t_all *all);
void		opt_left_move(t_all *all);
void		opt_right_move(t_all *all);
void		reprint_char(t_all *all, t_cmd *nav);

/*
*** ======================= horizontal_movements_tools.c
*/

int			check_if_spaces_before(t_all *all, int pos);
int			check_if_spaces_after(t_all *all, int pos);
t_cmd		*goto_cursor_pos(t_cmd *lst, int pos);
int			count_2_prev_spaces(t_all *all);
int			count_2_next_spaces(t_all *all);

/*
*** ======================= goto.c
*/

void		goto_end(t_all *all);
void		goto_begin(t_all *all);
void		goto_up(t_all *all);
void		goto_right(t_all *all);
void		goto_left(t_all *all);

/*
*** ======================= vertical_movements.c
*/

void		goto_up_line(t_all *all);
void		goto_down_line(t_all *all);

/*
*** ======================= clear_screen.c
*/

void		ft_clear_screen(t_all *all);

/*
*** ======================= copy_cut_and_paste.c
*/

void		copy_buffer(t_all *all);
void		cut_buffer(t_all *all);
void		paste_copy_in_cmd(t_all *all);
void		paste_buffer(t_all *all);

/*
*** ======================= copy_left.c
*/

void		del_highlighted_left(t_all *all);
void		copy_left(t_all *all);

/*
*** ======================= copy_right.c
*/

void		del_highlighted_right(t_all *all);
void		copy_right(t_all *all);

/*
*** ======================= copy_tools.c
*/

void		standard_mode(char char2print);
void		reverse_mode(char char2print);

/*
*** ======================= cut_tools.c
*/

void		cut_right(t_all *all);
void		cut_left(t_all *all);

/*
*** ======================= shift.c
*/

void		shift_first_char(t_all *all, int curr_line);
void		shift_last_char(t_all *all, int curr_line);
void		shift(t_all *all);

/*
*** ======================= shift.c
*/

void		replace_cursor(t_all *all, int save);
void		new_shift(t_all *all);

#endif
