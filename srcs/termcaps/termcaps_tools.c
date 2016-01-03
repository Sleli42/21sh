/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/03 16:12:58 by lubaujar          #+#    #+#             */
/*   Updated: 2015/11/03 16:12:59 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

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

void	restore_term(t_termios restore)
{
	tputs_termcap("ve");
	tputs_termcap("me");
	if (tcgetattr(0, &restore) == -1)
		term_error("TCGETATTR");
	if (tcsetattr(0, 0, &restore) == -1)
		term_error("TCSETATTR");
}

void 	reset_term(void)
{
	struct termios	term;

	if (tcgetattr(0, &term) == -1)
		term_error("TCGETATTR");
	term.c_lflag |= ~(ECHO | ICANON);
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		term_error("TCSETATTR");
}