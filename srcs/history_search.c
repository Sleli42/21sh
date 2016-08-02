/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_search.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/25 07:55:52 by lubaujar          #+#    #+#             */
/*   Updated: 2016/07/25 07:55:54 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

void	display_search_histo_prompt(t_all *all)
{
	if (all->cmd && all->cmd_termcaps->lenght != 0)
	{
		all->histo_prompt = ft_strjoin("(histo-search) [", all->cmd);
		all->histo_prompt = ft_strjoin(all->histo_prompt, "]: ");
	}
	else
	{
		all->histo_prompt = ft_strjoin("(histo-search) [", "\0");
		all->histo_prompt = ft_strjoin(all->histo_prompt, "]: ");
	}
	ft_putstr(all->histo_prompt);
	CURSOR = ft_strlen(all->histo_prompt) - 1;
	CURSOR += (all->cmd) ? (int)ft_strlen(all->cmd) : 0;
	CURSOR += (CURSOR - PROMPT_LEN == -1) ? 1 : 0;
}

void	search_match_history_file(t_all *all)
{
	int		ct;
	int		match;
	int		stop;

	ct = 0;
	match = 0;
	stop = ft_tablen(all->history_buff);
	while (all->cmd && all->history_buff[ct] && ct < stop)
	{
		if (!ft_strncmp(skip_index(all->history_buff[ct]), all->cmd,\
										ft_strlen(all->cmd)))
		{
			(all->histo_match_tmp) ? ft_strdel(&all->histo_match_tmp) : NULL;
			all->histo_match_tmp = ft_strdup(skip_index(all->history_buff[ct]));
			ft_putstr(all->histo_match_tmp);
			match = 1;
			break ;
		}
		ct++;
	}
	if (!match)
		return (ft_putstr("No match !"));
}

void	update_search_line(t_all *all)
{
	create_cmd(all);
	refresh_line(all);
	display_search_histo_prompt(all);
	if (all->cmd && ft_strlen(all->cmd) > 1)
		search_match_history_file(all);
	CURSOR += (all->cmd) ? (int)ft_strlen(all->cmd) - 1 : 0;
}

void	init_search(t_all *all)
{
	if (!all->cmd_search_tmp)
		all->cmd_search_tmp = all->cmd_termcaps;
	all->already_in_search = 1;
	all->histo_match_tmp = NULL;
	!CMD_NULL ? del_dlist2(all->cmd_termcaps) : NULL;
	all->cmd_termcaps = create_cmd_dlst();
	all->cmd || *all->cmd ? ft_strdel(&all->cmd) : NULL;
	all->cmd = !all->cmd ? ft_strnew(MAXLEN - 1) : NULL;
	all->buff = ft_memset(ft_strnew(MAXLEN - 1), 0, (MAXLEN - 1));
}

void	search_history(t_all *all)
{
	init_search(all);
	refresh_line(all);
	create_cmd(all);
	display_search_histo_prompt(all);
	while (*all->buff != '\n')
	{
		if (!read_keys_search(all))
			break ;
	}
	ft_strdel(&all->histo_prompt);
	ft_strdel(&all->prompt);
	all->prompt = ft_strdup("$: ");
	if (!CMD_NULL)
	{
		realloc_termcaps_cmd(all, all->histo_match_tmp);
		create_and_exec_command(all);
	}
}
