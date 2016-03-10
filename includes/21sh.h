/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/03 16:12:43 by lubaujar          #+#    #+#             */
/*   Updated: 2015/11/03 16:12:44 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _21SH_H
# define _21SH_H

# include <stdlib.h>
# include <unistd.h>
# include <libft.h>
# include <stdio.h>
# include <sys/types.h> 
# include <sys/wait.h>
# include <sys/stat.h>
	// termcaps
# include <term.h>
# include <termios.h>
# include <curses.h>
# include <sys/ioctl.h>
# include <dirent.h>
	// others
# include "arrows_and_movements.h"
# include "autocomplete.h"
# include "colors.h"
# include "env.h"
# include "exec_binary.h"
# include "history.h"
# include "lists.h"
# include "read.h"
# include "redirect.h"
# include "shell.h"
# include "termcaps.h"

# define	MAXLEN			2048
# define	K_UP			279165000
# define	K_CTRL_UP		-23278475
# define	K_DOWN			279166000
# define	K_CTRL_DOWN		-23278474
# define	K_RIGHT			279167000
# define	K_CTRL_RIGHT	-23278473
# define	K_LEFT			279168000
# define	K_CTRL_LEFT		-23278472
# define	K_ECHAP			2700000
# define	K_BACKSPACE		12700000
# define	K_DELETE		2145308824
# define	K_ENTER			1000000
# define	K_TAB			900000
# define	K_HOME			279172000
# define	K_END			279170000
# define	K_CTRL_CLEAR	-7040000
# define	K_CTRL_COPY		-6990000
# define	K_CTRL_PASTE	-4302000
# define	K_CTRL_CUT		-4310000

# define 	NOTATTY 		1
# define	PROMPT_LEN		3
# define	LINE_LEN		all->ws.ws_col
# define	CURSOR			all->cursor_pos
# define	CMD_NULL		(!all->cmd_termcaps || !all->cmd_termcaps->head || \
													!all->cmd_termcaps->head->c)
# define	SPLIT_T			" ;&<>()=|*/{}\"\'`\n"

typedef struct dirent	t_dirent;
typedef struct winsize	t_winsize;
typedef struct stat		t_stat;

typedef struct			s_node
{
	char				*s;
	size_t				index;
	struct s_node		*next;
	struct s_node		*prev;
}						t_node;

typedef struct			s_dlist
{
	struct s_node		*head;
	struct s_node		*tail;
	size_t				lenght;
}						t_dlist;

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

typedef struct			s_select
{
	char				*arg;
	int					onArg;
	struct s_select		*next;
	struct s_select		*prev;
}						t_select;

typedef struct			s_clist
{
	struct s_select		*head;
	struct s_select		*tail;
	size_t				lenght;
}						t_clist;

typedef struct			s_var
{
	char				*var_name;
	char				*content;
	struct s_var		*prev;
	struct s_var		*next;
}						t_var;

typedef struct			s_all
{
		// TERM 2 USE && TERM 2 RESTORE
	t_termios			term;
	t_termios			restore;
		// TERMCAPS CMD
	t_dlist2			*cmd_termcaps;
	t_dlist2			*pcmd_t;
	t_dlist2			*p_mark;
	int					pcmd_i;
	int					current_key;
	char				*buff;
		// AUTOCOMPLETE
	t_clist				*list_dir;
	t_select			*nav_dir;
	t_winsize			ws;
	t_stat				stat;
	char				*tmp_cmd;
	char				*tmp_dir;
	char				*equ2find;
	int					already_autocomplete;
	int					already_open;
	int					replace_cursor;
	int					maxlen_arg;
	int					files_by_row;
		// HORIZONTAL MOVES
	int					cursor_pos;
	int					history_moves;
	int					already_in_moves;
		// VERTICAL MOVES
	int					nb_lines;
	int					curr_line;
	int					max_rows;
	int					curr_row;
	int					up_count;
		// HISTORY
	char				**history_buff;
	int					fd_history;
	int					pos_history;
	int					index_history;
	int					lines2del;

	t_dlist				*cmd_history;
	int					already_in_history;
	int					is_history;
		// COPY & PASTE & CUT
	int					already_in_select;
			// --COPY
	int					save_cursor_pos;
	int					cpy_move_right;
	int					cpy_move_left;
			// --PASTE
	char				*copy;
	int					already_in_paste;
			// --READ
	t_var				*local_var;
	int					query;
	size_t				max_len;
		// PARSE && EXEC
	t_dlist				*env;
	t_node				*nav;
	char				**dupenv;
	char				**path2exec;
	char				**parsecmd;
	char				**pipe;
	char				*oldpwd;
	char				*cmd;
		// AGGREGATIONS
	char				**cmd_array;
	char				*agg2split;
	char				*file;
	char				agg;
		// PIPES & REDIRECTIONS
	char				*file2redir;
	int					redir_in_pipe;
		//
	int					fd2open;
	int					stop;
	int					skip;
	int					inpipe;
	int					inredir;
	int					fd2restore;
		// --SOSO
	int					lv;
}						t_all;

typedef	struct			s_redirect
{
	char				*action_name;
	void				(*f)(t_all *, char *);
}						t_redirect;

typedef	struct			s_keys
{
	int					action_name;
	void				(*f)(t_all *);
}						t_keys;

/* ----------------------------------------------------------------------
*** ============================================================ BUILTINS
*/
	/*
	*** ======================= builtins.c
	*/
	void		pwd_display(t_all *all, char *cmd);
	void		goto_dir(t_all *all, char *cmd);
	void		free_all(t_all *all, char *cmd);
	void		built_history(t_all *all, char *cmd);
	void		built_mark(t_all *all, char *cmd);
	void		read_built(t_all *all, char *cmd);
	void		find_lv(t_all *all, int lv);
	void		built_echo(t_all *all, char *cmd);
	/*
	*** ======================= builtins_tools.c
	*/
	void		update_oldpwd(t_all *all);

#endif