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

int			check_keys_arrows(t_all *all, char *buff)
{
	int		ct;

	ct = 0;
	all->current_key = ft_getkey(buff);
	// printf("all curr: %d\n", all->current_key);
	// printf("K_END: %d\n", K_END);
	if (all->current_key == K_ENTER)
		return (-1);
	if (all->current_key == K_RIGHT || all->current_key == K_LEFT
		|| all->current_key == K_UP || all->current_key == K_DOWN
		|| all->current_key == K_CTRL_RIGHT || all->current_key == K_CTRL_LEFT
		|| all->current_key == K_DELETE || all->current_key == K_BACKSPACE
		|| all->current_key == K_HOME || all->current_key == K_END)
		return (1);
	return (0);
}

void		parse_keys(t_all *all)
{
	int		i;
	static const	t_keys	keys[] =

	{{K_UP, goto_latest_commands},
	{K_DOWN, goto_latest_commands},
	{K_RIGHT, horizontal_moves},
	{K_LEFT, horizontal_moves},
	{K_BACKSPACE, del_char},
	{K_DELETE, del_char},
	{K_CTRL_LEFT, opt_left_move},
	{K_CTRL_RIGHT, opt_right_move},
	{K_HOME, goto_begin},
	{K_END, goto_end}};

	i = 0;
	//all->current_key = ft_getkey(buff);
	// printf("->> |%d|\n", keys[4].action_name);
	//printf("->> |%d|\n", all->current_key);
//	// int j = 0;
	// while (buff[j])
	// 	printf("-> [ %d ] ", buff[j++]);
	// printf("\n");
	while (i < 10)
	{
		if (all->current_key ==  keys[i].action_name)
		{
			 //printf("->> |%d|\n", keys[i].action_name);
			keys[i].f(all);
			return ;
		}
		i++;
	}
}

int		check_if_spaces_before(t_dlist2 *lst, int pos)
{
	t_cmd	*tmp;
	int		ct;

	tmp = lst->head;
	ct = 0;
	if (tmp)
	{
		while (ct++ < pos)
		{
			if (tmp->c == ' ')
				return (1);
			tmp = tmp->next;
		}
	}
	return (0);
}

int		check_if_spaces_after(t_dlist2 *lst, int pos)
{
	t_cmd	*tmp;
	int		ct;

	tmp = lst->head;
	ct = -1;
	if (tmp)
	{
		while (tmp && ++ct < pos)
			tmp = tmp->next;
		if (tmp->c == ' ')
			tmp = tmp->next;
		while (tmp)
		{
			if (tmp->c == ' ')
				return (1);
			tmp = tmp->next;
		}
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

void	opt_right_move(t_all *all)
{
	t_cmd	*nav;

	nav = goto_cursor_pos(all->cmd_termcaps->head, all->cursor_pos - 1);
	if (check_if_spaces_after(all->cmd_termcaps, all->cursor_pos - 1))
	{
		if (nav->next->c == ' ' && nav->next->next->c != ' ')
			nav = nav->next->next;
		/* FAUX SI ON PART DU DEBUT DE CHAINE */
		// printf("nav->|%c|\n", nav->c);
		// 	printf("nav->next |%c|\n", nav->next->c);
		while (nav)
		{
			if (nav->c == ' ' && nav->prev->c != ' ')
			{
				tputs_termcap("nd");
				all->cursor_pos++;
				nav = nav->next;
				break ;
			}
			tputs_termcap("nd");
			all->cursor_pos++;
			nav = nav->next;
		}
	}
	else
		goto_end(all);
}

void	opt_left_move(t_all *all)
{
	t_cmd	*nav;

	nav = goto_cursor_pos(all->cmd_termcaps->head, all->cursor_pos - 1);
	if (check_if_spaces_before(all->cmd_termcaps, all->cursor_pos - 1))
	{
		while (nav)
		{
			if (nav->c == ' ' && nav->prev->c != ' ')
			{
				tputs_termcap("le");
				all->cursor_pos--;
				nav = nav->prev;
				break ;
			}
			tputs_termcap("le");
			all->cursor_pos--;
			nav = nav->prev;
		}
	}
	else
		goto_begin(all);
}

void	horizontal_moves(t_all *all)
{
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
}

void	goto_begin(t_all *all)
{
	if (all->cursor_pos > 1)
	{
		while (all->cursor_pos > 1)
		{
			tputs_termcap("le");
			all->cursor_pos--;
		}
	}
}

void	goto_end(t_all *all)
{
	if (all->cursor_pos >= 1 && all->cursor_pos < (int)all->cmd_termcaps->lenght + 1)
	{
		while (all->cursor_pos < (int)all->cmd_termcaps->lenght + 1)
		{
			tputs_termcap("nd");
			all->cursor_pos++;
		}
	}
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
	init_windows_size(all);
	// printf("col: %d\n", all->ws.ws_col);
	//printf("%d\n", all->cursor_pos);
	if (all->already_in_history)
		realloc_termcaps_cmd(all, all->cmd);
	//tputs_termcap("me");
	tputs_termcap("dm");
	// printf("cursor_pos: %d\n", all->cursor_pos);
	// // printf("lenght: %zu\n", all->cmd_termcaps->lenght);
	if (all->cmd_termcaps->lenght > 0 && all->cursor_pos > 1)
	{
		if ((size_t)all->cursor_pos <= all->cmd_termcaps->lenght + 1)
		{
		//	write(1, "HEERE\n", 6);
		//	printf("cursor before: %d\n", all->cursor_pos);
			(all->current_key != K_BACKSPACE) /*&& all->current_key != K_BACKSPACE3*/
			 ? dlst_del_one2(all->cmd_termcaps, all->cursor_pos)
				: dlst_del_one2(all->cmd_termcaps, all->cursor_pos - 1);
		}
		(all->current_key == K_BACKSPACE) /*|| all->current_key == K_BACKSPACE2
			|| all->current_key == K_BACKSPACE3*/
			? tputs_termcap("le") : NULL;
		tputs_termcap("dc");
		if (all->current_key == K_BACKSPACE) /*|| all->current_key == K_BACKSPACE2
			|| all->current_key == K_BACKSPACE3*/
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