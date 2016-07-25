/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/23 04:48:08 by lubaujar          #+#    #+#             */
/*   Updated: 2016/07/23 04:48:11 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

void			sig_stop(int sig)
{
	t_all	*all;
	char	cp[2];

	all = NULL;
	if ((all = f_cpy(NULL)) == NULL)
		return (ft_putendl("no signal"));
	if (sig == SIGTSTP)
	{
		cp[0] = all->term.c_cc[VSUSP];
		cp[1] = 0;
		all->term.c_lflag |= (ICANON | ECHO);
		signal(SIGTSTP, SIG_DFL);
		tcsetattr(0, 0, &(all->term));
		ioctl(0, TIOCSTI, cp);
	}
}

void			sig_cont(int sig)
{
	t_all	*all;

	all = NULL;
	if ((all = f_cpy(NULL)) == NULL)
		return (ft_putendl("no signal"));
	if (sig == SIGCONT)
	{
		signal(SIGTSTP, sig_stop);
		init_term(all, all->dupenv);
		loop(all);
	}
}

void			sig_winch(int sig)
{
	t_all	*all;

	all = NULL;
	if ((all = f_cpy(NULL)) == NULL)
		return (ft_putendl("no signal"));
	if (sig == SIGWINCH)
	{
		;
	}
}

void			sig_int(int sig)
{
	t_all	*all;
	char	cp[3];

	all = NULL;
	if ((all = f_cpy(NULL)) == NULL)
		;
	if (sig == SIGINT)
	{
		if (!all->prog_exec)
		{
			ft_bzero(cp, 3);
			cp[0] = '\n';
			all && !CMD_NULL ? del_dlist2(all->cmd_termcaps) : NULL;
			all && all->cmd && *all->cmd ? ft_strdel(&all->cmd) : NULL;
			ioctl(0, TIOCSTI, cp);
			init_glob(all);
		}
	}
}

void			sig_catch(void)
{
	signal(SIGWINCH, sig_winch);
	signal(SIGINT, sig_int);
	signal(SIGCONT, sig_cont);
	signal(SIGTSTP, sig_stop);
}
