/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/21 02:17:06 by lubaujar          #+#    #+#             */
/*   Updated: 2015/12/21 02:17:07 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _21SH_H
# define _21SH_H

# include <stdlib.h>
# include <unistd.h>
# include "libft/include/libft.h"
# include <stdio.h>
# include <sys/types.h> 
# include <sys/wait.h>
// termcaps
# include <term.h>
# include <termios.h>
# include <curses.h>
# include <sys/ioctl.h>
# include <dirent.h>

# define	MAXLEN		4096
# define	K_UP		(buff[0] == 27 && buff[1] == 91 && buff[2] == 65)
# define 	K_DOWN		(buff[0] == 27 && buff[1] == 91 && buff[2] == 66)
# define 	K_RIGHT		(buff[0] == 27 && buff[1] == 91 && buff[2] == 67)
# define	K_LEFT		(buff[0] == 27 && buff[1] == 91 && buff[2] == 68)
# define	K_SPACE		(buff[0] == 32 && !buff[1] && !buff[2])
# define	K_ECHAP		(buff[0] == 27 && !buff[1] && !buff[2])
# define	K_BACKSPACE	(buff[0] == 27 && buff[1] == 91 && buff[2] == 51)
# define 	K_DELETE	(buff[0] == 127 && !buff[1] && !buff[2])
# define	K_DELETE2	(buff[0] == 127 && buff[1] == 91 && buff[2] == 65)
# define 	K_ENTER		(buff[0] == 10 && !buff[1] && !buff[2])
# define	K_TAB		(buff[0] == 9 && !buff[1] && !buff[2])

typedef struct termios	t_termios;

typedef struct			s_cmd
{
	char				c;
	struct s_cmd		*next;
	struct s_cmd		*prev;
}						t_cmd;

typedef struct			s_dlist2
{
	struct s_cmd		*head;
	struct s_cmd		*tail;
	size_t				lenght;
}						t_dlist2;

typedef struct			s_all
{
	t_dlist2			*cmd_termcaps;
	t_termios			restore;
	char				*cmd;
	int					cursor;
}						t_all;

void	init_term(void);
void	restore_term(t_termios restore);
int		check_keys_arrows(t_all *all, char buff[3]);
void	make_moves(t_all *all, char buff[3]);
void	loop(t_all *all);

/*
*** ============================================================ dlist_2.c
*/
void	display_dlst(t_dlist2 *lst);
t_dlist2	*create_cmd_dlst(void);
t_cmd		*dlst_cmd_new(char c);
void		swap_elems_cmd(t_cmd *a, t_cmd *b);
t_dlist2	*dlst_insert_cmd(t_dlist2 *lst, t_cmd *node, int pos);
t_dlist2	*dlist_add_front_2(t_dlist2 *lst, t_cmd *node);
t_dlist2	*dlst_add_back_2(t_dlist2 *lst, t_cmd *node);
int			len_lst_cmd(t_cmd *lst);
t_dlist2	*dlst_del_one2(t_dlist2 *lst, char arg2del);
int			update_list2(t_dlist2 *lst, t_cmd *elem);
void		del_dlist2(t_dlist2 *lst);

#endif