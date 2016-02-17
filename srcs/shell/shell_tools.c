/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/03 16:43:24 by lubaujar          #+#    #+#             */
/*   Updated: 2015/11/03 16:43:29 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

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
	all->cmd_termcaps = dlst_insert_cmd(all->cmd_termcaps,
		dlst_cmd_new(char2add), (CURSOR - PROMPT_LEN) + 1);
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
	all->cursor_pos = (int)all->cmd_termcaps->lenght + PROMPT_LEN;
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
