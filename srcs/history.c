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
		printf("-> %s\n", tmp->s);
		printf("-> %zu\n", tmp->index);
		printf("-> %zu\n", lst->lenght);
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

// char	*goto_latest_commands(t_all *all, size_t lenght)
// {
// 	char	*cmd2exec;
// 	//display_prompt(all);
// 	if (lenght <= all->cmd_history->lenght)
// 	{
// 		cmd2exec = display_last_cmd(all->cmd_history, lenght);
// 		return (cmd2exec);
// 		/*
// 		write(1, "\n", 1);
// 		parse_command(all, cmd2exec);
// 		exec_command(all);
// 		*/
// 	}
// 	return (NULL);
// 	//display_dlst_history(all->cmd_history);
// }

void	new_line(t_all *all)
{
	int	i = all->cmd_termcaps->lenght;

	//printf("curr: %s\n", all->current);
	if (i == 0 && all->current != NULL)
		i = ft_strlen(all->current);
	while (i--)
	{
		tputs_termcap("dc"); // efface 1 char sous le curseur
		tputs_termcap("le"); // deplace le curseur de 1 vers la gauche
	}
}

/*
$: -> echo lol
-> 4 -> l
-> 4 -> i
-> lol
-> 3 -> i
-> 4 -> l
-> ok
-> 2 . . .
-> 4 . . .
-> ls -l
-> 1 . . .
-> 4 . . .
*/

void	goto_latest_commands(t_all *all, char buff[3])
{
	if (K_UP && all->cmd_history && all->cmd_history->lenght > 0
		&& all->nav != NULL)
	{
		new_line(all);
		all->cmd = all->nav->s;
		if (all->nav->index > 0)
			all->nav = all->nav->prev;
		all->current = ft_strdup(all->cmd);
		ft_putstr(all->cmd);
	}
	if (K_DOWN && all->cmd_history && all->cmd_history->lenght > 0
		&& all->nav != NULL)
	{
		// new_line(all);
		// all->nav = all->nav->next;
		// all->cmd = all->nav->s;
		// all->current = ft_strdup(all->cmd);
		// ft_putstr(all->cmd);
	}
}