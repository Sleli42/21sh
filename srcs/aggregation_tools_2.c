/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aggregation_tools_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/23 04:42:25 by lubaujar          #+#    #+#             */
/*   Updated: 2016/07/23 04:42:26 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

int		check_fd_to_fd(char *s)
{
	int		ct;

	ct = 0;
	if (!ft_strncmp(s + 1, ">&", 2))
	{
		if (ft_isdigit(s[0]) && ft_isdigit(s[ft_strlen(s) - 1]))
			return (1);
	}
	return (0);
}

int		check_close_fd(char **array)
{
	int		ct;

	ct = 0;
	while (array && array[ct])
	{
		if (!ft_strcmp(array[ct], "1>&-") || !ft_strcmp(array[ct], "2>&-"))
			return (1);
		ct++;
	}
	return (0);
}

void	exec_double_fd(t_all *all, char **array)
{
	int		first_fd;
	int		secnd_fd;

	all->dbl_fd = 1;
	first_fd = ft_atoi(&array[ft_tablen(array) - 1][0]);
	secnd_fd = ft_atoi(&array[ft_tablen(array) - 1]\
				[ft_strlen(array[ft_tablen(array) - 1]) - 1]);
	if ((first_fd >= 0 && first_fd <= 2)
		&& (secnd_fd >= 0 && secnd_fd <= 2))
		dup2(secnd_fd, first_fd);
	else
	{
		ft_putstr("42sh: ");
		(first_fd > secnd_fd) ? ft_putnbr(first_fd) : ft_putnbr(secnd_fd);
		ft_putstr(": Bad file descriptor\n");
		all->dbl_fd = -1;
	}
}
