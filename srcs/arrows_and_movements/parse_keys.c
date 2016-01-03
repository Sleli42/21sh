/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/03 18:06:46 by lubaujar          #+#    #+#             */
/*   Updated: 2016/01/03 18:06:48 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int		ft_getkey(char *s)
{
	int			result;
	int			i;
	int			mult;
	int			value;

	result = 0;
	i = 0;
	while (i < 6)
	{
		mult = 10;
		value = s[i];
		while (value > 10)
		{
			mult *= 10;
			value /= 10;
		}
		result = result * mult + s[i];
		i++;
	}
	return (result);
}

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