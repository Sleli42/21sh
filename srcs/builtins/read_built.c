/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 11:43:19 by skhatir           #+#    #+#             */
/*   Updated: 2016/02/02 19:58:03 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static t_var	*init_caps(void)
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

static void		add_back(t_var *var_cp, t_var **local_var, t_all *all)
{
	t_var		*nav;
	t_var		*cpy;

	cpy = init_caps();
	cpy->var_name = ft_strdup(var_cp->var_name);
	cpy->content = ft_strdup(var_cp->content);
	nav = (*local_var) ? (*local_var) : NULL;
	if (ft_strlen(var_cp->var_name) > all->max_len)
		all->max_len = ft_strlen(var_cp->var_name);
	if (!nav)
		(*local_var) = cpy;
	else
	{
		while (nav)
		{
			if (nav->var_name && var_cp->var_name && !ft_strcmp(nav->var_name, var_cp->var_name))
			{
				nav->content ? ft_strdel(&nav->content): NULL;
				nav->content = ft_strdup(var_cp->content);
				var_cp->content ? ft_strdel(&var_cp->content) : NULL;
				var_cp->var_name ? ft_strdel(&var_cp->var_name) : NULL;
				var_cp ? free(var_cp) : NULL;
				var_cp = NULL;
				return ;
			}
			else if (!nav->next)
			{
				nav->next = cpy;
				cpy->prev = nav;
				return ;
			}
			nav = nav->next;
		}
	}
}

static void		creat_var(t_all *all, char *var, char *in)
{
	t_var		*var_cp;

	var_cp = NULL;
	if ((var_cp = (t_var *)malloc(sizeof(t_var *))) == NULL)
		exit(printf("MALLOC LOCAL VAR FAIL\n"));
	var_cp->var_name = ft_strdup(var);
	var_cp->content = ft_strdup(in);
	add_back(var_cp, &all->local_var, all);
}

static char			*implode(char **var_tab, int index)
{
	char			*stock;
	char			*tmp;
	char			*for_sp;

	stock = ft_strdup(var_tab[index]);
	while (var_tab[++index])
	{
		tmp = ft_strjoin(stock, (for_sp = ft_strjoin(" ", var_tab[index])));
		ft_strdel(&stock);
		stock = ft_strdup(tmp);
		ft_strdel(&for_sp);
		ft_strdel(&tmp);
	}
	return (stock);
}

void	ft_tabdel(char ***tabi)
{
	char	**p;
	int		i;

	i = 0;
	p = (*tabi);
	while (p[i] && **p)
	{
		ft_strdel(&p[i]);
		i++;
	}
	p = NULL;
}

// void		init_tread(t_all)
// {}

int			dft_reply(char ***cmd_tab)
{
	char		**dft_reply;

	dft_reply = NULL;
	if ((dft_reply = (char **)malloc(sizeof(char *) * 3)) == NULL)
		exit(printf("MALLOC dft_reply failed\n"));
	dft_reply[0] = ft_strdup("read");
	dft_reply[1] = ft_strdup("REPLY");
	dft_reply[2] = NULL;
	ft_tabdel(cmd_tab);
	(*cmd_tab) = dft_reply;
	return (0x0);
}

int				read_line_err(int err)
{
	if (err)
	{
		ft_putstr(S_ERR);
		return (-1);
	}
	return (0);
}

int				read_ct(char *cmd_tab, int *opt, t_all *all)
{
	int			i;
	int			j;
	// int			ret;

	i = 0;
	j = 0;
	(void)all;
	while (cmd_tab[++i])
	{
		while (RD_OP[++j])
		{
			if (RD_OP[j])
				(*opt) = DB(j, (*opt));
		}
		j = 0;
	}
	return (0);
}

void			get_opt(char **cmd_tab, int *opt, t_all *all)
{
	int			i;
	int			j;

	i = 1;
	j = 1;
	// init_tread(all);
	while (cmd_tab[i] && cmd_tab[i][0] == '-')
	{
		if ((i += read_ct(cmd_tab[i], opt, all)) == -1)
			read_line_err(1);
	}
}

void			read_built(t_all *all, char *cmd)
{
	int			i;
	int			j;
	int			key;
	int			opt;
	char		*tmp;
	char		buf[0x5];
	char		*stock;
	char		**cmd_tab;
	char		**var_tab;

	cmd_tab = ft_strsplit(cmd, ' ');
	cmd_tab[1] ? get_opt(cmd_tab, &opt, all) : dft_reply(&cmd_tab);
		// return ;
	stock = NULL;
	(void)all;
	ft_putchar('\n');
	stock = ft_strnew(0);
	while ((i = read(0x0, buf, 0x5)) > 0x0)
	{
		tmp = NULL;
		buf[i] = 0x0;
		if (*buf == '\n')
			break;
		if (!(key = check_keys_arrows(all, buf)))
		{
			ft_putstr(buf);
			tmp = ft_strjoin(stock, buf);
			stock ? ft_strdel(&stock) : NULL;
			stock = ft_strdup(tmp);
			tmp ? ft_strdel(&tmp): NULL;
		}
		ft_memset(buf, 0, 0x5);
	}
	i = 0x0;
	j = 0x0;
	var_tab = ft_strsplit(stock, ' ');
	stock ? ft_strdel(&stock) : NULL;
	while(cmd_tab[++i])
	{
		if (!cmd_tab[i + 1] && var_tab[j] && var_tab[j + 1])
		{
			creat_var(all, cmd_tab[i], (tmp = implode(var_tab, j)));
			tmp ? ft_strdel(&tmp) : NULL;
		}
		else
			var_tab[j++] ? creat_var(all, cmd_tab[i], var_tab[j - 1]) : NULL;
	}
	ft_putchar('\n');
}
