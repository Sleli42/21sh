/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 01:12:03 by lubaujar          #+#    #+#             */
/*   Updated: 2015/12/01 01:12:05 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

char	**parse_history(void)
{
	char	**ret;
	char	*buff;
	int		r;
	int		fd;

	if ((fd = open(".21sh_history", O_RDONLY)) == -1)
		error("OPEN");
	buff = NULL;
	ret = NULL;
	buff = ft_strnew(MAXLEN - 1);
	//ft_memset(buff, 0, MAXLEN - 1);
	while ((r = read(fd, buff, (MAXLEN - 1))) > 0)
		buff[r] = 0;
	//write(1, "bug\n", 4);
	ret = ft_strsplit(buff, '\n');
	//write(1, "bug\n", 4);
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
	//printf("test |%s|\n", all->history_buff[all->index_history - 1]);
	if (all->history_buff != NULL)
	{
	//	write(1, "bug\n", 4);
		if (all->history_buff[0] != NULL)
		{
			del_array(&all->history_buff);
			all->history_buff = parse_history();
		}
		//printf("[0]:c %s\n", all->history_buff[0]);
	}
	//if (!(tmp = (char*)malloc(sizeof(char) * ft_strlen(all->history_buff[all->index_history - 1]) + 1)))
	//	error("MALLOC");
	// tmp = ft_strnew(ft_strlen(all->history_buff[all->index_history - 1]));
	//write(1, "bug\n", 4);
	//display_tab_history(all->history_buff);
	while (all->history_buff[all->index_history - 1][ct] != ':')
		ct++;
	tmp = ft_strdup(all->history_buff[all->index_history - 1] + (ct + 1));
	// printf("tmp: %s\n", tmp);
	// ct++;
	// while (all->history_buff[all->index_history - 1][ct])
	// 	tmp[i++] = all->history_buff[all->index_history - 1][ct++];
	// tmp[i] = 0;
	all->cursor_pos = i;
	ft_putstr(tmp);
	realloc_termcaps_cmd(all, tmp);
	//ft_strdel(&tmp);
	// tputs_termcap("cb");
	// tputs_termcap("rc");
//	printf("%s\n", all->history_buff[all->index_history - 1]);
}

/*
sc      Sauvegarder la position du curseur
rc      Restaurer la position enregistrée du curseur
cb      Effacer depuis le début de la ligne jusqu'au curseur
*/



void	goto_latest_commands(t_all *all)
{
	//write(1, "here\n", 5);
	//printf("cursor pos: %d\n", all->cursor_pos);
	if (all->cursor_pos == 1)
		tputs_termcap("sc");
	// printf("%d\n", all->index_history);
	if (all->current_key == K_UP && all->index_history > 1)
	{
		if (all->cursor_pos > 1)
		{
			tputs_termcap("rc");
			tputs_termcap("ce");
			all->cursor_pos = 1;
		}
		all->index_history--;
		display_index_cmd(all);
	}
	if (all->current_key == K_DOWN && all->index_history <= all->pos_history - 1)
	{
		all->index_history++;
		if (all->cursor_pos > 1 || all->index_history == all->pos_history)
		{
			tputs_termcap("rc");
			tputs_termcap("ce");
			all->cursor_pos = 1;
		}
		//printf("index: %d\n", all->index_history);
		//printf("pos: %d\n", all->pos_history);
		if (all->index_history == all->pos_history)
			return;
		else
			display_index_cmd(all);
	}
}