/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 12:33:17 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/21 16:06:46 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

char	**parse_history(t_all *all)
{
	t_hist	msc;
	char	**ret;
	char	buff[MAXLEN];

	if ((msc.fd = open(all->history_path, O_RDONLY)) == -1)
		error("OPEN");
	ret = NULL;
	msc.stock = NULL;
	while ((msc.r = read(msc.fd, buff, (MAXLEN - 1))) > 0)
	{
		msc.tmp = NULL;
		buff[msc.r] = 0;
		msc.tmp = ft_strjoin(msc.stock, buff);
		msc.stock = ft_strdup(msc.tmp);
		ft_strdel(&msc.tmp);
	}
	ret = msc.stock ? ft_strsplit(msc.stock, '\n') : NULL;
	msc.stock ? ft_strdel(&msc.stock) : NULL;
	close(msc.fd);
	return (ret);
}

void	add_to_history(t_all *all)
{
	char	*history_line;
	char	*tmp;
	int		ct;
	int		i;

	history_line = ft_strnew(all->cmd_termcaps->lenght + 1);
	tmp = ft_itoa(all->pos_history++);
	ct = 0;
	i = 0;
	while (tmp && tmp[i])
		history_line[ct++] = tmp[i++];
	(tmp) ? ft_strdel(&tmp) : NULL;
	history_line[ct++] = ':';
	i = 0;
	!all->cmd ? create_cmd(all) : NULL;
	while (all->cmd[i])
		history_line[ct++] = all->cmd[i++];
	history_line[ct] = '\0';
	write(all->fd_history, history_line, ft_strlen(history_line));
	write(all->fd_history, "\n", 1);
	(history_line && *history_line) ? ft_strdel(&history_line) : NULL;
}

void	display_index_cmd(t_all *all)
{
	int		ct;
	char	*tmp;

	ct = 0;
	tmp = NULL;
	if (all->history_buff)
		del_array(&all->history_buff);
	if ((all->history_buff = parse_history(all)) == NULL)
		return (init_history(all));
	if (!check_history_file(all->history_buff))
		return (ft_putstr("no history"));
	while (all->history_buff[all->index_history - 1][ct] != ':')
		ct++;
	tmp = ft_strdup(all->history_buff[all->index_history - 1] + (ct + 1));
	realloc_termcaps_cmd(all, tmp);
	ft_putstr(tmp);
}

int		check_history_file(char **histo)
{
	int		ret;

	ret = histo && *histo ? ft_tablen(histo) : 0;
	return (ret + 1);
}

int		count_lines_2del(t_all *all)
{
	int		ret;

	ret = 1;
	while (CURSOR > ret * LINE_LEN)
		ret++;
	return (ret);
}
