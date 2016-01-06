/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/05 10:04:19 by lubaujar          #+#    #+#             */
/*   Updated: 2016/01/05 10:04:22 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	copy_buffer(t_all *all)
{
	if (!all->already_in_cpy)
	{
		all->save_cursor_pos = all->cursor_pos;
		all->already_in_cpy = 1;
		all->cpy_move_right = 0;
		all->cpy_move_left = 0;
	}
	else
	{
		tputs_termcap("me");
		all->already_in_cpy = 0;
		if (all->cpy_move_right > 0)
			copy_right(all);
		else if (all->cpy_move_left > 0)
			copy_left(all);
	}
}

void	cut_buffer(t_all *all)
{
	int		ct;
	char	*ret;

	ct = -1;
	ret = NULL;
	if (all->cursor_pos < (int)all->cmd_termcaps->lenght)
	{
		create_cmd(all);
		ret = ft_strnew(all->cursor_pos - 1);
		while (++ct < all->cursor_pos - 1)
			ret[ct] = all->cmd[ct];
		ret[ct] = 0;
		realloc_termcaps_cmd(all, ret);
		ft_strdel(&all->cmd);
		ft_strdel(&ret);
		tputs_termcap("dm");
		tputs_termcap("ce");
		tputs_termcap("ed");
	}
}

static char	*insert_str_to_str(char *cmd, char *cpy, int pos)
{
	char	*ret;
	int		ct;
	int		i;
	int		j;

	ct = 0;
	i = 0;
	j = 0;
	if (!(ret = (char *)malloc(sizeof(char) * pos + ft_strlen(cpy) + 1)))
		return (NULL);
	while (cmd[i] && i < pos)
		ret[ct++] = cmd[i++];
	while (cpy[j])
		ret[ct++] = cpy[j++];
	if ((size_t)i < ft_strlen(cmd))
		while (cmd[i])
			ret[ct++] = cmd[i++];
	ret[ct] = 0;
	return (ret);
}

void	paste_buffer(t_all *all)
{
	int		save;
	char	*new_str;

	save = 0;
	if (all->copy)
	{
		//printf("cursor paste: %d\n", all->cursor_pos);
		//printf("cursor 0: %d\n", all->cursor_pos);
		all->cursor_pos += ft_strlen(all->copy);
		create_cmd(all);
		/* -> fct a revoir !!!
		new_str = insert_str_to_str(all->cmd, all->copy, all->cursor_pos);
		// if (all->cpy_move_left > 0 && all->cpy_move_right == 0)
		// 	save = all->cursor_pos 
		// else if (all->cpy_move_right > 0 && all->cpy_move_left == 0)
			save = all->cursor_pos;
		// printf("cursor 1: %d\n", all->cursor_pos);
		// printf("len total: %zu\n", ft_strlen(new_str));
		realloc_termcaps_cmd(all, new_str);
		ft_strdel(&new_str);
		tputs_termcap("im");
		ft_putstr(all->copy);
		tputs_termcap("ei");
		while (save < all->cursor_pos)
		{
			tputs_termcap("nd");
			save++;
		}
		// printf("lenght: %zu\n", all->cmd_termcaps->lenght);
		// printf("cursor 1: %d\n", all->cursor_pos);
		// t_cmd *nav = goto_cursor_pos(all->cmd_termcaps->head, all->cursor_pos);
		// printf("|%c|\n", nav->c);
		// printf("|%c|\n", nav->prev->c);
	}
}