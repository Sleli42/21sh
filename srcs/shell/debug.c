/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/04 10:32:07 by lubaujar          #+#    #+#             */
/*   Updated: 2016/01/04 10:32:08 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	display_dlst(t_dlist2 *lst)
{
	t_cmd *tmp = lst->head;

	printf("\n");
	while (tmp) {
		printf("[ %c ]", tmp->c);
		tmp = tmp->next;
	}
	printf("\nlenght: %zu\n", lst->lenght);
}

void	display_current_arg(t_all *all)
{
	t_select	*nav;

	nav = all->list_dir->head;
	while (nav)
	{
		if (nav->onArg)
			write(0, nav->arg, ft_strlen(nav->arg));
		nav = nav->next;
	}
}

void	display_line(t_dlist2 *cmd_termcaps)
{
	t_cmd	*nav;

	nav = cmd_termcaps->head;
	while (nav)
	{
		write(1, &nav->c, 1);
		nav = nav->next;
	}
}

void	display_cursor(t_dlist2 *lst, int pos)
{
	t_cmd *tmp = lst->head;
	int		ct = 0;

	while (ct < pos) {
		tmp = tmp->next;
		ct++;
	}
	printf("cursor: |%c|\n", tmp->c);
}


void	read_key(char *buff)
{
	printf("buff: |%s|\n", buff);
	printf("buff[0]: |%c|\n", buff[0]);
	printf("|%d|\n", ft_getkey(buff));
}ß