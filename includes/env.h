/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 14:29:02 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/21 16:00:05 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "full_sh.h"
# include "builtins.h"

typedef struct s_all		t_all;
typedef struct s_dlist		t_dlist;
typedef struct s_node		t_node;

/*
*** ======================================================================== ENV
*/

/*
*** ======================= env.c
*/

void		env_display(t_all *all, char *cmd);
void		multi_env_set(t_all *all, char **array);
void		env_set(t_all *all, char *cmd);
void		env_unset(t_all *all, char *cmd);
void		env_modify(t_all *all, char *cmd);

/*
*** ======================= so_env.c
*/

void		set_env_exec(t_env_info *inf, t_all *all);
int			add_spe_env(char **params, t_env_info *inf);
int			check_params(char **params, t_env_info *inf);
int			env_bin(t_all *all, t_env_info *inf);
void		update_env_info(t_all *all, t_env_info inf);

/*
*** ======================= so_env_2.c
*/

int			env_exec(t_all *all, char **params);
char		**check_format(char *cmd);

/*
*** ======================= env_init.c
*/

t_dlist		*dft_env(void);
t_dlist		*init_env(char **env);

/*
*** ======================= env_tools.c
*/

int			count_var_len(char *var);
int			check_match_env(t_all *all, char *s);
int			var_already_exist(t_all *all, char *var);
char		*find_env_arg(t_all *all, char *arg2find);
char		**ft_dupenv(t_dlist *env);

/*
*** ======================= env_tools_2.c
*/

int			check_env_error(char **tmp);
char		**realloc_env_array(t_dlist *env);
void		update_env(t_all *all, char *s);
int			good_env_formatting(char *s);
int			symbol_in_cmd(char *s, int symbol);

#endif
