/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_search_tools.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/27 03:32:21 by lubaujar          #+#    #+#             */
/*   Updated: 2016/07/27 03:32:23 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

int				check_keys_arrows_histo(t_all *all, char *buff)
{
	all->current_key = getkey(buff);
	if (all->current_key == K_ENTER)
		return (down_line(all));
	if (all->current_key == K_BACKSPACE)
		return (1);
	return (0);
}

static void		key_loop_histo(t_all *all, const t_keys keys[2])
{
	int		i;

	i = 0;
	while (i < 2)
	{
		if (all->current_key == keys[i].action_name)
		{
			keys[i].f(all);
			return ;
		}
		i++;
	}
}

void			parse_keys_histo(t_all *all)
{
	static const	t_keys	keys[] =
	{{K_BACKSPACE, del_char},
	{K_DELETE, del_char}};

	key_loop_histo(all, keys);
}

int				read_keys_search(t_all *all)
{
	int		key;

	key = 0;
	if (read(0, all->buff, (MAXLEN - 1)) == -1)
		return (0);
	if (*all->buff == 4)
		control_d(all);
	else if ((key = check_keys_arrows_histo(all, all->buff)) < 0)
		return (0);
	else if (key > 0)
	{
		(all->prompt) ? ft_strdel(&all->prompt) : NULL;
		all->prompt = ft_strdup(all->histo_prompt);
		parse_keys_histo(all);
	}
	else if (check_str(all->buff))
		insert_char(all);
	return (1);
}
