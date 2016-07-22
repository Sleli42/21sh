/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/03 15:59:16 by lubaujar          #+#    #+#             */
/*   Updated: 2016/05/24 18:57:13 by skhatir          ###   ########.fr       */
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

// void			sig_handler(int sig)
// {
// 	t_all		*all;
// 	char		cp[3];

// 	all = NULL;
// 	if ((all = f_cpy(NULL)) == NULL)
// 			;
// 	if (sig == SIGTERM)
// 		exit(0);
// 	else if (sig == SIGINT)
// 	{
// 		if (!all->prog_exec)
// 		{
// 			ft_bzero(cp, 3);
// 			cp[0] = '\n';
// 			all && !CMD_NULL ? del_dlist2(all->cmd_termcaps) : NULL;
// 			all && all->cmd && *all->cmd ? ft_strdel(&all->cmd) : NULL;
// 			ioctl(0, TIOCSTI, cp);
// 			init_glob(all);
// 		}
// 	}
// 	else if (sig == SIGKILL)
// 		exit(0);
// 	else
// 		return ;
// }

void			sig_catch(void)
{
	// int sig;

	// sig = 0;
	// while (sig++ < 32)
	// 	signal(sig, sig_handler);
	signal(SIGWINCH, sig_winch);
	signal(SIGINT, sig_int);
	signal(SIGCONT, sig_cont);
	signal(SIGTSTP, sig_stop);
}

void			opening_sh(void)
{
	char		buf[1024];
	int			r;
	int			art;

	r = 0x0;
	if ((art = open("misc/opening.shell", O_RDONLY)) < 0)
		return (ft_putendl("opening failed"));
	while ((r = read(art, buf, 1024)))
	{
		buf[r] = 0;
		ft_putstr(buf);
	}
	close(art);
}

int				main(int ac, char **av, char **env)
{
	t_all	*all;

	(void)ac;
	(void)av;
	// opening_sh();
	all = init_all(env);
	sig_catch();
	init_term(all, all->dupenv);
	loop(all);
	del_dlist(all->env);
	del_dlist(all->cmd_history);
	reset_term(all);
	write(1, "\n", 1);
	exit(1);
	return (0);
}
