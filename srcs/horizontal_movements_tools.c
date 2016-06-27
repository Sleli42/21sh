/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_movements_tools.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/03 18:03:21 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/21 16:11:23 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

int		check_if_spaces_before(t_all *all, int pos)
{
	if (pos <= PROMPT_LEN)
		return (0);
	while (all->cmd[pos])
	{
		if (all->cmd[pos] == ' ' && all->cmd[pos - 1] != ' ')
			return (1);
		pos--;
	}
	return (0);
}

int		check_if_spaces_after(t_all *all, int pos)
{
	if (pos + PROMPT_LEN == (int)ft_strlen(all->cmd))
		return (0);
	while (all->cmd[pos])
	{
		if (all->cmd[pos] == ' ' && all->cmd[pos - 1] != ' ')
			return (1);
		pos++;
	}
	return (0);
}

t_cmd	*goto_cursor_pos(t_cmd *lst, int pos)
{
	t_cmd	*tmp;
	int		ct;

	tmp = lst;
	ct = -1;
	if (tmp)
		while (tmp && ++ct < pos - 1)
			tmp = tmp->next;
	return (tmp);
}

int		count_2_prev_spaces(t_all *all)
{
	int		stop;
	int		tmp;

	stop = 0;
	tmp = (CURSOR - PROMPT_LEN) - 1;
	while (all->cmd[tmp] && all->cmd[tmp] != ' ')
	{
		stop++;
		tmp--;
	}
	stop += 1;
	return (stop);
}

int		count_2_next_spaces(t_all *all)
{
	int		stop;
	int		tmp;

	stop = 0;
	tmp = (CURSOR - PROMPT_LEN) + 1;
	while (all->cmd[tmp] && all->cmd[tmp] != ' ')
	{
		stop++;
		tmp++;
	}
	stop += 1;
	return (stop);
}
