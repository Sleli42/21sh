/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 14:24:07 by lubaujar          #+#    #+#             */
/*   Updated: 2015/12/02 14:24:08 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int		check_keys_arrows(t_all *all, char *buff)
{
	int		i;
	static const	t_keys	keys[] =

	{{K_UP, goto_latest_commands},
	{K_DOWN, goto_latest_commands},
	{K_RIGHT, horizontal_moves},
	{K_LEFT, horizontal_moves},
	{K_BACKSPACE, del_char},
	{K_BACKSPACE2, del_char},
	{K_BACKSPACE3, del_char},
	{K_DELETE, del_char},
	{K_CTRL_LEFT, horizontal_moves_by_words}};

	i = 0;
	all->current_key = ft_getkey(buff);
	if (all->current_key == K_ENTER)
		return (-1);
	// printf("-> |%d|\n", test);
	// printf("->> |%d|\n", keys[4].action_name);
	// printf("->> |%d|\n", all->current_key);
//	// int j = 0;
	// while (buff[j])
	// 	printf("-> [ %d ] ", buff[j++]);
	// printf("\n");
	while (i < 9)
	{
		if (all->current_key ==  keys[i].action_name)
		{
			keys[i].f(all);
			return (1);
		}
		i++;
	}
	return (0);
}

void	horizontal_moves_by_words(t_all *all)
{
	if (all->current_key == K_CTRL_LEFT)
	{
		write(1, "ok\n", 3);
	}
}

void	horizontal_moves(t_all *all)
{
	// if (all->current && !all->history_moves)
	// {
	// 	all->history_moves = 1;
	// 	realloc_termcaps_cmd(all, all->current);
	// 	all->cursor_pos = (int)all->cmd_termcaps->lenght;
	// 	all->stop = 1;
	// }
	// printf("all->cmd: %s\n", all->cmd);
//	printf("lenght: %zu\n", all->cmd_termcaps->lenght);
//	printf("cursor pos: %d\n", all->cursor_pos);
	if (all->current_key == K_LEFT && all->cmd_termcaps->lenght > 0 && all->cursor_pos > 1)
	{
		all->cursor_pos--;
		tputs_termcap("le");
	}
	if (all->current_key == K_RIGHT && all->cmd_termcaps->lenght > 0
		&&  (size_t)all->cursor_pos < all->cmd_termcaps->lenght + 1)
	{
		all->cursor_pos++;
		tputs_termcap("nd");
	}
	// all->stop = 0;
}
/*
void	update_cmd_line_del(t_all *all)
{
	int		ct;

	ct = all->cursor_pos;
	while ((size_t)ct++ <= all->cmd_termcaps->lenght)
		tputs_termcap("nd");
	while (--ct)
	{
		tputs_termcap("le");
		tputs_termcap("dc");
	}
	create_cmd(all);
	ft_putstr(all->cmd);
	ct = (int)all->cmd_termcaps->lenght;
	while (ct-- >= all->cursor_pos)
		tputs_termcap("le");
}*/

void	del_char(t_all *all)
{
//	write(1, "here\n", 5);
	if (all->already_in_history)
		realloc_termcaps_cmd(all, all->cmd);
	//tputs_termcap("me");
	tputs_termcap("dm");
	//printf("cursor_pos: %d\n", all->cursor_pos);
	if (all->cmd_termcaps->lenght > 0 && all->cursor_pos > 1)
	{
		// printf("lenght: %zu\n", all->cmd_termcaps->lenght);
		if ((size_t)all->cursor_pos <= all->cmd_termcaps->lenght + 1)
		{
		//	write(1, "HEERE\n", 6);
		//	printf("cursor before: %d\n", all->cursor_pos);
			(all->current_key != K_BACKSPACE2 && all->current_key != K_BACKSPACE3)
			 ? dlst_del_one2(all->cmd_termcaps, all->cursor_pos)
				: dlst_del_one2(all->cmd_termcaps, all->cursor_pos - 1);
		}
		(all->current_key == K_BACKSPACE || all->current_key == K_BACKSPACE2
			|| all->current_key == K_BACKSPACE3)
			? tputs_termcap("le") : NULL;
		tputs_termcap("dc");
		if (all->current_key == K_BACKSPACE || all->current_key == K_BACKSPACE2
			|| all->current_key == K_BACKSPACE3)
			all->cursor_pos--;
		tputs_termcap("ed");
	}
}
/*
void	make_moves(t_all *all, char buff[3])
{
	//int			deltab = 0;
	//write(1, "here\n", 5);
	//printf("|%c|\n", all->cmd_termcaps->tail->c);
	if (K_RIGHT || K_LEFT)
	{
		horizontal_moves(all, buff);
	}
	if (K_UP || K_DOWN)
		goto_latest_commands(all, buff);
	// if (K_TAB)
	// {
	// 	if (!all->cmd_termcaps->head)
	// 	{
	// 		return ;
	// 	}
	// 	else
	// 		open_directories(all);
	// }
	if (K_DELETE || K_DELETE2 || buff[0] == 127 || K_BACKSPACE)
	{
		if (all->already_in_history)
			realloc_termcaps_cmd(all, all->cmd);
		// if (all->already_autocomplete)
		// {
		// 	//printf("tail: %c\n", all->cmd_termcaps->tail->c);
		// 	printf("cursor_ pos: %d\n", all->cursor_pos);
		// 	printf("lenght list: %zu\n", all->cmd_termcaps->lenght);
		// }
		tputs_termcap("me");
		tputs_termcap("dm");
		if (all->cmd_termcaps->lenght > 0 && all->cursor_pos > 1)
		{
			if ((size_t)all->cursor_pos <= all->cmd_termcaps->lenght + 1)
			{
			//	write(1, "HEERE\n", 6);
				(K_BACKSPACE) ? dlst_del_one2(all->cmd_termcaps, all->cursor_pos)
					: dlst_del_one2(all->cmd_termcaps, all->cursor_pos - 1);
			}
			(!K_BACKSPACE) ? tputs_termcap("le") : NULL;
			tputs_termcap("dc");
			if (!K_BACKSPACE)
				all->cursor_pos--;
			tputs_termcap("ed");
		}
	}
}*/