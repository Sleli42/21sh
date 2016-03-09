/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 14:31:17 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/09 14:31:19 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "21sh.h"

typedef struct s_all		t_all;

/* -------------------------------------------------------------------
*** ============================================================ SHELL
*/
	/*
	*** ======================= main.c
	*/
	int			main(int ac, char **av, char **env);
	/*
	*** ======================= shell_init.c
	*/
	t_all		*init_all(char **env);
	/*
	*** ======================= shell_loop.c
	*/
	void		display_prompt(t_all *all);
	void		create_and_exec_command(t_all *all);
	void		define_nb_lines(t_all *all);
	void		write_buffer(t_all *all);
	void		insert_char(t_all *all);
	void		read_keys(t_all *all);
	void		init_loop(t_all *all);
	void		already_in_func(t_all *all);
	void		already_in_func_extended(t_all *all);
	void		get_cursor_row(t_all *all);
	void		parse_cursor_row(t_all *all, char *buff);
	void		loop(t_all *all);
	/*
	*** ======================= shell_tools.c
	*/
	char		goto_elem(t_cmd *cmd, int pos);
	void		update_cmd_line_insert(t_all *all, char char2add);
	void		realloc_termcaps_cmd(t_all *all, char *cmd2realloc);
	void		create_cmd(t_all *all);
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