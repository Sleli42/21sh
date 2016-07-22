/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop_tools_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 18:06:36 by lubaujar          #+#    #+#             */
/*   Updated: 2016/05/24 16:47:44 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"
#define ERROR_MSG	"\n42sh: Parse error"

int			check_str(char *buff)
{
	int		ct;

	ct = 0;
	while (buff[ct])
	{
		if (!ft_isprint(buff[ct]))
			return (0);
		ct++;
	}
	return (1);
}

void		check_glob(t_glob *g)
{
	if (g->err)
		return ;
	else if (g->sub != 0 || g->crush != 0 || g->c_indx != 0 || g->quote != 0 ||\
		g->d_quote != 0)
		g->err = g->err && *g->err ? g->err : ft_strdup(ERROR_MSG);
}

void		save_glob(t_all *all, t_glob *g)
{
	if (*all->buff == '(' || *all->buff == ')')
		g->sub += *all->buff == '(' ? 1 : -1;
	else if (*all->buff == '{' || *all->buff == '}')
		g->crush += *all->buff == '{' ? 1 : -1;
	else if (*all->buff == '[' || *all->buff == ']')
		g->c_indx += *all->buff == '[' ? 1 : -1;
	else if (*all->buff == '\'')
		g->quote += g->quote ? -1 : 1;
	else if (*all->buff == '\"')
		g->d_quote += g->d_quote ? -1 : 1;
	else if (*all->buff == '\\')
		g->back += g->back ? -1 : 1;
	if (g->sub < 0 || g->crush < 0 || g->c_indx < 0)
		g->err = ft_strdup(ERROR_MSG);
}

void		create_and_exec_command(t_all *all)
{
	char		*tmp;

	create_cmd(all);
	(all->cmd[ft_strlen(all->cmd) - 1] == '\n') ?
	all->cmd[ft_strlen(all->cmd) - 1] = '\0' : write(1, "\0", 1);
	write(1, "\n", 1);
	tmp = ft_epur_str(all->cmd);
	all->cmd || *all->cmd ? ft_strdel(&all->cmd) : NULL;
	all->cmd = ft_strdup(tmp);
	tmp || *tmp ? ft_strdel(&tmp) : NULL;
	if (all->cmd[0] != 0 && ft_strlen(all->cmd) > 0)
	{
		parse_command(all, all->cmd);
		all->parsecmd && all->parsecmd[0] ? exec_command(all) : NULL;
		add_to_history(all);
	}
	!CMD_NULL ? del_dlist2(all->cmd_termcaps) : NULL;
	all->cmd || *all->cmd ? ft_strdel(&all->cmd) : NULL;
	loop(all);
}

void		write_buffer(t_all *all)
{
	int		ct;

	ct = 0;
	if (all->globing.dt_print | all->globing.cr_split)
	{
		*&all->globing.cr_split = 0x0;
		*&all->globing.dt_print = 0x0;
	}
	else
		ft_putstr(all->buff);
	if (ft_strlen(all->buff) > 1)
	{
		while (all->buff[ct])
		{
			dlst_add_back_2(all->cmd_termcaps, dlst_cmd_new(all->buff[ct]));
			CURSOR++;
			ct++;
		}
	}
	else
	{
		dlst_add_back_2(all->cmd_termcaps, dlst_cmd_new(*all->buff));
		CURSOR++;
	}
}
