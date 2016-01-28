/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_movements_tools.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/03 18:03:21 by lubaujar          #+#    #+#             */
/*   Updated: 2016/01/03 18:03:22 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

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
	// printf("cmp: %d && %zu\n", all->cursor_pos, ft_strlen(all->cmd));
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
	{
		while (tmp && ++ct < pos - 1)
			tmp = tmp->next;
	}
	return (tmp);
}

void	goto_begin(t_all *all)
{
	if (all->cursor_pos > PROMPT_LEN)
	{
		while (all->cursor_pos > PROMPT_LEN)
		{
			tputs_termcap("le");
			all->cursor_pos--;
		}
	}
}

void	goto_end(t_all *all)
{
	if (all->cursor_pos >= 1 && all->cursor_pos - PROMPT_LEN < (int)all->cmd_termcaps->lenght)
	{
		while (all->cursor_pos - PROMPT_LEN < (int)all->cmd_termcaps->lenght)
		{
			tputs_termcap("nd");
			all->cursor_pos++;
		}
	}
}