/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_binary.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 14:30:16 by lubaujar          #+#    #+#             */
/*   Updated: 2016/05/24 16:28:59 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_BINARY_H
# define EXEC_BINARY_H

# include "full_sh.h"

typedef struct s_all		t_all;

typedef	struct	s_builtins
{
	char		*action_name;
	void		(*f)(t_all *, char *);
}				t_builtins;

/*
*** ============================================================ EXEC_BINARY
*/

/*
*** ======================= binary.c
*/

void			write_error_exec(char *err);
void			exec_right_binary_loop(t_all *all, char **argv_bin);
void			exec_right_binary(t_all *all, char **argv_bin);
void			exec_binary(t_all *all, char *bin, char **argv_bin, char **env);

/*
*** ======================= binary_tools.c
*/

void			write_error(char *cmd_error);
int				good_access(char *bin);
char			*get_pwd_path(char *bin);
char			*create_path(char *path, char *bin);
void			check_mode_file(t_all *all, char *cmd);

/*
*** ======================= binary_operators.c
*/

int				binary_operators(char **array, int *nb_bin_ope);
void			and_operator(char **parsecmd, int *ct, int err);
void			or_operator(char **parsecmd, int *ct, int err);
void			loop_binary_ope(t_all *all, char **parsecmd);

/*
*** ======================= binary_operators_tools.c
*/

int				error_bin_operators(char *err);
int				check_good_bin_format(char **cmd);
void			goto_next_command(char **parsecmd, int *ct, int err);

/*
*** ======================= parse_cmd.c
*/

char			**medium_split(char **medium, char *cmd);
char			**medium_parse(char *cmd);
void			parse_command(t_all *all, char *buff);
int				len_array(char **array);
int				check_redirection(char *s);

/*
*** ======================= parse_cmd_2.c
*/

int				count_medium_split(char *s);
void			medium_split_extend(char **medium, char *tmp, int *i);
void			medium_split_extend_2(char **medium, \
													char *cmd, int *i, int *ct);

/*
*** ======================= cmd_parse.c
*/

int				len_array(char **array);
void			parse_command(t_all *all, char *buff);
int				check_redirection(char *s);

/*
*** ======================= cmd_exec.c
*/

void			simple_cmd_loop(t_all *all, t_builtins built[11], char *cmd);
void			exec_simple_cmd(t_all *all, char *cmd);
void			exec_redirection_cmd(t_all *all, char *cmd);
void			exec_command(t_all *all);

/*
*** ======================= hash.c
*/

int				hash_bin(char *s);
void			add_to_hash_table(t_all *all, char *bin);
int				hash_exist(char **hash, char *s);

#endif
