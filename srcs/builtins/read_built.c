/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 11:43:19 by skhatir           #+#    #+#             */
/*   Updated: 2016/03/21 16:08:29 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

void					get_opt(char **cmd_tab, int *opt, t_all *all)
{
	int					i;
	int					ck;
	char				**p;

	i = 1;
	ck = 0;
	while (cmd_tab[i] && cmd_tab[i][0] == '-')
	{
		if ((ck = read_ct(&cmd_tab[i], opt, all)) < 0)
			return (read_line_err(ck, &all->r_box.err));
		i += ck;
	}
	if (cmd_tab[i])
		all->r_box.cmd_tab = &cmd_tab[i];
	else
	{
		p = (char **)malloc(sizeof(char *) * 2);
		p[0] = ft_strdup("REPLY");
		p[1] = NULL;
		all->r_box.cmd_tab = p;
	}
	while (cmd_tab[i])
		if (cmd_tab[i++][0] == '-')
			return (read_line_err(BAD_FORMAT, &all->r_box.err));
}

void					get_var(t_read *r_box, t_all *all, int fd)
{
	char				*stock;
	int					breakpoint;

	stock = ft_strnew(0);
	breakpoint = 0x1;
	all->r_box.check_time = 0x0;
	r_box->var_tab = NULL;
	if (fd == 0 && all->r_box.prompt)
		ft_putstr(all->r_box.prompt);
	while (breakpoint > 0 && all->r_box.nchars-- != 0)
	{
		if ((breakpoint = get_char(all, r_box, fd, &stock)) < 0)
			return (ft_putchar('\n'));
	}
	if (breakpoint == RD_KILL)
		return ;
	r_box->var_tab = ft_strsplit(stock, ' ');
	r_box->full_string = ft_strdup(stock);
	stock ? ft_strdel(&stock) : NULL;
}

void					link_var(t_read *p, t_all *all)
{
	int					i;
	int					j;
	char				*tmp;

	i = 0x0;
	j = 0x0;
	tmp = NULL;
	i += ft_strcmp(p->cmd_tab[i], "read") ? 0 : 1;
	while (p->cmd_tab[i] && p->var_tab[j])
	{
		if (!p->cmd_tab[i + 1] && p->var_tab[j])
		{
			creat_var(all, p->cmd_tab[i], (tmp = implode(p->var_tab, j)));
			tmp ? ft_strdel(&tmp) : NULL;
		}
		else
			p->var_tab[j++] ? creat_var(all, p->cmd_tab[i], p->var_tab[j - 1])\
																: NULL;
		i++;
	}
}

int						init_var(t_all *all, char *cmd)
{
	CMD_TAB = ft_strsplit(cmd, ' ');
	CMD_TAB[1] ? get_opt(CMD_TAB, &all->r_box.opt, all) : dft_reply(&CMD_TAB);
	ft_putchar('\n');
	if (all->r_box.err < 0)
		return (0);
	if (fcntl(all->r_box.fd, F_GETFD) == -1)
	{
		ft_putstr("not a valid fd\n");
		return (0);
	}
	get_var(&all->r_box, all, all->r_box.fd);
	return (1);
}

void					read_built(t_all *all, char *cmd)
{
	t_read				p;

	init_rbox(all);
	if (!init_var(all, cmd))
		return ;
	if (!all->r_box.var_tab)
		return ;
	p = all->r_box;
	if (p.a && p.cmd_tab && p.var_tab[0])
	{
		p.cmd_tab = do_array(p.cmd_tab, p.var_tab, all);
		fill_array(all, p.cmd_tab, p.var_tab);
	}
	else if (!p.a)
		link_var(&p, all);
	ft_putchar('\n');
}
