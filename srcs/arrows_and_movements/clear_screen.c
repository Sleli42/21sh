/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_screen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/04 17:35:45 by lubaujar          #+#    #+#             */
/*   Updated: 2016/01/04 17:35:46 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	ft_clear_screen(t_all *all)
{
	// tputs_termcap("sc");
	if (all->cmd_termcaps->lenght == 0)
	{
		tputs_termcap("cl");
		display_prompt(all);
	}
	else
	{
		tputs_termcap("cl");
		display_prompt(all);
		create_cmd(all);
		ft_putstr(all->cmd);
	}
}
