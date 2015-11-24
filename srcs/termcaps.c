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

void	move_cursor(char *buff, char *cmd, int *i)
{
	// printf("buff: |%s|\n", buff);
	// printf("*buff: |%d|\n", *buff);
	// printf("cmd: |%s|\n", cmd);
	// printf("*cmd: |%c|\n", *cmd);
	// printf("i = %d\n", i);
	// printf("cmd[i]: |%c|\n", cmd[i]);
	// printf("cmd[i - 1]: |%c|\n", cmd[i - 1]);
	// printf("cmd[i - 1]: |%d|\n", cmd[i - 1]);
	// printf("cmd[i + 1]: |%c|\n", cmd[i + 1]);
	// printf("cmd[i + 1]: |%d|\n", cmd[i + 1]);
	// printf("buff[i - 1]: |%c|\n", buff[i - 1]);
	// printf("buff[i - 1]: |%d|\n", buff[i - 1]);
	// printf("buff[i + 1]: |%c|\n", buff[i + 1]);
	// printf("buff[i + 1]: |%d|\n", buff[i + 1]);
	if (K_RIGHT)
	{
		//(*i)--;
		// printf("cmd[i]: |%c|\n", cmd[i]);
	//	printf("cmd[i + 1]: |%c|", cmd[(*i) + 1]);
		if (cmd[(*i) + 1] != 0)
		{
			//(*i)++;
			tputs_termcap("nd");
		}
	}
		//tputs_termcap("kr");
	if (K_LEFT)
	{
	//	printf("cmd[i - 1]: |%c|", cmd[(*i) - 1]);
		if (cmd[(*i) - 1] != 0)
		{
			//(*i)--;
			tputs_termcap("le");
		}
	}
	//tputs_termcap("kl");
}

void	restore_term(t_termios restore)
{
	tputs_termcap("ve");
	if (tcgetattr(0, &restore) == -1)
		term_error("TCGETATTR");
	if (tcsetattr(0, 0, &restore) == -1)
		term_error("TCSETATTR");
}