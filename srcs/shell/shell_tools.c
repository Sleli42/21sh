/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/03 16:43:24 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/21 16:01:38 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

char	goto_elem(t_cmd *cmd, int pos)
{
	t_cmd	*tmp;
	int		ct;

	tmp = cmd;
	ct = 1;
	while (ct++ < pos)
		tmp = tmp->next;
	return (tmp->c);
}

void	update_cmd_line_insert(t_all *all, char char2add)
{
	all->cmd_termcaps = dlst_insert_cmd(all, all->cmd_termcaps,
		dlst_cmd_new(char2add), (CURSOR - PROMPT_LEN \
								+ all->globing.esc_mem) + 1);
	CURSOR++;
}

void	realloc_termcaps_cmd(t_all *all, char *cmd2realloc)
{
	int		ct;

	ct = 0;
	if (all->cmd_termcaps && ((t_cmd *)all->cmd_termcaps->head) && \
								((t_cmd *)all->cmd_termcaps->head)->c)
	{
		if (!all->pcmd_i)
			all->pcmd_t = all->cmd_termcaps;
		all->cmd_termcaps = NULL;
		all->cmd_termcaps = create_cmd_dlst();
	}
	else
		all->pcmd_t = NULL;
	while (cmd2realloc[ct])
		dlst_add_back_2(all->cmd_termcaps, dlst_cmd_new(cmd2realloc[ct++]));
	CURSOR = (int)all->cmd_termcaps->lenght + PROMPT_LEN;
	define_current_line(all);
	all->nb_lines = all->curr_line;
	all->pcmd_i = 1;
}

void	create_cmd(t_all *all)
{
	t_cmd	*nav;
	int		i;

	if (CMD_NULL)
		return ;
	nav = all->cmd_termcaps->head;
	i = 0;
	if (all->cmd && *all->cmd)
		ft_strdel(&all->cmd);
	if (!(all->cmd = (char *)malloc(sizeof(char) * \
				len_lst_cmd(all->cmd_termcaps->head) + 1)))
		error("MALLOC");
	if (nav && all->cmd)
	{
		while (nav)
		{
			all->cmd[i++] = nav->c;
			nav = nav->next;
		}
	}
	all->cmd[i] = '\0';
}

void		define_current_line(t_all *all)
{
	if (all->curr_line == 1)
	{
		while (CURSOR > (LINE_LEN * all->curr_line))
			all->curr_line++;
	}
}
