/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 12:33:17 by lubaujar          #+#    #+#             */
/*   Updated: 2016/02/15 12:33:19 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

char	**parse_history(void)
{
	char	**ret;
	char	*buff;
	int		r;
	int		fd;
	char	*stock;
	char	*tmp;

	if ((fd = open(".21sh_history", O_RDONLY)) == -1)
		error("OPEN");
	buff = NULL;
	ret = NULL;
	buff = ft_strnew(MAXLEN - 1);
	stock = NULL;
	while ((r = read(fd, buff, (MAXLEN - 1))) > 0)
	{
		tmp = NULL;
		buff[r] = 0;
		tmp = ft_strjoin(stock, buff);
		stock = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
	ret = stock ? ft_strsplit(stock, '\n') : NULL;
	stock ? ft_strdel(&stock) : NULL;
	close(fd);
	return (ret);
}

void	add_to_history(t_all *all)
{
	char	*history_line;
	char	*tmp;
	int		ct;
	int		i;

	if (!(history_line = (char *)malloc(sizeof(char) * (int)all->cmd_termcaps->lenght + 1)))
		return ;
	tmp = ft_itoa(all->pos_history++);
	ct = 0;
	i = 0;
	while (tmp[i])
		history_line[ct++] = tmp[i++];
	(tmp) ? ft_strdel(&tmp) : NULL;
	history_line[ct++] = ':';
	i = 0;
	while (all->cmd[i])
		history_line[ct++] = all->cmd[i++];
	history_line[ct] = '\0';
	write(all->fd_history, history_line, ft_strlen(history_line));
	write(all->fd_history, "\n", 1);
	(history_line) ? ft_strdel(&history_line) : NULL;
}

void	display_index_cmd(t_all *all)
{
	int		ct = 0;
	int		i = 0;
	char	*tmp;

	tmp = NULL;
	// if (all->history_buff != NULL)
	// {
	//	write(1, "bug\n", 4);
		// if (all->history_buff[0] != NULL)
		// {
			if (all->history_buff)
				del_array(&all->history_buff);
			all->history_buff = parse_history();
		// }
	// }
	// exit(printf("here\n"));
			// if ()
	if (!check_history_file(all->history_buff))
	{
		exit(printf("nohi\n")); /* gestion erreur */
		return ;
	}
	while (all->history_buff[all->index_history - 1][ct] != ':')
		ct++;
	// exit(printf("here\n"));
	tmp = ft_strdup(all->history_buff[all->index_history - 1] + (ct + 1));
	all->cursor_pos = i;
	ft_putstr(tmp);
	realloc_termcaps_cmd(all, tmp);
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

	ret = all->curr_line;
	while (CURSOR > ret * LINE_LEN)
		ret++;
	return (ret);
}











