/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_screen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/04 17:35:45 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/21 16:12:28 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

void	ft_clear_screen(t_all *all)
{
	if (all->cmd_termcaps->lenght == 0)
	{
		tputs_termcap("cl");
		display_prompt(all);
		tputs_termcap("sc");
	}
	else
	{
		tputs_termcap("cl");
		display_prompt(all);
		tputs_termcap("sc");
		create_cmd(all);
		ft_putstr(all->cmd);
	}
	exec_right_binary(all, ft_strsplit("reset", ' '));
	loop(all);
}
