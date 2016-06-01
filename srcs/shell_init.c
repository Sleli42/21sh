/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/04 10:40:48 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/21 16:29:44 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

void		init_loop(t_all *all)
{
	all->stop = 0;
	all->already_in_select = 0;
	all->already_in_paste = 0;
	all->cursor_pos = 0;
	all->nb_lines = 1;
	all->curr_line = 1;
	all->index_history = all->pos_history;
	all->cmd_termcaps = all->p_mark ? all->p_mark : create_cmd_dlst();
	all->pcmd_t = NULL;
	all->pcmd_i = 0;
	all->cmd ? ft_strdel(&all->cmd) : NULL;
	all->buff = ft_memset(ft_strnew(MAXLEN - 1), 0, (MAXLEN - 1));
	all->prog_exec = 0;
	all->env_exec = all->dupenv;
	init_windows_size(all);
}

void		init_history(t_all *all)
{
	char	buf[512];

	all->history_path = NULL;
	if ((all->fd_history = open(".21sh_history", \
				O_WRONLY | O_CREAT | O_APPEND, 0644)) == -1)
		write(1, "open error\n", 11);
	all->history_path = ft_strjoin(getcwd(buf, 512), "/.21sh_history");
	all->history_buff = parse_history(all);
	all->pos_history = check_history_file(all->history_buff);
}

void		init_read(t_all *all)
{
	all->p_mark = NULL;
	all->local_var = NULL;
	all->query = 0;
	all->max_len = 0;
}

void		init_glob(t_all *all)
{
	t_glob	*g;

	g = &all->globing;
	g->sub = 0x0;
	g->crush = 0x0;
	g->c_indx = 0x0;
	g->quote = 0x0;
	g->d_quote = 0x0;
	g->back = 0x0;
	g->esc_mem = 0x0;
	g->err = NULL;
	g->dt_print = 0x0;
	g->cr_split = 0x0;
}

t_all		*init_all(char **env)
{
	t_all	*all;
	int		i;

	i = 0;
	if (!(all = (t_all *)malloc(sizeof(t_all))))
		error("MALLOC");
	init_windows_size(all);
	all->env = init_env(env);
	all->dupenv = ft_dupenv(all->env);
	all->path2exec = ft_strsplit(find_env_arg(all, "PATH") + 5, ':');
	all->parsecmd = NULL;
	all->pipe = NULL;
	all->nav = NULL;
	all->tmp_cmd = NULL;
	all->already_autocomplete = 0;
	all->already_open = 0;
	all->hash = malloc(sizeof(char *) * 250);
	while (i < 250)
		all->hash[i++] = 0;
	init_history(all);
	init_read(all);
	init_glob(all);
	return (all);
}
