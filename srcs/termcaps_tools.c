/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/03 16:12:58 by lubaujar          #+#    #+#             */
/*   Updated: 2016/05/24 16:47:39 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

t_all	*f_cpy(t_all *all)
{
	static t_all *cpy;

	if (all)
		cpy = all;
	return (cpy);
}

int		lu_putchar(int c)
{
	ft_putchar(c);
	return (0);
}

void	tputs_termcap(char *tc)
{
	char	*res;

	if ((res = tgetstr(tc, NULL)) == NULL)
		return ;
	tputs(res, 0, lu_putchar);
}

void	reset_term(void)
{
	struct termios	term;

	if (tcgetattr(0, &term) == -1)
		;
	term.c_lflag = (ECHO | ICANON);
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		;
}
