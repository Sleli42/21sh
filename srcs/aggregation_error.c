/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aggregation_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 17:02:15 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/21 16:03:56 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

int		check_error_agg2(t_all *all, char **split, char *file)
{
	while (split && ft_strcmp(*split, ">&"))
		split++;
	if (!ft_strcmp(*(split + 1), "-"))
		close_fd(all, *(split - 1));
	else if (ft_isdigit(file[0]) && ft_atoi(file) > 2)
	{
		ft_putstr("sh: ");
		ft_putnbr(ft_atoi(file));
		ft_putstr(": Bad file descriptor\n");
		return (1);
	}
	else if ((ft_isdigit(*(split - 1)[0]) && ft_atoi(*(split - 1)) > 2
		&& ft_strcmp(file, "-")))
	{
		ft_putstr("sh: ");
		ft_putstr(file);
		ft_putstr(": ambiguous redirect\n");
		return (1);
	}
	return (0);
}

int		check_error_agg3(t_all *all, char **split, char *file)
{
	while (split && ft_strcmp(*split, "<&"))
		split++;
	if (!ft_strcmp(*(split + 1), "-"))
		close_fd(all, *(split - 1));
	else if (ft_isdigit(file[0]) && ft_atoi(file) > 2)
	{
		ft_putstr("sh: ");
		ft_putnbr(ft_atoi(file));
		ft_putstr(": Bad file descriptor\n");
		return (1);
	}
	else if ((ft_isdigit(*(split - 1)[0]) && ft_atoi(*(split - 1)) > 2
		&& ft_strcmp(file, "-")))
	{
		ft_putstr("sh: ");
		ft_putstr(file);
		ft_putstr(": ambiguous redirect\n");
		return (1);
	}
	return (0);
}
