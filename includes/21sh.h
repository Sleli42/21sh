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

# define	MAXLEN		4096

typedef struct			s_node
{
	char				*s;
	struct s_node		*next;
	struct s_node		*prev;
}						t_node;

typedef struct			s_dlist
{
	struct s_node		*head;
	struct s_node		*tail;
	size_t				lenght;
}						t_dlist;

typedef struct			s_all
{
	t_dlist				*env;
	char				**parsecmd;
	char				**dupenv;
}						t_all;

typedef	struct			s_redirect
{
	char				*action_name;
	void				(*f)(char *);
}						t_redirect;

typedef	struct			s_builtins
{
	char				*action_name;
	void				(*f)(t_all *);
}						t_builtins;

/*
*** ============================================================ main.c
*/
void		loop(t_all *all);
/*
*** ============================================================ init.c
*/
char		**ft_dupenv(char **env);
t_dlist		*init_env(char **env);
t_all		*init_all(char **env);
/*
*** ============================================================ error.c
*/
void		error(char *err);
/*
*** ============================================================ dlist.c
*/
t_dlist		*create_dlst(void);
t_node		*dlst_new(char *data);
t_dlist		*dlst_add_back(t_dlist *lst, t_node *node);
t_dlist		*dlst_del_one(t_dlist *lst, char *arg2del);
int			update_list(t_dlist *lst, t_node *elem);
/*
*** ============================================================= env.c
*/
void		env_display(t_all *all);
void		env_set(t_all *all);
void		env_unset(t_all *all);
/*
*** ============================================================ tools.c
*/
char		*find_env_arg(t_all *all, char *arg2find);
/*
*** ============================================================ parse_cmd.c
*/
void		exec_command(char **cmd);
void		parse_command(t_all *all, char *buff);
int			check_redirection(char *s);
/*
*** ============================================================ builtins.c
*/
void		pwd_display(t_all *all);
void		goto_dir(t_all *all);
void		free_all(t_all *all);
/*
*** ============================================================ redirection.c
*/
void		dup_and_exec(char **argv, int fd2open, int fd2back, int fd2dup);
void		erase_and_replace(char *cmd);
void		add_to_end(char *cmd);
void		read_file(char *cmd);
void		read_stdin(char *cmd);

#endif