/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 14:29:02 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/09 14:29:04 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "21sh.h"

typedef struct s_all		t_all;
typedef struct s_dlist		t_dlist;
typedef struct s_node		t_node;

/* -----------------------------------------------------------------
*** ============================================================ ENV
*/
	/*
	*** ======================= env.c
	*/
	void		env_display(t_all *all, char *cmd);
	void		env_set(t_all *all, char *cmd);
	void		env_unset(t_all *all, char *cmd);
	/*
	*** ======================= env_init.c
	*/
	t_dlist		*init_env(char **env);
	/*
	*** ======================= env_tools.c
	*/
	char		*find_env_arg(t_all *all, char *arg2find);
	char		**ft_dupenv(char **env);

#endif