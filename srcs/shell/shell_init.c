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

t_all		*init_all(char **env)
{
	t_all	*all;

	if (!(all = (t_all *)malloc(sizeof(t_all))))
		error("MALLOC");
	//catch_sig();
	//init_termios(all->term);
	init_windows_size(all);
	all->env = init_env(env);
	all->dupenv = ft_dupenv(env);
	all->cmd_history = create_dlst();
	// all->cmd = create_cmd_dlst();
	all->path2exec = ft_strsplit(find_env_arg(all, "PATH") + 5, ':');
	all->parsecmd = NULL;
	all->pipe = NULL;
	all->nav = NULL;
		// --HISTORY
	// if ((all->fd2open = open(redirect[1], O_WRONLY | O_CREAT | O_APPEND, 0644)) == -1)
	if ((all->fd_history = open(".21sh_history", O_WRONLY | O_CREAT | O_APPEND, 0644)) == -1)
		write(1, "open error\n", 11);
	all->history_buff = parse_history();
	all->pos_history = check_history_file(all->history_buff);
	all->tmp_cmd = NULL;
	all->line2write = 1;
	all->already_autocomplete = 0;
	// all->file_history = ft_strdup(".21sh_history");
	return (all);
}

// void		fct_sig(int sig)
// {
// 	if (sig == SIGINT || sig == SIGCONT)
// 		display_prompt(f_cpy(NULL));
// 	else
// 		exit(0);
// }

// static void		catch_sig(void)
// {
// 	signal(SIGINT, fct_sig);
// 	signal(SIGCONT, fct_sig);
// }