/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_binary.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 14:30:16 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/09 14:30:18 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_BINARY_H
# define EXEC_BINARY_H

# include "21sh.h"

typedef struct s_all		t_all;

typedef	struct			s_builtins
{
	char				*action_name;
	void				(*f)(t_all *, char *);
}						t_builtins;

/* -------------------------------------------------------------------------
*** ============================================================ EXEC_BINARY
*/
	/*
	*** ======================= binary_tools.c
	*/
	int			good_access(char *bin);
	char		*create_path(char *path, char *bin);
	void		exec_right_binary(t_all *all, char **argv_bin);
	void		exec_binary(char *bin, char **argv_bin, char **env);
	/*
	*** ======================= cmd_parse.c
	*/
	void		parse_command(t_all *all, char *buff);
	int			check_redirection(char *s);
	/*
	*** ======================= cmd_exec.c
	*/
	void		simple_cmd_loop(t_all *all, \
					const t_builtins built[9], char *cmd);
	void		exec_simple_cmd(t_all *all, char *cmd);
	void		exec_redirection_cmd(t_all *all, char *cmd);
	void		exec_command(t_all *all);

#endif