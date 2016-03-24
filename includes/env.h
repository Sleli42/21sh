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
char		**realloc_env(t_all *all);
void		update_env(t_all *all, char *s2add);
void		env_set(t_all *all, char *cmd);
void		env_unset(t_all *all, char *cmd);
/*
*** ======================= env_init.c
*/
t_dlist		*dft_env(void);
t_dlist		*init_env(char **env);

/*
*** ======================= env_tools.c
*/

char		*find_env_arg(t_all *all, char *arg2find);
char		**ft_dupenv(char **env);
int			count_var_len(char *var);
int			cmp_env_var(t_all *all, char *s);
int			var_already_exist(t_all *all, char *var);

#endif
