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

int		check_keys_arrows(char buff[3])
{
	if (K_ENTER)
		return (-1);
	if (K_UP || K_DOWN)
	{
		return (1);
	}
	else if (K_RIGHT || K_LEFT)
	{
		return (2);
	}
	return (0);
}

void	make_moves(t_all *all, char buff[3])
{
	if (K_UP || K_DOWN)
	{
		//display_dlst_history(all->cmd_history);
		goto_latest_commands(all, buff);
	}
	// if (K_DELETE)
	// {

	// }
	// if (K_LEFT)
	// {
		
	// }
}