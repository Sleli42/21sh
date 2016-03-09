/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 14:35:16 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/09 14:35:17 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTS_H
# define LISTS_H

# include "21sh.h"

typedef struct s_all		t_all;

// typedef struct dirent	t_dirent;
// typedef struct termios	t_termios;
// typedef struct winsize	t_winsize;
// typedef struct stat		t_stat;

typedef struct s_dlist2		t_dlist2;
typedef struct s_cmd		t_cmd;
/* -------------------------------------------------------------------
*** ============================================================ LISTS
*/
	/*
	*** ======================= dlist.c
	*/
	t_node		*dlst_node_new(char *data, size_t index);
	t_dlist		*dlst_add_back(t_dlist *lst, t_node *node);
	t_dlist		*dlst_del_one(t_dlist *lst, char *arg2del);
	void		del_dlist(t_dlist *lst);
	/*
	*** ======================= dlist_tools.c
	*/
	t_dlist		*create_dlst(void);
	int			len_lst_node(t_node *lst);
	int			update_list(t_dlist *lst, t_node *elem);
	/*
	*** ======================= dlist_2.c
	*/
	t_dlist2	*dlst_insert_cmd(t_dlist2 *lst, t_cmd *node, int pos);
	t_dlist2	*dlist_add_front_2(t_dlist2 *lst, t_cmd *node);
	t_dlist2	*dlst_add_back_2(t_dlist2 *lst, t_cmd *node);
	t_dlist2	*dlst_del_one2(t_dlist2 *lst, int pos);
	void		del_dlist2(t_dlist2 *lst);
	/*
	*** ======================= dlist_2_tools.c
	*/
	t_cmd		*dlst_cmd_new(char c);
	t_dlist2	*create_cmd_dlst(void);
	void		swap_elems_cmd(t_cmd *a, t_cmd *b);
	int			len_lst_cmd(t_cmd *lst);
	int			update_list2(t_dlist2 *lst, t_cmd *elem);
	/*
	*** ======================= clist.c
	*/
	t_clist		*create_clst(void);
	t_select	*clst_create_elem(char *s);
	t_clist		*clst_add_elem_back(t_clist *lst, t_select *node);
	int			len_clst(t_select *lst);
	void		del_clist(t_clist **lst);

#endif