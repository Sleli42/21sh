/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_table_f2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 14:51:00 by skhatir           #+#    #+#             */
/*   Updated: 2016/03/21 16:07:33 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

int			ft_t(t_all *all, char *n)
{
	if ((all->r_box.timeout = ft_atoi(n)) < 1)
		return (BAD_TIME);
	return (2);
}

int			ft_p(t_all *all, char *n)
{
	all->r_box.prompt = n;
	return (2);
}

int			ft_a(t_all *all, char *n)
{
	all->r_box.a = 0x1;
	all->r_box.a_name = ft_strdup(n);
	return (2);
}

int			ft_n(t_all *all, char *n)
{
	all->r_box.nchars = ft_atoi(n);
	return (2);
}

int			ft_d(t_all *all, char *n)
{
	all->r_box.delim = n[0] > 31 ? n[0] : '\n';
	return (2);
}
