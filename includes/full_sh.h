/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full_sh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 15:48:53 by skhatir           #+#    #+#             */
/*   Updated: 2016/05/24 17:57:07 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FULL_SH_H
# define FULL_SH_H

# include <stdlib.h>
# include <unistd.h>
# include <libft.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <term.h>
# include <termios.h>
# include <curses.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include "arrows_and_movements.h"
# include "autocomplete.h"
# include "colors.h"
# include "env.h"
# include "exec_binary.h"
# include "history.h"
# include "lists.h"
# include "builtins.h"
# include "redirect.h"
# include "shell.h"
# include "termcaps.h"

/*
********	DEFINE	 ***********************************************************
*/

# define MAXLEN			4096
# define K_UP			279165000
# define K_CTRL_UP		-23278475
# define K_DOWN			279166000
# define K_CTRL_DOWN	-23278474
# define K_RIGHT		279167000
# define K_CTRL_RIGHT	-23278473
# define K_LEFT			279168000
# define K_CTRL_LEFT	-23278472
# define K_ECHAP		2700000
# define K_BACKSPACE	12700000
# define K_DELETE		2145308824
# define K_ENTER		1000000
# define K_TAB			900000
# define K_HOME			279172000
# define K_END			279170000
# define K_CTRL_CLEAR	-7040000
# define K_CTRL_COPY	-6990000
# define K_CTRL_PASTE	-4302000
# define K_CTRL_CUT		-4310000
# define NOTATTY 		1
# define PROMPT_LEN		3
# define LINE_LEN		all->ws.ws_col
# define CURSOR			all->cursor_pos
# define CMD_T			all->cmd_termcaps
# define CMD_NULL		(!CMD_T || !CMD_T->head || !CMD_T->head->c)
# define SPLIT_T		" ;&<>()=|*/{}\"\'`\n"
# define GLOB			"\"\'\\{}()[]"

/*
********	TYPEDEF/STRUCT	****************************************************
*/

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
	int					onarg;
	struct s_select		*next;
	struct s_select		*prev;
}						t_select;

typedef struct			s_clist
{
	struct s_select		*head;
	struct s_select		*tail;
	size_t				lenght;
}						t_clist;

typedef struct			s_glob
{
	int					sub;
	int					crush;
	int					c_indx;
	int					quote;
	int					d_quote;
	int					back;
	char				*err;
	int					esc_mem;
	int					dt_print;
	int					cr_split;
}						t_glob;

/*
********	ALL_BOX		********************************************************
*/

typedef struct			s_all
{
	t_termios			term;
	t_termios			restore;
	t_dlist2			*cmd_termcaps;
	t_dlist2			*pcmd_t;
	t_dlist2			*p_mark;
	int					pcmd_i;
	int					current_key;
	char				*buff;
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
	int					cursor_pos;
	int					history_moves;
	int					already_in_moves;
	int					nb_lines;
	int					curr_line;
	int					max_rows;
	int					curr_row;
	int					up_count;
	char				**history_buff;
	int					fd_history;
	int					pos_history;
	int					index_history;
	int					lines2del;
	char				*history_path;
	t_dlist				*cmd_history;
	int					already_in_history;
	int					is_history;
	int					already_in_select;
	int					save_cursor_pos;
	int					cpy_move_right;
	int					cpy_move_left;
	char				*copy;
	int					already_in_paste;
	int					lv;
	t_var				*local_var;
	int					query;
	size_t				max_len;
	t_read				r_box;
	t_dlist				*env;
	t_node				*nav;
	char				**dupenv;
	char				*tmp_var_env;
	char				**path2exec;
	char				***parsecmd;
	char				**pipe;
	int					nb_pipe;
	char				*oldpwd;
	char				*cmd;
	char				**cmd_array;
	char				*agg2split;
	char				*file;
	char				agg;
	char				*file2redir;
	int					redir_in_pipe;
	int					fd2open;
	int					stop;
	int					skip;
	int					dupout;
	int					duperr;
	int					fd2restore;
	t_glob				globing;
	char				**hash;
	int					nb_bin_ope;
	int					err_exec;
	int					save_curs;
	int					prog_exec;
	char				**env_exec;
}						t_all;

/*
********	FT_TABLE	********************************************************
*/

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

void					sig_handler(int sig);
void					sig_catch(void);
void					init_dft(t_all *all);

#endif
