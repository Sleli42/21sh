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
	all->histo_prompt = ft_strjoin("(histo-search) [", all->cmd);
	all->histo_prompt = ft_strjoin(all->histo_prompt, "]: ");
	// ft_putstr("(histo-search) [");
	// (all->cmd) ? ft_putstr(all->cmd) : NULL;
	// ft_putstr("]: ");
	ft_putstr(all->histo_prompt);
	CURSOR = ft_strlen(all->histo_prompt) - 1;
	CURSOR += (all->cmd) ? (int)ft_strlen(all->cmd) : 0;
}

void	refresh_line(t_all *all)
{
	int		save;

	get_cursor_row(all);
	all->lines2del = count_lines_2del(all);
	save = 1;
	tputs_termcap("up");
	tputs_termcap("do");
	if (save < all->lines2del)
	{
		while (save++ < all->lines2del)
		{
			tputs_termcap("ce");
			tputs_termcap("cb");
			tputs_termcap("up");
		}
	}
	else
	{
		tputs_termcap("cb");
		tputs_termcap("ce");
	}
	// while (CURSOR > 0)
	// 	tputs_termcap("le");
	// printf("CURSOR: %d\n", CURSOR);
}

void	update_search_line(t_all *all)
{
	create_cmd(all);
	refresh_line(all);
	display_search_histo_prompt(all);
	CURSOR += (all->cmd) ? (int)ft_strlen(all->cmd) - 1 : 0;
	ft_putstr(all->cmd);
}

void	init_search(t_all *all)
{
	if (!all->cmd_search_tmp)
		all->cmd_search_tmp = all->cmd_termcaps;
	all->already_in_search = 1;
	!CMD_NULL ? del_dlist2(all->cmd_termcaps) : NULL;
	all->cmd_termcaps = create_cmd_dlst();
	all->cmd || *all->cmd ? ft_strdel(&all->cmd) : NULL;
	all->cmd = !all->cmd ? ft_strnew(MAXLEN - 1) : NULL;
	all->buff = ft_memset(ft_strnew(MAXLEN - 1), 0, (MAXLEN - 1));
}

int		read_keys_search(t_all *all)
{
	int		key;

	key = 0;
	if (read(0, all->buff, (MAXLEN - 1)) == -1)
		return (0);
	if (*all->buff == 4)
		control_d(all);
	else if ((key = check_keys_arrows(all, all->buff)) < 0)
		return (0);
	else if (key > 0)
	{
		// ft_putstr("yes\n");
		parse_keys(all);
	}
	else if (check_str(all->buff))
	{
		insert_char(all);
		update_search_line(all);
	}
	return (1);
}

void	search_history(t_all *all)
{
	init_search(all);
	refresh_line(all);
	display_search_histo_prompt(all);
	create_cmd(all);
	while (*all->buff != '\n')
	{
		// define_nb_lines(all);
		if (!read_keys_search(all))
			break ;
	}
	if (!CMD_NULL)
		del_dlist2(all->cmd_termcaps);
	ft_strdel(&all->histo_prompt);
	ft_strdel(&all->prompt);
	all->prompt = ft_strdup("$: ");
	// printf("goto search history match\n");
}
