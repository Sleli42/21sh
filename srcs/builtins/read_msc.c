/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_msc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 15:27:28 by skhatir           #+#    #+#             */
/*   Updated: 2016/03/21 16:07:46 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

char			*implode(char **var_tab, int index)
{
	char		*stock;
	char		*tmp;
	char		*for_sp;

	stock = ft_strdup(var_tab[index]);
	while (var_tab[++index])
	{
		for_sp = ft_strjoin(" ", var_tab[index]);
		tmp = ft_strjoin(stock, for_sp);
		ft_strdel(&stock);
		stock = ft_strdup(tmp);
		ft_strdel(&for_sp);
		ft_strdel(&tmp);
	}
	return (stock);
}

void			ft_tabdel(char ***tabi)
{
	char		**p;
	int			i;

	i = 0;
	p = (*tabi);
	while (p[i] && **p)
	{
		ft_strdel(&p[i]);
		i++;
	}
	p = NULL;
}

void			init_rbox(t_all *all)
{
	t_read		p;

	p.delim = '\n';
	p.glob = 0x0;
	p.err = 0x0;
	p.opt = 0x0;
	p.fd = 0x0;
	p.timeout = -1;
	p.nchars = -1;
	all->r_box.rdy = 0x1;
	p.prompt = NULL;
	p.a = 0x0;
	p.a_name = NULL;
	p.full_string = NULL;
	p.array = NULL;
	p.cmd_tab = NULL;
	p.var_tab = NULL;
	all->r_box = p;
}

t_var			*init_caps(void)
{
	t_var		*ret;

	ret = NULL;
	if ((ret = (t_var *)malloc(sizeof(t_var *))) == NULL)
		exit(printf("malloc init_caps failed\n"));
	ret->var_name = ft_strnew(0);
	ret->content = ft_strnew(0);
	ret->prev = NULL;
	ret->next = NULL;
	return (ret);
}

void			read_line_err(int err, int *r_err)
{
	(*r_err) = -1;
	if (err == BAD_FORMAT)
	{
		ft_putstr(FORMAT_ERR);
		return (ft_putstr(FORMAT_ERR2));
	}
	else if (err == BAD_FD)
		return (ft_putstr(FD_ERR));
	else if (err == BAD_TIME)
		return (ft_putstr(TIME_ERR));
}
