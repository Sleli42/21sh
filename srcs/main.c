 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/03 15:59:16 by lubaujar          #+#    #+#             */
/*   Updated: 2015/11/03 15:59:18 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

/*
mkdir test ; cd test ; ls -a ; ls | cat | wc -c > fifi ; cat fifi
*/
/*
void	display_tab(char **tab) {
	while (tab && *tab)
		printf("[%s]\n", *tab++);
}
*/
void	check_key(char *buff) {
	if (K_UP || K_DOWN || K_RIGHT || K_LEFT)
		printf("direction key detected\n");
}

void	display_prompt(t_all *all) {
	(void)all;
	write(1, "$: ", 3);
}

void	loop(t_all *all)
{
	int		r;
	char	buff[MAXLEN];

	r = 0;
	f_cpy(all);
	while (1091111096051)
	{
		display_prompt(all);
		ft_memset(buff, 0, ft_strlen(buff));
		if ((r = read(0, buff, (MAXLEN - 1))) == -1)
			return ;
		//check_key(buff);
		buff[r - 1] = '\0';
		if (r == 0)
			return ;
		else if (r > 0)
		{
			parse_command(all, buff);
			exec_command(all);
		}
	}
}

int		main(int ac, char **av, char **env)
{
	t_all	*all;

	(void)ac;
	(void)av;
	all = init_all(env);
	loop(all);
	restore_term(all->restore);
	write(1, "\n", 1);
	exit(1);
	return (0);
}