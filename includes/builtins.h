/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 15:46:53 by skhatir           #+#    #+#             */
/*   Updated: 2016/05/24 16:28:30 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "full_sh.h"
# include <limits.h>
# include <time.h>
# include <sys/types.h>
# include <fcntl.h>

typedef struct s_all	t_all;
typedef struct s_cmd	t_cmd;

/*
********************************************************************************
*********************** LOCAL_VAR **********************************************
*/

typedef struct			s_var
{
	char				*var_name;
	char				*content;
	struct s_var		*prev;
	struct s_var		*next;
}						t_var;

typedef struct			s_flv
{
	int					ct;
	char				*new_s;
	char				*tmp;
	char				*tmp2;
	char				*tmp3;
	char				*p2;
	char				**env_var;
	t_cmd				*nav;
}						t_flv;

void					find_lv(t_all *all);
char					*var_env(char *target);
int						var_len(char *var);
int						is_array_lv(char a);
void					init_fbox(t_flv *fbox, t_all *all, char *p);

/*
********************************************************************************
*********************** READ ***************************************************
*/

# define RD_OP			"-ersutpand"
# define DB(x, y)		((0x1 << x) | y)
# define CMP(x, y)		(x & (1 << y))
# define FORMAT_ERR		"read [-ers] [-u fd] [-t timeout] [-p prompt] "
# define FORMAT_ERR2	"[-a array] [-n nchars] [-d delim] [name ...]\n"
# define FD_ERR			"read -u: bad file descriptor. Usage: [-u [0-255]]"
# define TIME_ERR		"read -t: bad time. Usage [-t [value > 0]]"
# define CMD_TAB		all->r_box.cmd_tab
# define TIME_CTRL(x)	(x > 0 ? x : 1)
# define BAD_FORMAT		-1
# define BAD_FD			-2
# define BAD_TIME		-3
# define RD_KILL		-2
# define CURENT_PID		-42
# define LAST_PID		-41

typedef struct			s_read
{
	char				delim;
	int					fd;
	int					timeout;
	int					check_time;
	struct timeval		time_set;
	fd_set				set;
	int					rdy;
	size_t				nchars;
	char				*prompt;
	int					a;
	char				*a_name;
	char				*full_string;
	char				**array;
	char				glob;
	int					err;
	int					opt;
	char				**cmd_tab;
	char				**var_tab;
}						t_read;

typedef struct			s_rmisc
{
	int					breakpoint;
	char				*stock;
	char				*tmp;
}						t_misk;

/*
*** --------			INIT & ERR --------------------------------|
*/

void					init_rbox(t_all *all);
t_var					*init_caps(void);
int						dft_reply(char ***cmd_tab);
int						check_requiere(int f, \
										char **cmd_tab, int i, t_all *all);
void					read_line_err(int err, int *r_err);

/*
*** --------			GET & FILL VARIABLE -----------------------|
*/

void					creat_var(t_all *all, char *var, char *in);
char					*implode(char **var_tab, int index);
int						read_ct(char **cmd_tab, int *opt, t_all *all);
void					get_var(t_read *r_box, t_all *all, int fd);
void					get_opt(char **cmd_tab, int *opt, t_all *all);
int						get_char(t_all *all, t_read *r_box, int fd, char **s);
void					read_built(t_all *all, char *cmd);

/*
*** --------			read_(*f)_table ---------------------------|
*/

int						ft_u(t_all *all, char *n);
int						ft_t(t_all *all, char *n);
int						ft_p(t_all *all, char *n);
int						ft_a(t_all *all, char *n);
int						ft_n(t_all *all, char *n);
int						ft_d(t_all *all, char *n);
int						ft_ft(t_all *all, int f, char *next_cm);

/*
*** --------			ARRAY -------------------------------------|
*/

char					*format_array(char *name, int index, char ck);
char					**do_array(char **cmd_tab, char **var_tab, t_all *all);
void					fill_array(t_all *all, char **cmd_tab, char **var_tab);

/*
*** --------			MISC --------------------------------------|
*/

void					ft_tabdel(char ***tabi);

/*
********************************************************************************
*********************** MARK_BUILT *********************************************
*/

# define _M (m_box.history && *m_box.history && m_box.history[m_box.p_index])

typedef struct			s_mark
{
	int					params;
	int					p_index;
	char				*p_cmd;
	char				**history;
}						t_mark;

char					*first_cmd(char *cmd);
int						get_arg(char *p_cmd);
int						get_index(char *p_cmd);
char					*obtain_history_p(char *history);
void					join_params(char **p_cmd, char *orig_cmd);
void					built_mark(t_all *all, char *cmd);

/*
********************************************************************************
*********************** ECHO ***************************************************
*/

void					built_echo(t_all *all, char *cmd);

/*
********************************************************************************
*********************** HISTORY ************************************************
*/

void					built_history(t_all *all, char *cmd);

/*
********************************************************************************
*********************** CD *****************************************************
*/

void					goto_dir(t_all *all, char *cmd);
void					update_oldpwd(t_all *all);

/*
********************************************************************************
*********************** ENV ****************************************************
*/

#include "env.h"

typedef struct			s_env_info
{
	int					exec;
	int					unless;
	int					len;
	char				*bin;
	char				**env_spe;
	char				**set_var;
}						t_env_info;


char					**ft_tabdelone(char **array, char *s);
char					*dup_comp(char *target, char **array);
char					**ft_tabjoin(char **dupenv, char **env_spe);
void					ft_printtab(char **array);
void					init_inf(t_env_info *inf);

/*
********************************************************************************
*********************** MSC ****************************************************
*/

void					free_all(t_all *all, char *cmd);
void					pwd_display(t_all *all, char *cmd);

#endif
