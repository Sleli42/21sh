/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 14:32:20 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/21 15:59:11 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

# include "full_sh.h"

typedef struct s_all		t_all;

/*
*** ============================================================ REDIRECTS
*/

char	*my_strstr(t_all *all, char *s);
/*
*** ======================= pipe.c
*/

char	***create_pipe_arrays(char **split);
void	loop_pipe_extended(t_all *all, char ***pipe2exec, \
										int dup_stdin, int p[2]);
void	loop_pipe(t_all *all, char ***pipe2exec);
void	create_pipe(t_all *all, char *cmd);

/*
*** ======================= pipe_tools.c
*/

char	*create_good_path(t_all *all, char *cmd);
int		check_redirect(char *s);
int		open_file(char *file, int redir);
char	*redirected_in_args(char **args, int *redir_type);
char	**modify_pipe_array(t_all *all, char **array);

/*
*** ======================= pipe_tools_2.c
*/

int		check_pipe_error(char ***pipe2exec);
int		redirect_in_args(char **array);
int		redirect_in_arrays(t_all *all, char ***arrays);
int		check_and_operator(char ***array);

/*
*** ======================= redirection.c
*/

void	erase_and_replace(t_all *all, char *cmd);
void	add_to_end(t_all *all, char *cmd);
void	read_file(t_all *all, char *cmd);
void	read_stdin_loop(t_all *all, char **argv, char **redirect);
void	read_stdin(t_all *all, char *cmd);

/*
*** ======================= redirection_2.c
*/

char	**replace_argv(char **array, char *redir);
int		count_args(char **array, char *redir);
char	**rework_args_2_exec(char **array, char *redir);
char	*formatting_redirect_cmd(char *cmd, char *redir);
int		check_if_valid_cmd(t_all *all, char *try);

/*
*** ======================= redirection_3.c
*/

int		check_error(t_all *all, char **array, char *redir);
int		check_double_redirection(char **array);
char	*first_redirect(char **array);
char	*get_fd_2_open(char **array, char *redir);
int		count_redirect(char *s);

/*
*** ======================= redirection_tools.c
*/

char	*read_stdin_cpy_buff(void);
char	*my_strstr(t_all *all, char *s);
int		read_stdin_cmp_key(t_all *all, char **argv, char *key, char *tmp_buff);
void	dup_and_exec(t_all *all, char **argv, int fd2back, int fd2dup);
void	exec_double_redirection(t_all *all, char **array);

/*
*** ======================= redirection_error.c
*/

void	redirection_error(char *file);
int		redirection_error_2(void);
void	redirection_error_3(int err);
int		redirection_error_4(void);

/*
*** ======================= aggregation1.c
*/

char	*get_good_file_agg1(char **array);
char	*rework_cmd_agg1(char *cmd);
char	**create_argv_cmd_agg1(char **split_agg, char *file);
void	exec_agg1(t_all *all, char *cmd);

/*
*** ======================= aggregation2.c
*/

char	*rework_cmd_agg2(char *cmd);
char	*get_good_file_agg2(char **array);
char	**create_argv_cmd_agg2(char **split_agg, char *file);
void	exec_agg2_extended_2(t_all *all, char **split_2exec);
void	exec_agg2_extended(t_all *all, char **split_agg, char *file);
void	exec_agg2(t_all *all, char *cmd);

/*
*** ======================= aggregation3.c
*/

char	*rework_cmd_agg3(char *cmd);
char	*get_good_file_agg3(char **array);
char	**create_argv_cmd_agg3(char **split_agg, char *file);
void	exec_agg3_extended(t_all *all, char **split_agg, char *file);
void	exec_agg3(t_all *all, char *cmd);

/*
*** ======================= aggregation_tools.c
*/

int		check_aggregations(char *cmd);
char	*check_file_in_cmd(char *cmd);
int		count_arg_agg(char **array, char *file);
void	close_fd(t_all *all, char *fd2close);
void	exec_aggregations(t_all *all, char *cmd);

/*
*** ======================= aggregation_tools_2.c
*/

int		check_fd_to_fd(char	*s);
int		check_close_fd(char **array);
void	exec_double_fd(t_all *all, char **array);

/*
*** ======================= aggregation_error.c
*/

int		check_error_agg2(t_all *all, char **split, char *file);
int		check_error_agg3(t_all *all, char **split, char *file);

#endif
