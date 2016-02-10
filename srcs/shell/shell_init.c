/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/04 10:40:48 by lubaujar          #+#    #+#             */
/*   Updated: 2016/01/04 10:40:49 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void		init_history(t_all *all)
{
	if ((all->fd_history = open(".21sh_history", \
				O_WRONLY | O_CREAT | O_APPEND, 0644)) == -1)
		write(1, "open error\n", 11);
	all->history_buff = parse_history();
	all->pos_history = check_history_file(all->history_buff);
}

void		init_read(t_all *all)
{
	all->p_mark = NULL;
	all->local_var = NULL;
	all->query = 0;
	all->max_len = 0;
}

t_all		*init_all(char **env)
{
	t_all	*all;

	if (!(all = (t_all *)malloc(sizeof(t_all))))
		error("MALLOC");
	init_windows_size(all);
	all->env = init_env(env);
	all->dupenv = ft_dupenv(env);
	all->path2exec = ft_strsplit(find_env_arg(all, "PATH") + 5, ':');
	all->parsecmd = NULL;
	all->pipe = NULL;
	all->nav = NULL;
	all->tmp_cmd = NULL;
	all->line2write = 1;
	all->already_autocomplete = 0;
	all->already_open = 0;
	init_history(all);
	init_read(all);
	return (all);
}
