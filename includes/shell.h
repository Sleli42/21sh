/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 14:31:17 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/21 15:59:49 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "full_sh.h"

typedef struct s_all		t_all;
typedef struct s_glob		t_glob;

/*
*** ====================================================================== SHELL
*/

/*
*** ======================= main.c
*/

int			main(int ac, char **av, char **env);

/*
*** ======================= shell_init.c
*/

void		init_loop(t_all *all);
void		init_history(t_all *all);
t_all		*init_all(char **env);
void		init_glob(t_all *all);

/*
*** ======================= shell_loop.c
*/

void		read_keys(t_all *all);
void		already_in_func(t_all *all);
void		already_in_func_extended(t_all *all);
void		loop(t_all *all);

/*
*** ======================= shell_loop_tools.c
*/

void		display_prompt(t_all *all);
void		define_nb_lines(t_all *all);
char		*get_cursor_row_loop(char *buff);
void		get_cursor_row(t_all *all);
void		parse_cursor_row(t_all *all, char *buff);

/*
*** ======================= shell_loop_tools_2.c
*/

int			check_str(char *buff);
void		create_and_exec_command(t_all *all);
void		write_buffer(t_all *all);
void		check_glob(t_glob *g);
void		save_glob(t_all *all, t_glob *g);

/*
*** ======================= shell_tools.c
*/

char		goto_elem(t_cmd *cmd, int pos);
void		update_cmd_line_insert(t_all *all, char char2add);
void		realloc_termcaps_cmd(t_all *all, char *cmd2realloc);
void		create_cmd(t_all *all);
void		define_current_line(t_all *all);

/*
*** ======================= shell_tools_2.c
*/

void		control_d(t_all *all);
void		insert_char_extend(t_all *all);
void		insert_char(t_all *all);

/*
*** ======================= debug.c
*/

void		display_dlst(t_dlist2 *lst);
void		display_current_arg(t_all *all);
void		display_line(t_dlist2 *cmd_termcaps);
void		display_cursor(t_dlist2 *lst, int pos);
void		read_key(char *buff);

/*
*** ======================= error.c
*/

void		error(char *err);
void		term_error(char *err);

#endif
