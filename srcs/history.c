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
	t_node	*tmp = lst->head_node;

	while (tmp) {
		printf("-> %s\n", tmp->s);
		tmp = tmp->next;
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

char	*goto_latest_commands(t_all *all, size_t lenght)
{
	char	*cmd2exec;
	//display_prompt(all);
	if (lenght <= all->cmd_history->lenght)
	{
		cmd2exec = display_last_cmd(all->cmd_history, lenght);
		return (cmd2exec);
		/*
		write(1, "\n", 1);
		parse_command(all, cmd2exec);
		exec_command(all);
		*/
	}
	return (NULL);
	//display_dlst_history(all->cmd_history);
}