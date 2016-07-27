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
	// printf("all->cmd: |%s|\n", all->cmd);
	if (all->cmd && all->cmd_termcaps->lenght != 0)
	{
		all->histo_prompt = ft_strjoin("(histo-search) [", all->cmd);
		all->histo_prompt = ft_strjoin(all->histo_prompt, "]: ");
	}
	else
	{
		all->histo_prompt = ft_strjoin("(histo-search) [", "\0");
		all->histo_prompt = ft_strjoin(all->histo_prompt, "]: ");
		// printf("CURSOR-PROMPT: %d\n", CURSOR - PROMPT_LEN);
		// del_dlist2(all->cmd_termcaps);
		// all->cmd_termcaps = create_cmd_dlst();
	}
	// ft_putstr("(histo-search) [");
	// (all->cmd) ? ft_putstr(all->cmd) : NULL;
	// ft_putstr("]: ");
	ft_putstr(all->histo_prompt);
	CURSOR = ft_strlen(all->histo_prompt) - 1;
	CURSOR += (all->cmd) ? (int)ft_strlen(all->cmd) : 0;
	CURSOR += (CURSOR - PROMPT_LEN == -1) ? 1 : 0;
	// printf("CURSOR: %d\n", CURSOR);
	// printf("CURSOR-PROMPT: %d\n", CURSOR - PROMPT_LEN);
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

char	*skip_index(char *s)
{
	if (!s)
		return (NULL);
	while (s && *s)
	{
		if (*s == ':')
		{
			s++;
			// printf("s: |%s|\n", s);
			break ;
		}
		s++;
	}
	return (s);
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
		return ;
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

int			check_keys_arrows_histo(t_all *all, char *buff)
{
	all->current_key = getkey(buff);
	if (all->current_key == K_ENTER)
		return (down_line(all));
	if (all->current_key == K_BACKSPACE)
		return (1);
	return (0);
}

void		key_loop_histo(t_all *all, const t_keys keys[2])
{
	int		i;

	i = 0;
	while (i < 2)
	{
		if (all->current_key == keys[i].action_name)
		{
			keys[i].f(all);
			return ;
		}
		i++;
	}
}

void		parse_keys_histo(t_all *all)
{
	static const	t_keys	keys[] =
	{{K_BACKSPACE, del_char},
	{K_DELETE, del_char}};

	key_loop_histo(all, keys);
}

int		read_keys_search(t_all *all)
{
	int		key;

	key = 0;
	if (read(0, all->buff, (MAXLEN - 1)) == -1)
		return (0);
	if (*all->buff == 4)
		control_d(all);
	else if ((key = check_keys_arrows_histo(all, all->buff)) < 0)
		return (0);
	else if (key > 0)
	{
		(all->prompt) ? ft_strdel(&all->prompt) : NULL;
		all->prompt = ft_strdup(all->histo_prompt);
		parse_keys_histo(all);
	}
	else if (check_str(all->buff))
		insert_char(all);
	return (1);
}

void	search_history(t_all *all)
{
	init_search(all);
	refresh_line(all);
	create_cmd(all);
	display_search_histo_prompt(all);
	while (*all->buff != '\n')
	{
		// define_nb_lines(all);
		if (!read_keys_search(all))
			break ;
	}
	ft_strdel(&all->histo_prompt);
	ft_strdel(&all->prompt);
	all->prompt = ft_strdup("$: ");
	if (!CMD_NULL)
	{
		realloc_termcaps_cmd(all, all->histo_match_tmp);
		// printf("cmd: |%s|\n", all->cmd);
		// ft_putstr("yes\n");
		// (all->cmd) ? ft_strdel(&all->cmd) : NULL;
		// all->cmd = ft_strdup(all->histo_match_tmp);
		// printf("histo: |%s|\n", all->histo_match_tmp);
		// printf("cmd: |%s|\n", all->cmd);
		create_and_exec_command(all);
		// del_dlist2(all->cmd_termcaps);
	}
	// printf("goto search history match\n");
}
