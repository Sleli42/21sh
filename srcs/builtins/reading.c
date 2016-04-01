/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 15:00:51 by skhatir           #+#    #+#             */
/*   Updated: 2016/03/21 16:09:40 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

void			set_timeout(t_all *all)
{
	FD_ZERO(&all->r_box.set);
	FD_SET(0, &all->r_box.set);
	all->r_box.time_set.tv_sec = all->r_box.timeout;
	all->r_box.time_set.tv_usec = 0;
	all->r_box.check_time = time(NULL);
	all->r_box.rdy = \
				select(1, &all->r_box.set, NULL, NULL, &all->r_box.time_set);
}

int				record_key(t_all *all, t_read *r_box, char **s, const char *buf)
{
	char		*tmp;

	tmp = NULL;
	CMP(r_box->opt, 0x2) ? NULL : ft_putstr(buf);
	all->r_box.glob = 0;
	if (*buf == '\\' && !CMP(r_box->opt, 0x1))
		all->r_box.glob = '\\';
	else if (*buf != '\n')
	{
		tmp = ft_strjoin((*s), buf);
		(*s) ? ft_strdel(&(*s)) : NULL;
		(*s) = ft_strdup(tmp);
		tmp ? ft_strdel(&tmp) : NULL;
	}
	return (1);
}

int				f_time(t_all *all, char **stock, t_read *r_box, int *bp)
{
	all->r_box.timeout -= (time(NULL) - all->r_box.check_time);
	(*bp) = all->r_box.timeout > 0 ? 1 : 0;
	if (all->r_box.timeout == 0)
	{
		r_box->var_tab = NULL;
		(*stock) ? ft_strdel(stock) : NULL;
		return (1);
	}
	return (0);
}

int				reading(t_all *all, t_read *r_box, char **stock, int fd)
{
	char		buf[16];
	int			i;

	i = 0;
	while (i < 16)
		buf[i++] = 0;
	if ((i = read(fd, buf, 16)) > 0x0)
	{
		buf[i] = 0x0;
		if (*buf == r_box->delim)
		{
			if (!all->r_box.glob)
				return (0);
			*buf == '\n' ? ft_putstr("\n> ") : \
							record_key(all, r_box, stock, buf);
			all->r_box.glob = 0;
		}
		else if (!check_keys_arrows(all, buf) || *buf == '\n')
			return (record_key(all, r_box, stock, buf));
	}
	return (RD_KILL);
}

int				get_char(t_all *all, t_read *r_box, int fd, char **s)
{
	int			breakpoint;

	breakpoint = 0;
	if (all->r_box.timeout > 0)
		set_timeout(all);
	else
		all->r_box.rdy = 1;
	if (all->r_box.rdy == -1)
	{
		ft_putstr("\nselect failed\n");
		return (-1);
	}
	if (all->r_box.rdy)
	{
		if ((breakpoint = reading(all, r_box, s, fd)) < 1)
			return (breakpoint);
		if (all->r_box.timeout > 0)
			if (f_time(all, s, r_box, &breakpoint))
				return (-1);
	}
	return (breakpoint);
}
