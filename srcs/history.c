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

void	display_dlst_history(t_dlist *lst) {
	t_node	*tmp = lst->tail_node;

	while (tmp != NULL) {
		printf("i: %zu -> %s\n", tmp->index, tmp->s);
		// printf("-> %zu\n", tmp->index);
		// printf("-> %zu\n", lst->lenght);
		tmp = tmp->prev;
	}
}

char	*display_last_cmd(t_dlist *lst, size_t pos)
{
	t_node	*tmp;
	size_t	ct;

	tmp = lst->head_node;
	ct = 0;
	while (ct < pos)
	{
		//ft_putstr(tmp->s);
		tmp = tmp->next;
		ct++;
	}
	ft_putstr(tmp->s);
	return (tmp->s);
}

void	new_line(t_all *all)
{
	int	i = all->cmd_termcaps->lenght;

	if (i == 0 && all->current != NULL)
		i = ft_strlen(all->current);
	//printf("nbchar 2 del: %d\n", i);
	while (i--)
	{
		tputs_termcap("dc"); // efface 1 char sous le curseur
		tputs_termcap("le"); // deplace le curseur de 1 vers la gauche
	}
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
	ft_strdel(&tmp);
	history_line[ct++] = ':';
	i = 0;
	while (all->cmd[i])
		history_line[ct++] = all->cmd[i++];
	history_line[ct] = '\0';
	write(all->fd_history, history_line, ft_strlen(history_line));
	write(all->fd_history, "\n", 1);
	ft_strdel(&history_line);
}

char	**parse_history(void)
{
	char	**ret;
	char	*buff;
	int		r;
	int		fd;

	fd = open(".21sh_history", O_RDONLY);
	buff = (char*)malloc(sizeof(char) * MAXLEN);
	while ((r = read(fd, buff, MAXLEN - 1)) > 0)
		buff[r] = 0;
	ret = ft_strsplit(buff, '\n');
	close(fd);
	return (ret);
}

void	display_index_cmd(t_all *all)
{
	int		ct = 0;
	int		i = 0;
	char	*tmp;

	if (all->history_buff != NULL)
	{
		del_array(&all->history_buff);
		all->history_buff = parse_history();
	}
	if (!(tmp = (char*)malloc(sizeof(char) * ct)))
		return ;
	while (all->history_buff[all->index_history - 1][ct] != ':')
		ct++;
	ct++;
	while (all->history_buff[all->index_history - 1][ct])
		tmp[i++] = all->history_buff[all->index_history - 1][ct++];
	tmp[i] = 0;
	all->cursor_pos = i;
	ft_putstr(tmp);
	realloc_termcaps_cmd(all, tmp);
	if (tmp)
		ft_strdel(&tmp);
	// tputs_termcap("cb");
	// tputs_termcap("rc");
//	printf("%s\n", all->history_buff[all->index_history - 1]);
}

/*
sc      Sauvegarder la position du curseur
rc      Restaurer la position enregistrée du curseur
cb      Effacer depuis le début de la ligne jusqu'au curseur
*/



void	goto_latest_commands(t_all *all, char buff[3])
{
	//printf("cursor pos: %d\n", all->cursor_pos);
	if (all->cursor_pos == 1)
		tputs_termcap("sc");
	//printf("%d\n", all->index_history);
	if (K_UP && all->index_history > 1)
	{
			/* jooooobbbbb .....*/
	//	printf("%d\n", all->index_history);
		if (all->cursor_pos > 1)
		{
			tputs_termcap("rc");
			tputs_termcap("ce");
			all->cursor_pos = 1;
		}
		all->index_history--;
		display_index_cmd(all);

	}
	if (K_DOWN && all->index_history <= all->pos_history - 1)
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
			/* jooooobbbbb .....*/
	}
	// if (K_UP && all->cmd_history->lenght > 0 && all->nav != NULL)
	// {
	// 	new_line(all);
	// 	all->cmd = all->nav->s;
	// 	if (all->nav->prev != NULL)
	// 		all->nav = all->nav->prev;
	// 	all->current = ft_strdup(all->cmd);
	// 	all->already_in_history = 1;
	// 	ft_putstr(all->cmd);
	// }
	// if (K_DOWN && all->cmd_history->lenght > 0 && all->nav != NULL)
	// {
	// 	new_line(all);
	// 	if (all->nav->next != NULL)
	// 		all->nav = all->nav->next;
	// 	all->cmd = all->nav->s;
	// 	all->current = ft_strdup(all->cmd);
	// 	all->already_in_history = 1;
	// 	ft_putstr(all->cmd);
	// }
	
}