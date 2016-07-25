/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/03 18:06:46 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/21 16:11:16 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

int			getkey(char *s)
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

int			down_line(t_all *all)
{
	if (all->curr_line < all->nb_lines)
	{
		while (all->curr_line < all->nb_lines)
		{
			tputs_termcap("do");
			all->curr_line++;
		}
		all->curr_line = 1;
	}
	all->already_in_search = 0;
	return (-1);
}

int			check_keys_arrows(t_all *all, char *buff)
{
	all->current_key = getkey(buff);
	// printf("Key: %d\n", all->current_key);
	if (all->current_key == K_ENTER || all->current_key == K_SHIFT_UP \
	|| all->current_key == K_SHIFT_DOWN || all->current_key == K_SHIFT_RIGHT \
										|| all->current_key == K_SHIFT_LEFT)
		return (down_line(all));
	if (all->current_key == K_RIGHT || all->current_key == K_LEFT
		|| all->current_key == K_UP || all->current_key == K_DOWN
		|| all->current_key == K_CTRL_RIGHT || all->current_key == K_CTRL_LEFT
		|| all->current_key == K_CTRL_UP || all->current_key == K_CTRL_DOWN
		|| all->current_key == K_DELETE || all->current_key == K_BACKSPACE
		|| all->current_key == K_HOME || all->current_key == K_END
		|| all->current_key == K_CTRL_CLEAR || all->current_key == K_CTRL_CUT
		|| all->current_key == K_CTRL_COPY || all->current_key == K_CTRL_PASTE
		|| all->current_key == K_TAB || all->current_key == K_CTRL_HISTO)
		return (1);
	return (0);
}

void		key_loop(t_all *all, const t_keys keys[18])
{
	int		i;

	i = 0;
	while (i < 18)
	{
		if (all->current_key == keys[i].action_name)
		{
			keys[i].f(all);
			return ;
		}
		i++;
	}
}

void		parse_keys(t_all *all)
{
	static const	t_keys	keys[] =
	{{K_UP, goto_latest_commands},
	{K_DOWN, goto_latest_commands},
	{K_RIGHT, horizontal_moves},
	{K_LEFT, horizontal_moves},
	{K_BACKSPACE, del_char},
	{K_DELETE, del_char},
	{K_CTRL_LEFT, opt_left_move},
	{K_CTRL_RIGHT, opt_right_move},
	{K_CTRL_UP, goto_up_line},
	{K_CTRL_DOWN, goto_down_line},
	{K_HOME, goto_begin},
	{K_END, goto_end},
	{K_CTRL_CLEAR, ft_clear_screen},
	{K_CTRL_CUT, cut_buffer},
	{K_CTRL_COPY, copy_buffer},
	{K_CTRL_PASTE, paste_buffer},
	{K_TAB, search_autocomplete},
	{K_CTRL_HISTO, search_history}};

	key_loop(all, keys);
}
