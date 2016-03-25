/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/05 17:17:19 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/21 16:11:53 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

void		standard_mode(char char2print)
{
	tputs_termcap("dc");
	tputs_termcap("me");
	tputs_termcap("im");
	ft_putchar(char2print);
	tputs_termcap("ei");
	tputs_termcap("le");
}

void		reverse_mode(char char2print)
{
	tputs_termcap("dc");
	tputs_termcap("mr");
	tputs_termcap("im");
	ft_putchar(char2print);
	tputs_termcap("ei");
	tputs_termcap("me");
	tputs_termcap("le");
}
