/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 14:32:20 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/09 14:32:22 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

# include "21sh.h"

typedef struct s_all		t_all;

/* -----------------------------------------------------------------------
*** ============================================================ REDIRECTS
*/
	char		*my_strstr(t_all *all, char *s);
	/*
	*** ======================= pipe.c
	*/
	void		create_pipe(t_all *all, char *cmd);
	void		exec_pipe_process(t_all *all, char *cmd, char **args);
	/*
	*** ======================= pipe_tools.c
	*/
	char		*create_good_path(t_all *all, char *cmd);
	int			check_redirect(char *s);
	int			open_file(char *file, int redir);
	char		*redirected_in_args(char **args, int *redir_type);
	/*
	*** ======================= redirection.c
	*/
	void		erase_and_replace(t_all *all, char *cmd);
	void		add_to_end(t_all *all, char *cmd);
	void		read_file(t_all *all, char *cmd);
	void		read_stdin(t_all *all, char *cmd);
	void		exec_redirect(t_all *all, char *cmd, char **args, char *file, int redir);
	/*
	*** ======================= redirection_tools.c
	*/
	void		display_array(char **array);
	void		dup_and_exec(t_all *all, char **argv, int fd2back, int fd2dup);
	int			check_aggregations(char *cmd);
	void		close_fd(t_all *all, char *fd2close);
	void		exec_aggregations(t_all *all, char *cmd);
	/*
	*** ======================= aggregation1.c
	*/
	char		*get_good_file_agg1(char **array);
	char		*rework_cmd_agg1(char *cmd);
	char		**create_argv_cmd_agg1(char **split_agg, char *file);
	void		exec_agg1(t_all *all, char *cmd);
	/*
	*** ======================= aggregation2.c
	*/
	char		*rework_cmd_agg2(char *cmd);
	int			check_error_agg2(t_all *all, char **split, char *file);
	char		*get_good_file_agg2(char **array);
	char		**create_argv_cmd_agg2(char **split_agg, char *file);
	void		exec_agg2(t_all *all, char *cmd);
	/*
	*** ======================= aggregation3.c
	*/
	char		*rework_cmd_agg3(char *cmd);
	int			check_error_agg3(t_all *all, char **split, char *file);
	char		*get_good_file_agg3(char **array);
	char		**create_argv_cmd_agg3(char **split_agg, char *file);
	void		exec_agg3(t_all *all, char *cmd);
	/*
	*** ======================= aggregation_tools.c
	*/
	int			check_aggregations(char *cmd);
	char		*check_file_in_cmd(char *cmd);
	int			count_arg_agg(char **array, char *file);
	void		close_fd(t_all *all, char *fd2close);
	void		exec_aggregations(t_all *all, char *cmd);

#endif