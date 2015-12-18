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

# define 	NOTATTY 	1

typedef struct dirent	t_dirent;
typedef struct termios	t_termios;
typedef struct winsize	t_winsize;

typedef struct			s_node
{
	char				*s;
	size_t				index;
	struct s_node		*next;
	struct s_node		*prev;
}						t_node;

typedef struct			s_dlist
{
	struct s_node		*head_node;
	struct s_node		*tail_node;
	size_t				lenght;
}						t_dlist;

typedef struct			s_cmd
{
	char				c;
	size_t				pos;
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

typedef struct			s_all
{
	// TERM 2 USE && TERM 2 RESTORE
	t_termios			term;
	t_termios			restore;
	// HISTORY
	t_dlist				*cmd_history;
	int					already_in_history;
	int					is_history;
	// TERMCAPS CMD
	t_dlist2			*cmd_termcaps;
		// --AUTOCOMPLETE
	t_clist				*list_dir;
	t_select			*nav_dir;
	t_winsize			ws;
	int					maxlen_arg;
	int					files_by_row;
	int					already_open;
	int					nb_char_write;
	int					ct_select;
		// --HORIZONTAL MOVES
	int					cursor_pos;
	int					history_moves;
	int					already_in_moves;
	// PARSE && EXEC
	t_dlist				*env;
	t_node				*nav;
	char				**dupenv;
	char				**path2exec;
	char				**parsecmd;
	char				**pipe;
	char				*oldpwd;
	char				*cmd;
	char				*current;
	int					fd2open;
	int					stop;
}						t_all;

typedef	struct			s_redirect
{
	char				*action_name;
	void				(*f)(t_all *, char *);
}						t_redirect;

typedef	struct			s_builtins
{
	char				*action_name;
	void				(*f)(t_all *, char *);
}						t_builtins;

/*
*** ============================================================ main.c
*/
void	display_dlst2(t_dlist2 *lst);

void	update_cmd_line_insert(t_all *all, char char2add);
void	realloc_termcaps_cmd(t_all *all, char *cmd2realloc);
void		create_cmd(t_all *all);
void		display_prompt(t_all *all);
void		loop(t_all *all);
/*
*** ============================================================ init.c
*/
char		**ft_dupenv(char **env);
t_dlist		*init_env(char **env);
int			init_tty(void);
void		init_windows_size(t_all *all);
void		init_term(void);
void 		reset_term(void);
t_all		*init_all(char **env);
/*
*** ============================================================ error.c
*/
void		error(char *err);
void		term_error(char *err);
/*
*** ============================================================ dlist.c
*/
t_dlist		*create_dlst(void);
t_node		*dlst_node_new(char *data, size_t index);
t_dlist		*dlst_add_back(t_dlist *lst, t_node *node);
t_dlist		*dlst_del_one(t_dlist *lst, char *arg2del);
int			len_lst_node(t_node *lst);
int			update_list(t_dlist *lst, t_node *elem);
void		del_dlist(t_dlist *lst);
/*
*** ============================================================ dlist_2.c
*/
t_dlist2	*create_cmd_dlst(void);
t_cmd		*dlst_cmd_new(char c, size_t pos);
t_dlist2	*dlst_insert_cmd(t_dlist2 *lst, t_cmd *node, int pos);
t_dlist2	*dlst_add_back_2(t_dlist2 *lst, t_cmd *node);
int			len_lst_cmd(t_cmd *lst);
t_dlist2	*dlst_del_one2(t_dlist2 *lst, char arg2del);
int			update_list2(t_dlist2 *lst, t_cmd *elem);
void		del_dlist2(t_dlist2 *lst);
/*
*** ============================================================ clist.c
*/
t_clist		*create_clst(void);
t_select	*clst_create_elem(char *s);
t_clist		*clst_add_elem_back(t_clist *lst, t_select *node);
int			len_clst(t_select *lst);
void		del_clist(t_clist **lst);
/*
*** ============================================================= env.c
*/
void		env_display(t_all *all, char *cmd);
void		env_set(t_all *all, char *cmd);
void		env_unset(t_all *all, char *cmd);
/*
*** ============================================================ tools.c
*/
char		*find_env_arg(t_all *all, char *arg2find);
void		update_oldpwd(t_all *all);
void		add_missing_char_to_cmd(t_all *all, char *s);
void		add_to_cmd(t_all *all, char *s);
int			find_maxlen_elem(t_clist *lst);
int			all_is_spaces(t_cmd *cmd);
char		goto_elem(t_cmd *cmd, int pos);
/*
*** ============================================================ binary_tools.c
*/
int			good_access(char *bin);
char		*create_path(char *path, char *bin);
void		exec_right_binary(t_all *all, char **argv_bin);
void		exec_binary(char *bin, char **argv_bin, char **env);
/*
*** ============================================================ cmd_parse.c
*/
void		parse_command(t_all *all, char *buff);
int			check_redirection(char *s);
/*
*** ============================================================ cmd_exec.c
*/
void		exec_simple_cmd(t_all *all, char *cmd);
void		exec_redirection_cmd(t_all *all, char *cmd);
void		exec_command(t_all *all);
/*
*** ============================================================ builtins.c
*/
void		pwd_display(t_all *all, char *cmd);
void		goto_dir(t_all *all, char *cmd);
void		free_all(t_all *all, char *cmd);
/*
*** ============================================================ redirection.c
*/
void		dup_and_exec(t_all *all, char **argv, int fd2back, int fd2dup);
void		erase_and_replace(t_all *all, char *cmd);
void		add_to_end(t_all *all, char *cmd);
void		read_file(t_all *all, char *cmd);
void		read_stdin(t_all *all, char *cmd);
/*
*** ============================================================ pipe.c
*/
char		*create_good_path(t_all *all, char *cmd);
void		create_pipe(t_all *all, char *cmd);
void		exec_pipe_process(t_all *all, char *cmd, char **args);
int			open_file(char *file, int redir);
void		exec_redirect(t_all *all, char *cmd, char **args, char *file, int redir);
/*
*** ============================================================ termcaps.c
*/
t_all		*f_cpy(t_all *all);
int			lu_putchar(int c);
void		tputs_termcap(char *tc);
void		move_cursor(char *buff, char *cmd, int *i);
void		restore_term(t_termios restore);
/*
*** ============================================================ history.c
*/
void		display_dlst_history(t_dlist *lst);
char		*display_last_cmd(t_dlist *lst, size_t pos);
void		new_line(t_all *all);
void		goto_latest_commands(t_all *all, char buff[3]);
/*
*** ============================================================ moves.c
*/
int			check_keys_arrows(t_all *all, char buff[3]);
void		make_moves(t_all *all, char buff[3]);
/*
*** ============================================================ autocomplete.c
*/
int			define_nb_files_by_row(t_all *all, t_clist *lst);
char		*find_path(char *cmd);
char		*search_equ(char *dir);
void		swap_elems(t_select *a, t_select *b);
void		sort_name(t_select **lst);
void		list_elems(t_all *all, DIR *entry);
void		new_line_autocomplet(t_all *all);
void		display_current(t_all *all, t_select *nav);
void		open_directory(t_all *all);

#endif