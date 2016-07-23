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
	opening_sh();
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
