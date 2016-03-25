/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/03 15:59:16 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/22 14:45:23 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

void			sig_handler(int sig)
{
	if (sig == SIGTERM)
		exit(0);
	if (sig == SIGKILL)
		exit(0);
	else if (sig == SIGTSTP || sig == SIGINT || sig == SIGCONT)
		;
	else
		return ;
}

void			sig_catch(void)
{
	int sig;

	sig = 1;
	while (sig++ < 32)
		signal(sig, sig_handler);
}

void			opening_sh(void)
{
	char		buf[1024];
	int			r;
	int			art;

	r = 0x0;
	if ((art = open("misc/opening.shell", O_RDONLY)) < 0)
		return (ft_putendl("openin failed"));
	while ((r = read(art, buf, 1024)))
	{
		buf[r] = 0;
		ft_putstr(buf);
	}
}

int				main(int ac, char **av, char **env)
{
	t_all	*all;

	(void)ac;
	(void)av;
	opening_sh();
	sig_catch();
	all = init_all(env);
	init_term();
	loop(all);
	del_dlist(all->env);
	del_dlist(all->cmd_history);
	reset_term();
	write(1, "\n", 1);
	exit(1);
	return (0);
}
